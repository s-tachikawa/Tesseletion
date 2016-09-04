////---------------------------------------------------------
//// 
////	iruna_surface.cpp
////	サーフェース関連
////	作成日 6月23日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_surface.h"
//#include "../Source/iruna_device.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// コンストラクタ(初期化するだけ)
//Surface::Surface()
//	: surface( 0 )
//{
//	return;
//}
//
//// コピーコンストラクタ、参照カウントをインクリメントする
//Surface::Surface( const Surface& another )
//	: surface( another.surface )
//{
//	surface->AddRef();
//
//	return;
//}
//
//// デストラクタ、参照カウントをデクリメントする
//Surface::~Surface()
//{
//	SafeRelease( surface );
//
//	return;
//}
//
//// Zバッファを作成する
//bool Surface::CreateDepth( U_INT width, U_INT height, Z_Format format )
//{
//	// Zバッファサイズのテーブル
//	static const D3DFORMAT Z_SIZE[] = {
//		D3DFMT_D16,		// Z_D16
//		D3DFMT_D32,		// Z_D32
//	};
//
//	return SUCCEEDED( Device::GetDevice()->CreateDepthStencilSurface(
//							width,
//							height,
//							Z_SIZE[ format ],
//							D3DMULTISAMPLE_NONE,
//							0,
//							true, // SetDepthTargetで変更したときに破棄するか？
//							&surface,
//							0 ) );
//}
//
//// 裏画面の描き込み先をこのサーフェスにする
//bool Surface::SetRenderTarget( U_LONG index )
//{
//	return SUCCEEDED( Device::GetDevice()->SetRenderTarget( index, surface ) );
//}
//
//// Zバッファの描き込み先をこのサーフェスにする
//bool Surface::SetDepthTarget()
//{
//	return SUCCEEDED( Device::GetDevice()->SetDepthStencilSurface( surface ) );
//}
//
//// 代入演算子オーバーロード、LPDIRECT3DSURFACE9をつっこめるように
//Surface& Surface::operator =( LPDIRECT3DSURFACE9 setSurface )
//{
//	surface		= setSurface;
//
//	return *this;
//}
//
//}	// graphics	end
//}	// iruna	end
//
///*----グローバル関数 定義----------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// 裏画面のサーフェスを取得する
//bool GetRenderTarget( Surface& surface, U_LONG index )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	if( FAILED( Device::GetDevice()->GetRenderTarget(
//									index,
//									&temp ) ) )
//		return false;
//
//	surface	= temp;
//
//	return true;
//}
//// 指定したレンダーターゲットの初期化
//bool SetRenderTargetFormat( U_LONG target )
//{
//	return SUCCEEDED( Device::GetDevice()->SetRenderTarget( target ,NULL ) );
//}
//
//// Zバッファのサーフェスを取得する
//bool GetDepthTarget( Surface& surface )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	// Zバッファの取得に失敗
//	if( FAILED( Device::GetDevice()->GetDepthStencilSurface(
//									&temp ) ) )
//		return false;
//
//	surface	= temp;
//
//	return true;
//}
//bool GetBackBuffer( Surface& back_buffer )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	// バックバッファの取得に失敗
//	if( FAILED( Device::GetDevice()->GetBackBuffer(
//										0,
//										0,
//										D3DBACKBUFFER_TYPE_MONO,
//										&temp ) ) )
//	{
//		return false;
//	}
//
//	back_buffer	= temp;
//
//	return true;
//}
//
//}	//	graphics	end
//}	//	iruna		end