//---------------------------------------------------------
// 
//	iruna_texture.cpp
//	テクスチャーの管理
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_texture.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
Texture::Texture()
	:	m_pcTexture( NULL ),
		m_pcSampleLinear( NULL ),
		m_pcDynamicTexture( NULL ),
		m_pcRenderTargetView( NULL ),
		m_pcDepthStencilView( NULL ),
		m_pcDepthStencil( NULL )
{
	return;	
}

// デストラクタ
Texture::~Texture()
{
	SafeRelease( m_pcTexture );
	SafeRelease( m_pcSampleLinear );

	// 動的テクスチャとして作成されているのであれば解放する
	if( m_pcDynamicTexture )
	{
		SafeRelease( m_pcDynamicTexture );
	}
	if( m_pcRenderTargetView )
	{
		SafeRelease( m_pcRenderTargetView );
	}
	if( m_pcDepthStencil )
	{
		SafeRelease( m_pcDepthStencil );
	}
	if( m_pcDepthStencilView )
	{
		SafeRelease( m_pcDepthStencilView );
	}
	

	return;
}

// 画像ファイルからテクスチャを読み込む
bool Texture::Load( std::string path, Color4 color, U_INT mipLevel, DWORD filter )
{
	// テクスチャの読み込み設定
	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	LoadInfo.Width = 0;									//	読み込むテクスチャの幅0に設定するとそのテクスチャの大きさになる？
	LoadInfo.Height = 0;								//	読み込むテクスチャの高さ0に設定するとそのテクスチャの大きさになる？
	LoadInfo.Depth = 0;									//	デプスの深度設定ボリュームテクスチャのときにしか適用できない
	LoadInfo.FirstMipLevel = 0;							//	ミップマップレベル最高値の設定
	LoadInfo.MipLevels = D3DX11_DEFAULT,				//	テクスチャ内のミップマップレベル数の設定
	LoadInfo.Usage = D3D11_USAGE_DEFAULT;				//	テクスチャの使用方法の設定
	LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//	デバイスコンテキストのバインド設定
	LoadInfo.CpuAccessFlags = 0;						//	CPUアクセスの設定
	LoadInfo.MiscFlags = 0;								//	リソースプロパティの設定
	LoadInfo.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	//	テクスチャフォーマットの設定
	LoadInfo.Filter = D3DX11_FILTER_TRIANGLE;			//	テクスチャのフィルター設定
	LoadInfo.MipFilter = D3DX11_FILTER_TRIANGLE;		//	設定したフィルターでミップマップをフィルタリングするフラグ
	LoadInfo.pSrcInfo = NULL;							//	オリジナルイメージのリソース


	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
				Device::GetDevice(),
				path.c_str(),
				&LoadInfo,
				NULL,
				&m_pcTexture,
				NULL) ) )
	{
		return false;
	}

	recoveryPath	= path;

	return true;
}

// テクスチャのサプラーステート
bool Texture::CreateSamplerSate()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC sSamDesc;
	ZeroMemory(&sSamDesc,sizeof(D3D11_SAMPLER_DESC));

	sSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sSamDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sSamDesc.MinLOD = 0;
	sSamDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// サンプラーステート作成
	pcDevice->CreateSamplerState( &sSamDesc, &m_pcSampleLinear );

	return false;
}

// カラの動的テクスチャを作成する
bool Texture::CreateTexture( U_INT width, U_INT height, DWORD usage, U_INT mipLevel, DXGI_FORMAT eFormat )
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// 2次元テクスチャの設定
	D3D11_TEXTURE2D_DESC sTexDesc;
	memset( &sTexDesc, 0, sizeof( sTexDesc ) );
	sTexDesc.Usage              = D3D11_USAGE_DEFAULT;
	sTexDesc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	sTexDesc.BindFlags          = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	sTexDesc.Width              = width;
	sTexDesc.Height             = height;
	sTexDesc.CPUAccessFlags     = 0;
	sTexDesc.MipLevels          = 1;
	sTexDesc.ArraySize          = 1;
	sTexDesc.SampleDesc.Count   = 1;
	sTexDesc.SampleDesc.Quality = 0;

	hr = pcDevice->CreateTexture2D( &sTexDesc, NULL, &m_pcDynamicTexture );

	// テクスチャの作成に失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	bool bSuccess = CreateRenderTerget();

	// レンダーターゲットの作成に失敗
	if( !bSuccess )
	{
		return false;
	}

	//	シェーダーリソースの作成
	bSuccess = CreateShaderResourceView();
	
	//　シェーダーリソースの作成に失敗
	if( !bSuccess )
	{
		return false;
	}

	bSuccess = CreateDepthStecil( width, height );
	// デプスステンシルの作成に失敗
	if( !bSuccess )
	{
		return false;
	}

	// 動的なテクスチャの作成に成功
	return true;
	
}

