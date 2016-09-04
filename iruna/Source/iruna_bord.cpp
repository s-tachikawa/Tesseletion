////---------------------------------------------------------
//// 
////	iruna_bord.cpp
////	板ポリのデフォルトクラス(派生してビルボードとかにする)
////	作成日 6月24日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_bord.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// 静的メンバ変数の実体
//VertexDeclaration	Board::declaration;
//
//// コンストラクタ
//Board::Board()
//{
//	// 頂点バッファクラスの確保
//	positionBuffer	= new VertexBuffer;
//	texcoordBuffer	= new VertexBuffer;
//	colorBuffer		= new VertexBuffer;
//	normalBuffer	= new VertexBuffer;
//
//	//	頂点バッファの生成
//	positionBuffer->Create( VertexBuffer::FLOAT3, 4 );
//	texcoordBuffer->Create( VertexBuffer::FLOAT2, 4 );
//	colorBuffer->Create(	VertexBuffer::COLOR,  4 );
//	normalBuffer->Create( 	VertexBuffer::FLOAT3, 4 );
//
//	// バックアップ用データを初期化
//	for( int i = 0; i < 4; i++ )
//	{
//		size[ i ]	= math::Vector3( 0.f, 0.f, 0.f );
//		color[ i ]	= Color4( 0xFFFFFFFF );
//	}
//	
//	// UV座標の初期化
//	texcoord[ 0 ]	= math::Vector2( 0.f, 0.f );
//	texcoord[ 1 ]	= math::Vector2( 1.f, 0.f );
//	texcoord[ 2 ]	= math::Vector2( 0.f, 1.f );
//	texcoord[ 3 ]	= math::Vector2( 1.f, 1.f );
//
//	// 法線
//	normal[ 0 ] = math::Vector3( 0, 0, -1 );
//	normal[ 1 ] = math::Vector3( 0, 0, -1 );
//	normal[ 2 ] = math::Vector3( 0, 0, -1 );
//	normal[ 3 ] = math::Vector3( 0, 0, -1 );
//
//	// 頂点バッファに値をセット
//	positionBuffer->SetBuffer( size,	 0, 4 );
//	texcoordBuffer->SetBuffer( texcoord, 0, 4 );
//	colorBuffer->SetBuffer(	   color,	 0, 4 );
//	normalBuffer->SetBuffer( normal, 0, 4 );
//
//	render	= new DeviceController;
//
//	// 頂点宣言
//	static VertexDeclaration::Element	element[] = {
//	// 頂点
//	{ 0, 0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
//	// 法線
//	{ 1, 0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0 },
//	// UV
//	{ 2, 0, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
//	// カラー
//	{ 3, 0, D3DDECLTYPE_D3DCOLOR,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,	0 },
//
//	D3DDECL_END()
//	};
//
//	// 設定した頂点宣言もとにデクラレーションを生成
//	declaration.Create( element );
//
//	return;
//}
//
//// デストラクタ(仮想関数)
//Board::~Board()
//{
//	declaration.Release();
//
//	SafeDelete( positionBuffer );
//	SafeDelete( texcoordBuffer );
//	SafeDelete( normalBuffer );
//	SafeDelete( colorBuffer	   );
//	SafeDelete( render		   );
//
//	return;
//}
//
//// 板ポリゴンのサイズを設定する(仮想関数)
//void Board::SetSize( math::Vector2 setSize )
//{
//	size[ 0 ]		= math::Vector3( -setSize.x / 2.f,  setSize.y / 2.f, 0.f );
//	size[ 1 ]		= math::Vector3(  setSize.x / 2.f,  setSize.y / 2.f, 0.f );
//	size[ 2 ]		= math::Vector3( -setSize.x / 2.f, -setSize.y / 2.f, 0.f );
//	size[ 3 ]		= math::Vector3(  setSize.x / 2.f, -setSize.y / 2.f, 0.f );
//
//	positionBuffer->SetBuffer( size, 0, 4 );
//
//	return;
//}
//
//// 板ポリゴンにテクスチャのどの部分を貼るか(仮想関数)
//void Board::SetTexUV( math::RectF uvRect )
//{
//	texcoord[ 0 ]	= math::Vector2( uvRect.left,	uvRect.top		);
//	texcoord[ 1 ]	= math::Vector2( uvRect.right,	uvRect.top		);
//	texcoord[ 2 ]	= math::Vector2( uvRect.left,	uvRect.bottom	);
//	texcoord[ 3 ]	= math::Vector2( uvRect.right,	uvRect.bottom	);
//
//	texcoordBuffer->SetBuffer( texcoord, 0, 4 );
//
//	return;
//}
//
//// 板ポリゴンの色を設定する(仮想関数)
//void Board::SetColor( Color4 setColor )
//{
//	for( int i = 0; i < 4; i++ )
//		color[ i ]	= setColor;
//
//	colorBuffer->SetBuffer( color, 0, 4 );
//
//	return;
//}
//
//// 板ポリゴンを表示する(仮想関数)
//bool Board::Draw()
//{
//	
//	declaration.Set();
//
//	positionBuffer->IntoStream( 0 );
//	normalBuffer->IntoStream( 1 );
//	colorBuffer->IntoStream( 3 );
//	texcoordBuffer->IntoStream( 2 );
//
//	return render->DrawPrimitive( Primitive::TRIANGLE_STRIP, 2 );
//}
//
//}	//	graphicd	end
//}	//	iruna		end