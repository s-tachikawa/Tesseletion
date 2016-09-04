//*********************************************************************
/*!
	@file	iruna_material.h
	@brief	質感等のパラメータ
	@author	立川 翔野
	@date	2011/06/23	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_MATERIAL_H
#define IRUNA_MATERIAL_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_color4.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	Material
//! @brief	質感等のパラメータを扱う共用体
//!
//!=====================================================================
struct Material
{
//	パブリック	メンバ変数
public:
	Color4F		diffuse;	//!< 拡散光
	Color4F		ambient;	//!< 環境光
	Color4F		specular;	//!< 鏡面光
	Color4F		emissive;	//!< 放射光
	float		power;		//!< 鏡面光のハイライト
	
// ●パブリック		メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	Material();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(1つずつ指定して初期化するタイプ)
	//! @param	[in] setDiffuse		- 拡散光にセットする値
	//! @param	[in] setAmbient		- 環境光にセットする値
	//! @param	[in] setSpecular	- 鏡面光にセットする値
	//! @param	[in] setEmissive	- 放射光にセットする値
	//! @param	[in] setPower		- 鏡面光のハイライトにセットする値
	//! 
	//!--------------------------------------------------------------------
	Material( Color4F setDiffuse, Color4F setAmbient, Color4F setSpecular, Color4F setEmissive, float setPower );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ(D3DMATERIAL9で初期化するタイプ)
	//! @param	[in] setMaterial	- 質感パラメータにセットする値
	//! 
	//!--------------------------------------------------------------------
	Material( D3DMATERIAL9 setMaterial );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	D3DMATERIAL9型で取得する
	//! @retval	D3DMATERIAL9型
	//! 
	//!--------------------------------------------------------------------
	D3DMATERIAL9	GetMaterial() const;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	引数がD3DMATERIAL9なところにつっこむとD3DMATERIAL9として扱われる
	//! @retval	D3DMATERIAL9型
	//! 
	//!--------------------------------------------------------------------
	inline	operator D3DMATERIAL9() const;
};

// インラインメンバ関数の実装
// 引数がD3DMATERIAL9なところにつっこむとD3DMATERIAL9として扱われる
inline Material::operator D3DMATERIAL9() const
{
	return GetMaterial();
}

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_MATERIAL_H	end