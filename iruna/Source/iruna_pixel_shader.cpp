//---------------------------------------------------------
// 
//	iruna_pixcel_sheder.cpp
//	シェーダーファイル管理クラス
//	作成日 1月14日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_pixel_shader.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	コンストラクタ
PixelShader::PixelShader()
	:	m_pcPS( NULL )
{
	m_eType = ePixcelShader;
	return;
}

//	デストラクタ
PixelShader::~PixelShader()
{
	if( m_pcPS )
	{
		SafeRelease( m_pcPS );
	}
}

//	ピクセルシェーダーの作成
bool PixelShader::CreateShader( std::string strShader,std::string strPixelEntry, eShaderVersion eVersion )
{
	// ピクセルシェーダーのバージョン列挙
	const char* strPixelShaderVersion[] = 
	{
		"ps_1_0",
		"ps_1_1",
		"ps_2_0",
		"ps_3_0",
		"ps_4_0",
		"ps_5_0",
	};

	//	エラー出力用ボルブ
	ID3DBlob* pcErrorBlob;

	HRESULT hr = S_OK;

	ID3DBlob* pcShaderBlob = NULL;

	//	シェーダーファイルを読み込んでコンパイル
	hr = D3DX11CompileFromFile(
		strShader.c_str(),						//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,									//	シェーダー内でマクロを使用するときに使用
		NULL,									//	インクルードファイルを使用できるためのフラグ
		strPixelEntry.c_str(),					//	シェーダーを実行するエントリーポイントの関数名
		strPixelShaderVersion[ eVersion ],		//	シェーダーモデル
		0,										//	シェーダーのコンパイルバージョンHLSLファイル
		0,										//	シェーダーのコンパイルバージョンFXファイル
		NULL,
		&pcShaderBlob,
		&pcErrorBlob,
		NULL
		);

	// シェーダー作成失敗
	if( FAILED( hr ) )
	{
		if( pcErrorBlob != NULL )
		{
			// エラーメッセージ出力
			OutputDebugStringA( (char*)pcErrorBlob->GetBufferPointer() );
		}
	}
	// エラー出力用のボルブを開放する
	if( pcErrorBlob )
	{
		SafeRelease(pcErrorBlob);
	}

	// ピクセルシェーダーを作成
	ID3D11Device* pcDevice = Device::GetDevice();
	hr = pcDevice->CreatePixelShader(
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcPS
		);
	// ピクセルシェーダー作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}
	//	ピクセルシェーダー作成成功
	pcShaderBlob->Release();
	pcShaderBlob = NULL;

	return true;
}
//	ピクセルシェーダーにコンスタントバッファを設定
bool PixelShader::CreateConstantBuffer( int nBufferSize )
{
	ID3D11Device* pcDevice					= Device::GetDevice();
	ID3D11DeviceContext* pcDeviceContext	= Device::GetDeviceContext();

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC			m_cBufferDesc;		//!< 頂点バッファ設定情報(cbuffer設定用bufferDesc)

	//	コンスタントバッファの設定
	m_cBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;				// コンスタントバッファを動的に書き換えが可能にするフラグ
	m_cBufferDesc.ByteWidth			= nBufferSize;						// コンスタントバッファのサイズ
	m_cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;		// コンスタントバッファ用にバッファをバインドさせるためのフラグ
	m_cBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;			// コンスタントバッファをCPUからアクセスできるようにするかどうか
	m_cBufferDesc.MiscFlags			= 0;

	//	コンスタントバッファの作成
	hr = pcDevice->CreateBuffer( &m_cBufferDesc,NULL, &m_pcConstantBuffer );

	// コンスタントバッファ作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	return false;
}

//	頂点シェーダーにコンスタントバッファをセット
bool PixelShader::SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	HRESULT hr = S_OK;

	// コンスタントバッファが作成されていない
	if( !m_pcConstantBuffer )
	{
		return true;
	}

	D3D11_MAPPED_SUBRESOURCE	m_cMappedResource;	//!< 頂点シェーダー
	// コンスタントバッファに書き込めるように設定
	hr = pcDeviceContext->Map( 
		m_pcConstantBuffer,			//	データを書き込み用バッファ
		NULL,						
		D3D11_MAP_WRITE_DISCARD,	//　書き込めるようにフラグを設定
		NULL,
		&m_cMappedResource			//　データをマップさせるためのバッファ
		);

	//	 コンスタントバッファのマップに失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	CopyMemory( m_cMappedResource.pData, pData, nBufferSize );

	pcDeviceContext->UpdateSubresource(m_pcConstantBuffer, 0, 0, pData, 0, 0);

	// 書き込み禁止に設定
	pcDeviceContext->Unmap( m_pcConstantBuffer, NULL );

	
	pcDeviceContext->PSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return false;
}

//	頂点シェーダーにテクスチャをセット
bool PixelShader::SetTexture(Texture* pcTex,int nNum )
{
	// テクスチャがない
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->PSSetSamplers(nNum, 1, &pcSamplerState);
	pcDeviceContext->PSSetShaderResources(nNum, 1, &pcShederResource);

	return true;
}

//	作成できたシェーダーをデバイスコンテキストに設定
bool PixelShader::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();

	// ピクセルシェーダー
	if( m_pcPS )
	{
		pcDeviceContext->PSSetShader( m_pcPS, NULL, 0 );
	}	
	return true;
}

}	//	graphics	end
}	//	iruna		end