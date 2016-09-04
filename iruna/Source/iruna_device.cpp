//---------------------------------------------------------
// 
//	iruna_device.cpp
//	デバイスの管理と生成
//	作成日 6月22日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_device.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_viewport.h"

/*----プリプロセッサディレクティブ---------------------------------*/
#ifdef _DEBUG
#pragma comment ( lib, "d3dx9d.lib"	)

#else
#pragma comment ( lib, "d3dx9.lib"	)

#endif

#pragma comment ( lib, "d3d9.lib"	) // DX9用ライブラリ
#pragma comment ( lib, "d3d11.lib"	) // DX9用ライブラリ
#pragma comment ( lib, "d3dx11.lib"	) // DX9用ライブラリ
#pragma comment ( lib,"d3dCompiler.lib")

#pragma comment ( lib, "d3dxof.lib"	)
#pragma comment ( lib, "dxguid.lib"	)
#pragma comment ( lib, "dxerr.lib"  )


/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// 静的メンバ変数の実体
ID3D11Device*			Device::m_pcDevice				= NULL;
ID3D11DeviceContext*	Device::m_pcDeviceContext		= NULL;
IDXGISwapChain*			Device::m_pcSwapChain			= NULL;
ID3D11RenderTargetView*	Device::m_pcRenderTargetView	= NULL;
ID3D11RasterizerState*	Device::m_pcRasterizestate		= NULL;
ID3D11DepthStencilView*	Device::m_pcDepthStencilView	= NULL;
ID3D11Texture2D*		Device::m_pcDepthStencil		= NULL;
D3D11_VIEWPORT			Device::m_sViewPort;
D3D11_RASTERIZER_DESC	Device::m_sRas;

//	コンストラクタ
Device::Device()
{
	return;
}

//	デストラクタ
Device::~Device()
{
	m_pcDeviceContext->ClearState();
	SafeRelease( m_pcDeviceContext );
	SafeRelease( m_pcSwapChain		);
	SafeRelease( m_pcRenderTargetView );
	SafeRelease( m_pcDevice );
	SafeRelease( m_pcRasterizestate );
	SafeRelease( m_pcDepthStencilView );
	return;
}

