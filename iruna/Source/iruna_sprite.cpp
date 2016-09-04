////---------------------------------------------------------
//// 
////	iruna_sprite.cpp
////	2Dスプライト描画
////	作成日 6月24日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_sprite.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// 静的メンバ変数の実体
//VertexDeclaration	Sprite::declaration;
//
//// コンストラクタ
//Sprite::Sprite()
//{
//	// 頂点情報の初期化
//	for( int i = 0; i < 4; i++ )
//	{
//		data[ i ].position	= math::Vector4( 0.f, 0.f, 0.f, 1.f );
//		data[ i ].color		= Color4( 0xFFFFFFFF );
//	}
//
//	// UV座標の初期化
//	data[ 0 ].texcoord	= math::Vector2( 0.f, 0.f );
//	data[ 1 ].texcoord	= math::Vector2( 1.f, 0.f );
//	data[ 2 ].texcoord	= math::Vector2( 0.f, 1.f );
//	data[ 3 ].texcoord	= math::Vector2( 1.f, 1.f );
//
//	render	= new DeviceController;
//
//	// 頂点宣言
//	static VertexDeclaration::Element	element[] = {
//	// 頂点
//	{ 0, 0, D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT,	0 },
//	// カラー
//	{ 0,16, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
//	// uv座標
//	{ 0,20, D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
//
//	D3DDECL_END()
//	};
//
//	// 頂点宣言を元にデクラレーションデータの作成
//	declaration.Create( element );
//
//	return;
//}
//
//// デストラクタ
//Sprite::~Sprite()
//{
//	declaration.Release();
//
//	SafeDelete( render );
//
//	return;
//}
//
//// スプライトのサイズを設定する
//void Sprite::SetSize( math::Vector2 setSize )
//{
//	size	= setSize;
//
//	return;
//}
//
//// スプライトにテクスチャのどの部分を貼るか
//void Sprite::SetTexUV( math::RectF uvRect )
//{
//	data[ 0 ].texcoord	= math::Vector2( uvRect.left,	uvRect.top		);
//	data[ 1 ].texcoord	= math::Vector2( uvRect.right,	uvRect.top		);
//	data[ 2 ].texcoord	= math::Vector2( uvRect.left,	uvRect.bottom	);
//	data[ 3 ].texcoord	= math::Vector2( uvRect.right,	uvRect.bottom	);
//
//	return;
//}
//
//// スプライトの色を設定する
//void Sprite::SetColor( Color4 setColor )
//{
//	for( int i = 0; i < 4; i++ )
//		data[ i ].color	= setColor;
//
//	return;
//}
//
//// スプライトを表示する
//bool Sprite::Draw( math::Vector2 position )
//{
//	render->SetZBufferState( false );
//	declaration.Set();
//
//	data[ 0 ].position.x	= position.x;
//	data[ 0 ].position.y	= position.y;
//
//	data[ 1 ].position.x	= position.x + size.x;
//	data[ 1 ].position.y	= position.y;
//
//	data[ 2 ].position.x	= position.x;
//	data[ 2 ].position.y	= position.y + size.y;
//
//	data[ 3 ].position.x	= position.x + size.x;
//	data[ 3 ].position.y	= position.y + size.y;
//
//	bool	result	= render->DrawPrimitiveUp( Primitive::TRIANGLE_STRIP, 2, data, sizeof( Sprite::Data ) );
//
//	render->SetZBufferState( true );
//	return result;
//}
//
//}	//	graphics	end
//}	//	iruna		end