//---------------------------------------------------------
// 
//	iruna_efect.cpp
//	シェーダーファイル管理クラス
//	作成日 6月25日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_efect.h"
#include "../Source/iruna_device.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_vertex_declaration.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	コンストラクタ
Effect::Effect()
	:	m_pcVS( NULL ),
		m_pcVertexBlob( NULL ),
		m_pcConstantBuffer( NULL ),
		m_pcGS( NULL ),
		m_pcPS( NULL ),
		m_pcHull( NULL ),
		m_pcDomain( NULL ),
		m_pcDomainBlob( NULL ),
		m_pcDomainConstantBuffer( NULL )
{
	return;
}

//	デストラクタ
Effect::~Effect()
{
	if( m_pcVS )
	{
		SafeRelease( m_pcVS );
	}
	if( m_pcGS )
	{
		SafeRelease( m_pcGS );
	}
	if( m_pcPS )
	{
		SafeRelease( m_pcPS );
	}
	if( m_pcConstantBuffer )
	{
		SafeRelease( m_pcConstantBuffer );
	}
	if( m_pcDomain )
	{
		SafeRelease( m_pcDomain );
	}
	if( m_pcHull )
	{
		SafeRelease( m_pcHull );
	}
	if( m_pcDomainBlob )
	{
		SafeRelease( m_pcDomainBlob );
	}
	if( m_pcDomainConstantBuffer )
	{
		SafeRelease( m_pcDomainConstantBuffer );
	}
}