//	レンダーターゲットの作成
bool Texture::CreateRenderTerget()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// 動的なテクスチャが作成されていない
	if( !m_pcDynamicTexture )
	{
		return false;
	}

	// レンダーターゲットビューの設定
	D3D11_RENDER_TARGET_VIEW_DESC sRenderTergetDesc;
	memset( &sRenderTergetDesc, 0, sizeof( sRenderTergetDesc ) );
	sRenderTergetDesc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	sRenderTergetDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;

	// レンダーターゲットの作成
	hr = pcDevice->CreateRenderTargetView( m_pcDynamicTexture, &sRenderTergetDesc, &m_pcRenderTargetView );

	if( FAILED( hr ) )
	{
		return false;
	}

	return true;

}

// デプスステンシルの作成
bool Texture::CreateDepthStecil( U_INT width, U_INT height )
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	//	デプスステンシルビューの作成
	D3D11_TEXTURE2D_DESC sDepthDesc;
	sDepthDesc.Width					= width;
	sDepthDesc.Height					= height;
	sDepthDesc.MipLevels				= 1;
	sDepthDesc.ArraySize				= 1;
	sDepthDesc.Format					= DXGI_FORMAT_D24_UNORM_S8_UINT;
	sDepthDesc.SampleDesc.Count			= 1;
	sDepthDesc.SampleDesc.Quality		= 0;
	sDepthDesc.Usage					= D3D11_USAGE_DEFAULT;
	sDepthDesc.BindFlags				= D3D11_BIND_DEPTH_STENCIL;
	sDepthDesc.CPUAccessFlags			= 0;
	sDepthDesc.MiscFlags				= 0;

	hr = pcDevice->CreateTexture2D( &sDepthDesc, NULL, &m_pcDepthStencil );

	// デプスステンシル用テクスチャの作成に失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC sDepthStencilViewDesc;
	sDepthStencilViewDesc.Format		= sDepthDesc.Format;
	sDepthStencilViewDesc.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2DMS;
	sDepthStencilViewDesc.Flags			= 0;

	hr = pcDevice->CreateDepthStencilView( m_pcDepthStencil, &sDepthStencilViewDesc, &m_pcDepthStencilView );

	// デプスステンシルビューの作成に失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}

// シェーダーリソースビューの作成
bool Texture::CreateShaderResourceView()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// 動的なテクスチャが作成されていない
	if( !m_pcDynamicTexture )
	{
		return false;
	}

	// シェーダリソースビューの設定
	D3D11_SHADER_RESOURCE_VIEW_DESC sShaderResourceDesc;
	memset( &sShaderResourceDesc, 0, sizeof( sShaderResourceDesc ) );
	sShaderResourceDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	sShaderResourceDesc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
	sShaderResourceDesc.Texture2D.MipLevels = 1;

	hr = pcDevice->CreateShaderResourceView( m_pcDynamicTexture, &sShaderResourceDesc, &m_pcTexture );

	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}
// テクスチャを解放する
void Texture::Release()
{
	
	SafeRelease( m_pcSampleLinear );
	recoveryPath.clear();
	SafeRelease( m_pcTexture );
	
	// 動的なテクスチャが作成されていれば解放
	if( m_pcDynamicTexture )
	{
		SafeRelease( m_pcDynamicTexture );
	}
	if( m_pcRenderTargetView )
	{
		SafeRelease( m_pcRenderTargetView );
	}

	return;
}

// テクスチャをロックし、アクセスするためのLockedRectを返す(動的テクスチャのみ)
bool Texture::Lock( LockedRect &rect, DWORD flag )
{
	//return SUCCEEDED( texture->LockRect( 0, &rect, 0, flag ) );
	return true;
}

// テクスチャをアンロックし、アクセスできないようにする(動的テクスチャのみ)
bool Texture::Unlock()
{
	//return SUCCEEDED( texture->UnlockRect( 0 ) );
	return true;
}

// テクスチャを取得
ID3D11ShaderResourceView* const Texture::GetTexture()
{
	return m_pcTexture;
}

// テクスチャサンプラーステートを取得
ID3D11SamplerState* const Texture::GetSamplerState()
{
	return m_pcSampleLinear;
}
// レンダーターゲットの取得
ID3D11RenderTargetView*	const Texture::GetRenderTerget()
{
	return m_pcRenderTargetView;
}

// デプスステンシルビューの取得
ID3D11DepthStencilView*	const Texture::GetDepthStencil()
{
	return m_pcDepthStencilView;
}

// テクスチャのサイズを取得
POINT Texture::GetSize()
{
	POINT				temp;
	ZeroMemory( &temp, sizeof( temp ) );
	//D3DSURFACE_DESC		desc;
	//texture->GetLevelDesc( 0, &desc );

	//temp.x	= desc.Width;
	//temp.y	= desc.Height;

	//return temp;
	return temp;
}

}	//	graphics	end
}	//	iruna		end