// デバイスとSwapChainを作成する
bool Device::Create( HWND hWindow, U_LONG width, U_LONG height, bool mode )
{
	HRESULT hr = S_OK;

	// ドライバータイプ宣言
	D3D_DRIVER_TYPE eDriverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,		// ハードウェア実装、一般的な実装はこれ
		D3D_DRIVER_TYPE_WARP,			// 高パフォーマンスのソフトウェア ラスタライザー,9_1 から 10.1 までの機能レベルしかできない。
		D3D_DRIVER_TYPE_REFERENCE,		// 高精度で機能を実装できが、低速なドライバー一般的ではない
	};
	// ドライバーの数
	UINT numDriverTypes = sizeof( eDriverTypes ) / sizeof( eDriverTypes[0] );

	// 機能レベルタイプの宣言
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,			// DirectX11の機能をターゲットにします。シェーダーモデル5.0
		D3D_FEATURE_LEVEL_10_1,			// DirectX10.1の機能をターゲットにします。シェーダーモデル4.0
		D3D_FEATURE_LEVEL_10_0,			// DirectX10の機能をターゲットにします。シェーダーモデル4.0
	};
	UINT numFeatureLevels = sizeof( featureLevels ) / sizeof( featureLevels[0] );

	//　スワップチェインの設定
	// スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );

	sd.BufferCount = 1;										// バックバッファの数
	sd.BufferDesc.Width = width;							// ウィンドウの横幅
	sd.BufferDesc.Height = height;							// ウィンドウの縦幅
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// 表示ピクセルのフォーマット32Bit色のRGBA
	sd.BufferDesc.RefreshRate.Numerator = 60;				// 垂直同期のフレームレート(分子）
	sd.BufferDesc.RefreshRate.Denominator = 1;				// 垂直同期のフレームレート(分母)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// レンダリングターゲットとしてこのバッファを使用するフラグ
	sd.OutputWindow = hWindow;								// ウィンドウハンドルの指定
	sd.SampleDesc.Count = 1;								// マルチサンプリング、アンチエイリアスに使用する何もしないので1ピクセルの色を決めるサンプリング数
	sd.SampleDesc.Quality = 0;								// マルチサンプリング、アンチエイリアスの精度レベル
	sd.Windowed = mode;										// ウィンドウモード
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// スワップチェインの機能追加フラグ、フルスクリーン、ウィンドウモードの切りかえをスムーズに行ってくれる。


	// デバイスとスワップチェインを作成する。
	for( int i = 0; i < ( int )numDriverTypes; i++ )
	{
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,							// ビデオアダプターのポインタ既定のアダプターを使用するであればNULLを指定
			eDriverTypes[ i ],				// ドライバータイプの指定
			NULL,							// ソフトウェアラスタライザーのDLLハンドルドライバーのタイプがソフトウェア以外ならNULLを指定
			0,								// レイヤーのタイプを指定デバッグレイヤーに設定すると大幅に速度が低下するらしいので設定しない
			featureLevels,					//	DirectXの機能レベル
			numFeatureLevels,				// 機能レベルの個数
			D3D11_SDK_VERSION,				// 使用するSDKのバージョン
			&sd,
			&m_pcSwapChain,
			&m_pcDevice,
			NULL,
			&m_pcDeviceContext				// デバイスコンテキストの設定
			);

		if ( SUCCEEDED( hr ) )
		{
			// 成功したらループ脱出
			break;
		}
	}
	// デバイスの作成失敗
	if ( FAILED( hr ) )
	{
		return false;
	}
	
	// バックバッファ用のテクスチャを作成
	ID3D11Texture2D* pcBackBuffer;
	hr = m_pcSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pcBackBuffer );
	// バックバッファの取得に失敗
	if( FAILED( hr ) )
	{
		return false;
	}
	// レンダリングターゲットビューを作成
	hr = m_pcDevice->CreateRenderTargetView( pcBackBuffer, NULL, &m_pcRenderTargetView );
	pcBackBuffer->Release();
	pcBackBuffer = NULL;
	
	// レンダリングターゲットの作成に失敗
	if( FAILED( hr ) )
	{
		return false;
	}
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
	
	m_pcDevice->CreateTexture2D( &sDepthDesc, NULL, &m_pcDepthStencil );

	D3D11_DEPTH_STENCIL_VIEW_DESC sDepthStencilViewDesc;
	sDepthStencilViewDesc.Format		= sDepthDesc.Format;
	sDepthStencilViewDesc.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2DMS;
	sDepthStencilViewDesc.Flags			= 0;

	m_pcDevice->CreateDepthStencilView( m_pcDepthStencil, &sDepthStencilViewDesc, &m_pcDepthStencilView );
	
	// レンダーターゲットをデバイスコンテキストにバインド
	m_pcDeviceContext->OMSetRenderTargets( 1, &m_pcRenderTargetView, m_pcDepthStencilView );
	// ビューポートの設定
	m_sViewPort.Width = (FLOAT)width;
	m_sViewPort.Height = (FLOAT)height;
	m_sViewPort.MinDepth = 0.0f;
	m_sViewPort.MaxDepth = 1.0f;
	m_sViewPort.TopLeftX = 0;
	m_sViewPort.TopLeftY = 0;
	// ビューポートをコンテキストに設定
	m_pcDeviceContext->RSSetViewports( 1, &m_sViewPort );

	//	ラスタライズの設定
	ZeroMemory( &m_sRas, sizeof( m_sRas ) );
	m_sRas.CullMode = D3D11_CULL_FRONT;
	//m_sRas.FillMode = D3D11_FILL_SOLID;
	m_sRas.FillMode = D3D11_FILL_WIREFRAME;
	m_sRas.FrontCounterClockwise = TRUE;
	m_sRas.DepthClipEnable = TRUE;
	m_sRas.ScissorEnable = FALSE;
	hr = m_pcDevice->CreateRasterizerState( &m_sRas, &m_pcRasterizestate );
	m_pcDeviceContext->RSSetState( m_pcRasterizestate );

	// ブレンドステートの作成
	D3D11_BLEND_DESC BlendStateDesc;
	BlendStateDesc.AlphaToCoverageEnable = FALSE;
	BlendStateDesc.IndependentBlendEnable = FALSE;

	for( int i = 0; i < 8; i++ )
	{
		BlendStateDesc.RenderTarget[ i ].BlendEnable				= TRUE;
		BlendStateDesc.RenderTarget[ i ].SrcBlend					= D3D11_BLEND_SRC_ALPHA;
		BlendStateDesc.RenderTarget[ i ].DestBlend					= D3D11_BLEND_INV_SRC_ALPHA;
		BlendStateDesc.RenderTarget[ i ].BlendOp					= D3D11_BLEND_OP_ADD;
		BlendStateDesc.RenderTarget[ i ].SrcBlendAlpha				= D3D11_BLEND_ONE;
		BlendStateDesc.RenderTarget[ i ].DestBlendAlpha				= D3D11_BLEND_ZERO;
		BlendStateDesc.RenderTarget[ i ].BlendOpAlpha				= D3D11_BLEND_OP_ADD;
		BlendStateDesc.RenderTarget[ i ].RenderTargetWriteMask		= D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	//	ブレンドステートの作成
	m_pcDevice->CreateBlendState(&BlendStateDesc, &m_pcBlendState);
	
	//	各色の成分の合成方法
	float blendFactor[4] = {D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO};
	//そのブレンディングをコンテキストに設定
	m_pcDeviceContext->OMSetBlendState( m_pcBlendState, blendFactor, 0xffffffff );
	return true;
}