//	頂点シェーダーの作成
bool Effect::CreateVertexShader( std::string strShader,std::string strVertexEntry, eShaderVersion eVersion )
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
		&m_pcVertexBlob,
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
				m_pcVertexBlob->GetBufferPointer(),
				m_pcVertexBlob->GetBufferSize(),
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
bool Effect::CreateVertexConstantBuffer( int nBufferSize )
{
	ID3D11Device* pcDevice					= Device::GetDevice();
	ID3D11DeviceContext* pcDeviceContext	= Device::GetDeviceContext();
	
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC			m_cBufferDesc;		//!< 頂点バッファ設定情報(cbuffer設定用bufferDesc)

	//	コンスタントバッファの設定
	m_cBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;						// コンスタントバッファを動的に書き換えが可能にするフラグ
	m_cBufferDesc.ByteWidth			= nBufferSize;							// コンスタントバッファのサイズ
	m_cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;			// コンスタントバッファ用にバッファをバインドさせるためのフラグ
	m_cBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;			// コンスタントバッファをCPUからアクセスできるようにするかどうか
	m_cBufferDesc.MiscFlags			= 0;

	//	コンスタントバッファの作成
	hr = pcDevice->CreateBuffer( &m_cBufferDesc,NULL, &m_pcConstantBuffer );

	// コンスタントバッファ作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}

//	頂点シェーダーにコンスタントバッファをセット
bool Effect::SetVertexConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
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

	pcDeviceContext->VSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return true;
}
//	ピクセルシェーダーの作成
bool Effect::CreatePixelShader( std::string strShader,std::string strPixelEntry, eShaderVersion eVersion )
{
	// 頂点シェーダーのバージョン列挙
	const char* strVertexShaderVersion[] = 
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
		strShader.c_str(),							//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,									//	シェーダー内でマクロを使用するときに使用
		NULL,									//	インクルードファイルを使用できるためのフラグ
		strPixelEntry.c_str(),							//	ピクセルシェーダーを実行するエントリーポイントの関数名
		strVertexShaderVersion[ eVersion ],		//	シェーダーモデル
		0,			//	シェーダーのコンパイルバージョンHLSLファイル
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
//	ピクセルシェーダーにテクスチャをセット
bool Effect::SetTexture( Texture* pcTex )
{
	// テクスチャがない
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->PSSetSamplers( 0, 1, &pcSamplerState );
	pcDeviceContext->PSSetShaderResources( 0, 1, &pcShederResource );

	return true;
}
//	ジオメトリーシェーダー作成
bool Effect::CreateGeometryShader( std::string strShader,std::string strGeometryEntry, eShaderVersion eVersion )
{
	// 頂点シェーダーのバージョン列挙
	const char* strVertexShaderVersion[] = 
	{
		"gs_1_0",
		"gs_1_1",
		"gs_2_0",
		"gs_3_0",
		"gs_4_0",
		"gs_5_0",
	};

	//	エラー出力用ボルブ
	ID3DBlob* pcErrorBlob;

	HRESULT hr = S_OK;

	ID3DBlob* pcShaderBlob = NULL;

	hr = D3DX11CompileFromFile(
		strShader.c_str(),							//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,									//	シェーダー内でマクロを使用するときに使用
		NULL,									//	インクルードファイルを使用できるためのフラグ
		strGeometryEntry.c_str(),							//	ジオメトリシェーダーを実行するエントリーポイントの関数名
		strVertexShaderVersion[ eVersion ],		//	シェーダーモデル
		D3DCOMPILE_ENABLE_STRICTNESS,			//	シェーダーのコンパイルバージョンHLSLファイル
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

	//	ジオメトリーシェーダー作成
	ID3D11Device* pcDevice = Device::GetDevice();

	pcDevice->CreateGeometryShader( 
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcGS
		);

	//	ジオメトリシェーダー作成成功
	pcShaderBlob->Release();
	pcShaderBlob = NULL;

	return true;
}

//	ハルシェーダーの作成
bool Effect::CreateHullShader( std::string path, std::string strHullEntry, eShaderVersion eVersion )
{
	// ハルシェーダーのバージョン列挙
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

	HRESULT hr = S_OK;

	ID3DBlob* pcShaderBlob = NULL;

	hr = D3DX11CompileFromFile(
		path.c_str(),							//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,									//	シェーダー内でマクロを使用するときに使用
		NULL,									//	インクルードファイルを使用できるためのフラグ
		strHullEntry.c_str(),					//	ジオメトリシェーダーを実行するエントリーポイントの関数名
		strHullShaderVersion[ eVersion ],		//	シェーダーモデル
		D3DCOMPILE_ENABLE_STRICTNESS,			//	シェーダーのコンパイルバージョンHLSLファイル
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

	//	ジオメトリーシェーダー作成
	ID3D11Device* pcDevice = Device::GetDevice();

	pcDevice->CreateHullShader( 
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcHull
		);

	//	ジオメトリシェーダー作成成功
	pcShaderBlob->Release();
	pcShaderBlob = NULL;
	return true;
}

//	ドメインシェーダーの作成
bool Effect::CreateDomainShader( std::string path, std::string strDomainEntry, eShaderVersion eVersion )
{
	// ハルシェーダーのバージョン列挙
	const char* strDomainShaderVersion[] = 
	{
		"ds_1_0",
		"ds_1_1",
		"ds_2_0",
		"ds_3_0",
		"ds_4_0",
		"ds_5_0",
	};

	//	エラー出力用ボルブ
	ID3DBlob* pcErrorBlob;

	HRESULT hr = S_OK;

	hr = D3DX11CompileFromFile(
		path.c_str(),							//	シェーダーファイル名　シェーダはhlsl,fxファイルの2種類
		NULL,									//	シェーダー内でマクロを使用するときに使用
		NULL,									//	インクルードファイルを使用できるためのフラグ
		strDomainEntry.c_str(),					//	シェーダーを実行するエントリーポイントの関数名
		strDomainShaderVersion[ eVersion ],		//	シェーダーモデル
		D3DCOMPILE_ENABLE_STRICTNESS,			//	シェーダーのコンパイルバージョンHLSLファイル
		0,										//	シェーダーのコンパイルバージョンFXファイル
		NULL,
		&m_pcDomainBlob,
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

	//	ジオメトリーシェーダー作成
	ID3D11Device* pcDevice = Device::GetDevice();

	pcDevice->CreateDomainShader( 
		m_pcDomainBlob->GetBufferPointer(),
		m_pcDomainBlob->GetBufferSize(),
		NULL,
		&m_pcDomain
		);

	return true;
}

//	ドメインシェーダー用コンスタントバッファを作成
bool Effect::CreateDomainConstantBuffer( int nBufferSize )
{
	ID3D11Device* pcDevice					= Device::GetDevice();
	ID3D11DeviceContext* pcDeviceContext	= Device::GetDeviceContext();

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC			m_cBufferDesc;		//!< 頂点バッファ設定情報(cbuffer設定用bufferDesc)

	//	コンスタントバッファの設定
	m_cBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;					// コンスタントバッファを動的に書き換えが可能にするフラグ
	m_cBufferDesc.ByteWidth			= nBufferSize;							// コンスタントバッファのサイズ
	m_cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;			// コンスタントバッファ用にバッファをバインドさせるためのフラグ
	m_cBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;				// コンスタントバッファをCPUからアクセスできるようにするかどうか
	m_cBufferDesc.MiscFlags			= 0;

	//	コンスタントバッファの作成
	hr = pcDevice->CreateBuffer( &m_cBufferDesc,NULL, &m_pcDomainConstantBuffer );

	// コンスタントバッファ作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}

//	ドメインシェーダー用コンスタントバッファに変数を設定
bool Effect::SetDomainConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	HRESULT hr = S_OK;

	// コンスタントバッファが作成されていない
	if( !m_pcDomainConstantBuffer )
	{
		return true;
	}

	D3D11_MAPPED_SUBRESOURCE	m_cMappedResource;	//!< 頂点シェーダー
	// コンスタントバッファに書き込めるように設定
	hr = pcDeviceContext->Map( 
		m_pcDomainConstantBuffer,	//	データを書き込み用バッファ
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
	pcDeviceContext->Unmap( m_pcDomainConstantBuffer, NULL );

	pcDeviceContext->DSSetConstantBuffers( nRegisterNum, 1, &m_pcDomainConstantBuffer );

	return true;
}

//	作成できたシェーダーをデバイスコンテキストに設定
bool Effect::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	
	// 各シェーダーが作成されていれば設定する
	
	// 頂点シェーダー
	if( m_pcVS )
	{
		pcDeviceContext->VSSetShader( m_pcVS, NULL, 0 );
	}
	// ピクセルシェーダー
	if( m_pcPS )
	{
		pcDeviceContext->PSSetShader( m_pcPS, NULL, 0 );
	}
	// ジオメトリーシェーダーのセット
	if( m_pcGS )
	{
		pcDeviceContext->GSSetShader( m_pcGS, NULL, 0);
	}
	// ハルシェーダーの設定
	if( m_pcHull )
	{
		pcDeviceContext->HSSetShader( m_pcHull, NULL, 0 );
	}
	// ドメインシェーダーの設定
	if( m_pcDomain )
	{
		pcDeviceContext->DSSetShader( m_pcDomain, NULL, 0 );
	}
	
	return true;
}

}	//	graphics	end
}	//	iruna		end