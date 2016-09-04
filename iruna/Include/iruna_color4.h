//*********************************************************************
/*!
	@file	white_color4.h
	@brief	a,r,g,bの色を扱う
	@author	立川 翔野
	@date	2011/06/23	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_COLOR4_H
#define IRUNA_COLOR4_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	ColorChannel
//! @brief	RED BULE GREEN ALPHAを指定するための一覧
//!
//!=====================================================================
struct ColorChannel
{
//	パブリック	型定義
public:
	enum Type{
		BLUE,
		GREEN,
		RED,
		ALPHA,
		MAX
	};
};

//!=====================================================================
//!
//! @union	Color4
//! @brief	整数型のRED BULE GREEN ALPHAを扱う共用体
//!
//!=====================================================================
union Color4
{
//	パブリック	メンバ変数
public:
	U_CHAR	channel[ ColorChannel::MAX ];	//!< 1色ずつほしい用
	U_LONG	color;							//!< 全部まとめてほしい用

//	パブリック	メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(U_LONGで初期化するタイプ)
	//! @param	[in] setColor	- この色で初期化する
	//! 
	//!--------------------------------------------------------------------
	Color4( U_LONG setColor = 0 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(U_CHAR×4で初期化するタイプ)
	//! @param	[in] r	- レッドはこれで初期化する
	//! @param	[in] g	- グリーンはこれで初期化する
	//! @param	[in] b	- ブルーはこれで初期化する
	//! @param	[in] a	- アルファはこれで初期化する
	//! 
	//!--------------------------------------------------------------------
	Color4( U_CHAR r, U_CHAR g, U_CHAR b, U_CHAR a = 255 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	引数がU_LONGなところにつっこむとU_LONGとして扱われる
	//! @retval	U_LONG型の色(4色まとめて)
	//! 
	//!--------------------------------------------------------------------
	inline	operator U_LONG() const;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	配列の添え字アクセスのように一色ずつ色を取得する
	//! @retval	U_CHAR型の色(1色だけ)
	//! 
	//!--------------------------------------------------------------------
	inline const U_CHAR&	operator []( UINT getChannel ) const;
};

// インラインメンバ関数の実装
// 引数がU_LONGなところにつっこむとU_LONGとして扱われる
inline Color4::operator U_LONG() const
{
	return color;
}

// 配列の添え字アクセスのように一色ずつ色を取得する
inline const U_CHAR& Color4::operator []( UINT getChannel ) const
{
	return channel[ getChannel ];
}

//!=====================================================================
//!
//! @struct	Color4F
//! @brief	浮動小数点型のRED BULE GREEN ALPHAを扱う構造体
//!
//!=====================================================================
struct Color4F
{
// パブリック		メンバ変数
public:
	float	r;	//!< 赤
	float	g;	//!< 緑
	float	b;	//!< 青
	float	a;	//!< 透明度

// パブリック		メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(全て0で初期化するタイプ)
	//! 
	//!--------------------------------------------------------------------
	Color4F();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(D3DCOLORVALUEで初期化するタイプ)
	//! 
	//!--------------------------------------------------------------------
	Color4F( D3DCOLORVALUE colorValue );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(一つずつ指定して初期化するタイプ)
	//! @param	[in] setR	- レッドはこれで初期化する
	//! @param	[in] setG	- グリーンはこれで初期化する
	//! @param	[in] setB	- ブルーはこれで初期化する
	//! @param	[in] setA	- アルファはこれで初期化する
	//! 
	//!--------------------------------------------------------------------
	Color4F( float setR, float setG, float setB, float setA );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	引数がD3DCOLORVALUEなところにつっこむとD3DCOLORVALUEとして扱われる
	//! @retval	D3DCOLORVALUE型
	//! 
	//!--------------------------------------------------------------------
	inline	operator D3DCOLORVALUE() const;
};

// インラインメンバ関数の実装
// 引数がD3DCOLORVALUEなところにつっこむとD3DCOLORVALUEとして扱われる
inline Color4F::operator D3DCOLORVALUE() const
{
	D3DCOLORVALUE	temp;

	temp.r	= r;
	temp.g	= g;
	temp.b	= b;
	temp.a	= a;

	return temp;
}


}	// graphics	end
}	// iruna	end

/*----関数 宣言----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!--------------------------------------------------------------------
//! 
//! @brief	Color4FからColor4に変換する
//! @param	[in] colorValue	- 変換したいColor4F
//! @retval	Color4になった色
//! 
//!--------------------------------------------------------------------
inline const Color4 ToColor4( const Color4F& colorValue )
{
	return Color4( static_cast< U_CHAR >( colorValue.r * 255.f ),
				   static_cast< U_CHAR >( colorValue.g * 255.f ),
				   static_cast< U_CHAR >( colorValue.b * 255.f ),
				   static_cast< U_CHAR >( colorValue.a * 255.f ));
}

//!--------------------------------------------------------------------
//! 
//! @brief	Color4からColor4Fに変換する
//! @param	[in] color4	- 変換したいColor4
//! @retval	Color4Fになった色
//! 
//!--------------------------------------------------------------------
inline const Color4F ToColor4F( const Color4& color4 )
{
	return Color4F( color4[ ColorChannel::RED   ] / 255.f,
					color4[ ColorChannel::GREEN ] / 255.f,
					color4[ ColorChannel::BLUE  ] / 255.f,
					color4[ ColorChannel::ALPHA ] / 255.f);
}


}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_COLOR4_H	end