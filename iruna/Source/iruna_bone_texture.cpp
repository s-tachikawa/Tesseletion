//
///*----インクルード------------------------------------------------*/
//#include "../Include/iruna_bone_texture.h"
//#include "../Include/iruna_math.h"
//
///*----データ型-------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
////	コンストラクタ
//BoneTexture::BoneTexture()
//:		tran( NULL ),
//		rot( NULL ),
//		tranRt( NULL ),
//		rotRt( NULL ),
//		render( NULL )
//{
//	render	= new DeviceController;
//	tran	= new Texture;
//	rot		= new Texture;
//	tranRt	= new Surface;
//	rotRt	= new Surface;
//	
//
//
//	tran->GetSurface( ( *tranRt ) );
//	rot->GetSurface( ( *rotRt ) );
//
//	width = 0;
//	height = 0;
//
//	return;
//}
//
////	デストラクタ
//BoneTexture::~BoneTexture()
//{
//	SafeDelete( tran );
//	SafeDelete( rot );
//	SafeDelete( tranRt );
//	SafeDelete( rotRt );
//	SafeDelete( render );
//	return;
//}
////	ウィンドウサイズの設定
//void BoneTexture::SetWindowSize( int in_width, int in_height )
//{
//	width = in_width;
//	height = in_height;
//
//	return;
//}
//
////	テクスチャの更新
//void BoneTexture::TextureUpDate( math::Matrix* skinData )
//{
//	
//	int boneNum = sizeof( *skinData ) / sizeof( math::Matrix );
//
//	//	ボーンの数からテクスチャサイズを設定
//	//	MRTでやるため縦は1横はボーン数でピクセル数を合わせる
//	tran->Create( boneNum, 1, D3DUSAGE_RENDERTARGET );
//	rot->Create( boneNum, 1, D3DUSAGE_RENDERTARGET );
//	
//	Surface			backBuffer;		
//	Viewport		oldViewport;	
//	Viewport		newViewport;	
//	
//	newViewport.SetSize( 0, 0, width, height );
//
//	Surface		oldDepthTarget;
//	Surface		newDepthTarget;
//
//	newDepthTarget.CreateDepth( width, height,Surface::Z_D16 );
//
//	GetViewport( oldViewport );
//	GetBackBuffer( backBuffer );
//	GetDepthTarget( oldDepthTarget );
//
//	//	差し替え
//	newDepthTarget.SetDepthTarget();
//	newViewport.SetViewport();
//	tranRt->SetRenderTarget( 0 );
//	rotRt->SetRenderTarget( 1 );
//
//	return;
//}
//
////	平行移動成分テクスチャの取得
//Texture* BoneTexture::GetTransTexture()
//{
//	return tran;
//}
//
//Texture* BoneTexture::GetRotTexture()
//{
//	return rot;
//}
//
//}	//	graphics	end
//}	//	iruna		end