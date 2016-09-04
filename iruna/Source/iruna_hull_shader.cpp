//---------------------------------------------------------
// 
//	iruna_hull_sheder.cpp
//	シェーダーファイル管理クラス
//	作成日 1月14日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_hull_shader.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	コンストラクタ
HullShader::HullShader()
	:	m_pcHULL( NULL )
{
	m_eType = eHULLShader;
	return;
}

//	デストラクタ
HullShader::~HullShader()
{
	if( m_pcHULL )
	{
		SafeRelease( m_pcHULL );
	}
}

//	ピクセルシェーダーの作成
bool HullShader::CreateShader( std::string strShader,std::string strHullEntry, eShaderVersion eVersion )
{
	// ピクセルシェーダーのバージョン列挙
	const char* strHullShaderVersion[] = 
	{
		"hs_1_0",
		"hs_1_1",
		"hs_2_0",
		"hs_3_0",
		"hs_4_0",
		"hs_5_0",
	};

	//	エラー出力用ボルブ
	ID3DBlob* pcErrorBlob;
	ID3DBlob* pcShaderBlob;
	HRESULT hr = S_OK;

	//	シェーダーファイルを読み込んでコンパイル
	hr = D3DX11CompileFromFile(
		strShader.c_str(),						//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,									//	シェーダー内でマクロを使用するときに使用
		NULL,									//	インクルードファイルを使用できるためのフラグ
		strHullEntry.c_str(),					//	シェーダーを実行するエントリーポイントの関数名
		strHullShaderVersion[ eVersion ],		//	シェーダーモデル
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

	//	ハルシェーダーを作成
	ID3D11Device* pcDevice = Device::GetDevice();
	hr = pcDevice->CreateHullShader(
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcHULL
		);
	// ハルシェーダー作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}
//	ピクセルシェーダーにコンスタントバッファを設定
bool HullShader::CreateConstantBuffer( int nBufferSize )
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
bool HullShader::SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
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

	// 書き込み禁止に設定
	pcDeviceContext->Unmap( m_pcConstantBuffer, NULL );

	pcDeviceContext->HSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return false;
}

//	頂点シェーダーにテクスチャをセット
bool HullShader::SetTexture( Texture* pcTex, int nNum )
{
	// テクスチャがない
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->HSSetSamplers( 0, 1, &pcSamplerState );
	pcDeviceContext->HSSetShaderResources( 0, 1, &pcShederResource );

	return true;
}

//	作成できたシェーダーをデバイスコンテキストに設定
bool HullShader::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	if( m_pcHULL )
	{
		pcDeviceContext->HSSetShader( m_pcHULL, NULL, 0 );
	}	
	return true;
}

}	//	graphics	end
}	//	iruna		end