// 裏画面をクリアし、描画を開始する(静的メンバ関数)
bool Device::ClearScreen( float r, float g, float b, float a )
{
	// バックバッファを何色に染めるか
	float clearColor[ 4 ];
	clearColor[ 0 ] = r;
	clearColor[ 1 ] = g;
	clearColor[ 2 ] = b;
	clearColor[ 3 ] = a;
	m_pcDeviceContext->ClearRenderTargetView( m_pcRenderTargetView, clearColor );
	m_pcDeviceContext->ClearDepthStencilView( m_pcDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
	return false;
}

// 指定したレンダーターゲットをクリア
bool Device::ClearBackBuffer(math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil)
{
	float clearColor[ 4 ];
	clearColor[ 0 ] = vColor.x;
	clearColor[ 1 ] = vColor.y;
	clearColor[ 2 ] = vColor.z;
	clearColor[ 3 ] = vColor.w;
	m_pcDeviceContext->ClearRenderTargetView( pcRenderTerget, clearColor );
	m_pcDeviceContext->ClearDepthStencilView( pcDepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
	return true;
}

// 描画を終了し、裏画面に描いたものを表画面へ転送(静的メンバ関数)
bool Device::SwapScreen()
{
	m_pcSwapChain->Present( 0, 0 );
	return false;
}

// デフォルトのレンダリングターゲットの取得(バックバッファの取得)
ID3D11RenderTargetView* Device::GetRenderTargetView()
{
	return m_pcRenderTargetView;
}

// デフォルトのデプスステンシルビューを取得
ID3D11DepthStencilView* Device::GetDepthStencilView()
{
	return m_pcDepthStencilView;
}

// デフォルトのビューポートを取得
D3D11_VIEWPORT* Device::GetViewPort()
{
	return &m_sViewPort;
}

// デフォルトのラスタライズの設定を取得
D3D11_RASTERIZER_DESC* Device::GetRasterizerState()
{
	return &m_sRas;
}

// デバイスを取得する(静的メンバ関数)
ID3D11Device* Device::GetDevice()
{
	return m_pcDevice;
}

// デバイスコンテキストを取得する(静的メンバ関数)
ID3D11DeviceContext* Device::GetDeviceContext()
{
	return m_pcDeviceContext;
}

}//	graphics	end
}//	iruna		end
