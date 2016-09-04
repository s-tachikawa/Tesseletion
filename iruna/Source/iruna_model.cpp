////---------------------------------------------------------
//// 
////	iruna_model.cpp
////	固定メッシュモデルクラス
////	作成日 6月27日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_model.h"
//#include "../Source/iruna_device.h"
//
//namespace iruna
//{
//namespace graphics
//{
//// コンストラクタ
//Model::Model()
//		:mesh			( 0 ),
//		material		( 0 ),
//		texture			( 0 ),
//		materialCount	( 0 )
//{
//	return;
//}
//
////	デストラクタ
//Model::~Model()
//{
//	SafeArrayDelete( material );
//	SafeArrayDelete( texture );
//	SafeRelease( mesh );
//	recoveryPath.clear();
//}
//
////	モデルの読み込み
//bool Model::Load( std::string path )
//{
//	LPD3DXBUFFER	materialTemp	= 0;
//	D3DXMATERIAL*	materialInfo	= 0;
//
//	if( FAILED( D3DXLoadMeshFromX(
//			path.c_str(),
//			D3DXMESH_SYSTEMMEM,
//			Device::GetDevice(),
//			0,
//			&materialTemp,
//			0,
//			&materialCount,
//			&mesh ) ) )
//	{
//		//	読み込み失敗
//		return false;
//	}
//
//	//	読み込んだXfileを元にモデルを構成
//	materialInfo	= reinterpret_cast< D3DXMATERIAL* >( materialTemp->GetBufferPointer() );
//	material		= new Material[ materialCount ];
//	texture			= new Texture[ materialCount ];
//	recoveryPath	= path;
//
//	//	マテリアルの数分だけマテリアルとテクスチャーを読み込む
//	for( U_LONG i = 0; i < materialCount; i++ )
//	{
//		material[ i ]			= materialInfo[ i ].MatD3D;
//		material[ i ].ambient	= Color4F( 1.f, 1.f, 1.f, 1.f );
//
//		if( materialInfo[ i ].pTextureFilename != NULL )
//		{
//			std::string	temp	= materialInfo[ i ].pTextureFilename;
//			path.erase( 1 + path.find_last_of( '/' ) );
//
//			texture[ i ].Load( ( path + temp ).c_str() );
//		}
//	}
//
//	SafeRelease( materialTemp );
//
//	//	読み込み成功
//	return true;
//}
//
////	モデルの描画
//bool Model::Draw( U_LONG count )
//{
//	return SUCCEEDED( mesh->DrawSubset( count ) );
//}
//
//bool Model::RemakeVertexFormat( const VertexDeclaration::Element* element )
//{
//	LPD3DXMESH meshTemp;
//
//	if( FAILED( mesh->CloneMesh( mesh->GetOptions(),
//								 element,
//								 Device::GetDevice(),
//								 &meshTemp ) ) )
//	{
//		//	頂点フォーマットの作成に失敗
//		return false;
//	}
//	SafeRelease( mesh );
//
//	//	新たに作成したメッシュをコピー
//	mesh	= meshTemp;
//
//	//	頂点フォーマットの再作成に成功
//	return true;
//}
//
////	マテリアルの数取得
//U_LONG Model::GetMaterialCount()
//{
//	return materialCount;
//}
//
//// マテリアルの取得
//const Material* Model::GetMaterial( U_LONG count )
//{
//	// マテリアルの数を超えていないか
//	if( count < materialCount )
//	{
//		return &material[ count ];
//	}
//	return 0;
//}
//
//// テクスチャーの取得
//const LPDIRECT3DTEXTURE9 Model::GetTexture( U_LONG count )
//{
//	// マテリアルの数を超えていないか
//	if( count < materialCount ) 
//	{
//		return texture[ count ].GetTexture();
//	}
//
//	return 0;
//}
//
//}
//}