//---------------------------------------------------------
// 
//	iruna_vertex_sheder.cpp
//	シェーダーファイル管理クラス
//	作成日 6月25日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_vertex_shader.h"
#include "../Include/iruna_vertex_declaration.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	コンストラクタ
VertexShader::VertexShader()
	:	m_pcVS( NULL ),
		m_pcShaderBlob( NULL )
{
	// バーテクスシェーダ
	m_eType = eVertexShader;
	return;
}

//	デストラクタ
VertexShader::~VertexShader()
{
	if( m_pcVS )
	{
		SafeRelease( m_pcVS );
	}
	if( m_pcShaderBlob )
	{
		SafeRelease( m_pcShaderBlob );
	}
}

//	頂点シェーダーの作成
bool VertexShader::CreateShader( std::string strShader,std::string strVertexEntry, eShaderVersion eVersion )
{
	// 頂点シェーダーのバージョン列挙
	const char* strVertexShaderVersion[] = 
	{
		"vs_1_0",
		"vs_1_1",
		"vs_2_0",
		"vs_3_0",
		"vs_4_0",
		"vs_5_0",
	};
	
	//	エラー出力用ボルブ
	ID3DBlob* pcErrorBlob;
	
	HRESULT hr = S_OK;
	
	hr = D3DX11CompileFromFile(
		strShader.c_str(),							//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,										//	シェーダー内でマクロを使用するときに使用
		NULL,										//	インクルードファイルを使用できるためのフラグ
		strVertexEntry.c_str(),						//	頂点シェーダーを実行するエントリーポイントの関数名
		strVertexShaderVersion[ eVersion ],			//	シェーダーモデル
		0,											//	シェーダーのコンパイルバージョンHLSLファイル
		0,											//	シェーダーのコンパイルバージョンFXファイル
		NULL,
		&m_pcShaderBlob,
		&pcErrorBlob,
		NULL
		);

	// シェーダー読み込み失敗
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
	//	頂点シェーダーの作成
	ID3D11Device* pcDevice = Device::GetDevice();
	hr = pcDevice->CreateVertexShader( 
				m_pcShaderBlob->GetBufferPointer(),
				m_pcShaderBlob->GetBufferSize(),
				NULL,
				&m_pcVS
				);

	// 頂点シェーダーの作成に失敗
	if( FAILED( hr ) )
	{
		return false;
	}
	return true;
}
//	バーテクスシェーダーにコンスタントバッファを設定
bool VertexShader::CreateConstantBuffer( int nBufferSize )
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
bool VertexShader::SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
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
	
	pcDeviceContext->VSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return false;
}

//	頂点シェーダーにテクスチャをセット
bool VertexShader::SetTexture( Texture* pcTex, int nNum )
{
	// テクスチャがない
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->VSSetSamplers(nNum, 1, &pcSamplerState);
	pcDeviceContext->VSSetShaderResources(nNum, 1, &pcShederResource);

	return true;
}

//	作成できたシェーダーをデバイスコンテキストに設定
bool VertexShader::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();

	// 頂点シェーダー
	if( m_pcVS )
	{
		pcDeviceContext->VSSetShader( m_pcVS, NULL, 0 );
	}	
	return true;
}

}	//	graphics	end
}	//	iruna		end