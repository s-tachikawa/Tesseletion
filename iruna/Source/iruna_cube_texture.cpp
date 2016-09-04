////---------------------------------------------------------
//// 
////	iruna_cube_texture.cpp
////	キューブテクスチャー管理クラス
////	作成日 6月28日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_cube_texture.h"
//#include "../Source/iruna_device.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
////	コンストラクタ
//CubeTexture::CubeTexture()
//	:	texture( 0 )
//{
//	return;
//}
//
////	デストラクタ
//CubeTexture::~CubeTexture()
//{
//	SafeRelease( texture );
//	return;
//}
//
//// テクスチャの読み込み
//bool CubeTexture::Load(std::string path, Color4 color, U_INT mipLevel, DWORD filter)
//{
//
//	if( FAILED( D3DXCreateCubeTextureFromFileEx(
//				Device::GetDevice(),
//				path.c_str(),
//				0,
//				mipLevel,
//				0,
//				D3DFMT_A8R8G8B8,
//				D3DPOOL_MANAGED,
//				filter,
//				filter,
//				color,
//				0,
//				0,
//				&texture
//		) ))
//	{
//		//	テクスチャの読み込みに失敗
//		return false;
//	}
//
//	//	読み込み成功
//	return true;
//}
//
//// テクスチャの解放
//void CubeTexture::Release()
//{
//	SafeRelease( texture );
//	recoveryPath.clear();
//	return;
//}
//
//// テクスチャの取得
//const LPDIRECT3DCUBETEXTURE9& CubeTexture::GetTexture()
//{
//	return texture;
//}
//
//// サーフェースの取得
//bool CubeTexture::GetSurface( U_INT num, Surface &surface )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	if( FAILED( texture->GetCubeMapSurface( (D3DCUBEMAP_FACES)num ,0, &temp ) ) )
//	{
//		return false;
//	}
//
//	surface	= temp;
//		
//	return true;
//
//}
//
//}	//	graphics	end
//}	//	iruna		end