//---------------------------------------------------------
// 
//	iruna_color4.cpp
//	RGBAの色関係を扱う
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_color4.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// Color4 Union
// コンストラクタ(U_LONGで初期化するタイプ)
Color4::Color4( U_LONG setColor )
	: color( setColor )
{
	return;
}

// コンストラクタ(U_CHAR×4で初期化するタイプ)
Color4::Color4( U_CHAR r, U_CHAR g, U_CHAR b, U_CHAR a )
{
	channel[ ColorChannel::RED	 ]	= r;
	channel[ ColorChannel::GREEN ]	= g;
	channel[ ColorChannel::BLUE	 ]	= b;
	channel[ ColorChannel::ALPHA ]	= a;

	return;
}

// Color4F Struct
// コンストラクタ(全て0で初期化するタイプ)
Color4F::Color4F()
	: r( 0.f ),
	  g( 0.f ),
	  b( 0.f ),
	  a( 0.f )
{
	return;
}

// コンストラクタ(D3DCOLORVALUEで初期化するタイプ)
Color4F::Color4F( D3DCOLORVALUE colorValue )
	: r( colorValue.r ),
	  g( colorValue.g ),
	  b( colorValue.b ),
	  a( colorValue.a )
{
	return;
}

// コンストラクタ(一つずつ指定して初期化するタイプ)
Color4F::Color4F( float setR, float setG, float setB, float setA )
	: r( setR ),
	  g( setG ),
	  b( setB ),
	  a( setA )
{
	return;
}

}	//	graphics	end
}	//	iruna		end