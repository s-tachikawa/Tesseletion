//*********************************************************************
/*!
	@file	iruna_physics_rigid_struct.h
	@brief	剛体のパラメーター初期化構造体定義
	@author	立川 翔野
	@date	2012/05/30	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_PHYSICS_RIGID_STRUCT_H
#define IRUNA_PHYSICS_RIGID_STRUCT_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_math.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace physics
{

//!=====================================================================
//!
//! @class	BoxParameter
//! @brief	剛体( ボックス型 )パラメーター
//!
//!=====================================================================
struct BoxParameter
{
	float				weight;		//	剛体の重さ
	math::Vector3		pos;		//	位置
	math::Vector3		scale;		//	大きさ
	math::Vector3		center;		//	中心位置
	math::Vector3		rotate;		//	回転
	math::Vector3		halfSize;	//	半径
};

//!=====================================================================
//!
//! @class	BoxParameter
//! @brief	剛体( ボックス型 )パラメーター
//!
//!=====================================================================
struct SpherParameter
{
	float				weight;
	math::Vector3		pos;
	math::Vector3		scale;
	math::Vector3		center;
	math::Vector3		rotate;
	float				radius;
};

//!=====================================================================
//!
//! @class	PlaneParameter
//! @brief	剛体( 平面型 )パラメーター
//!
//!=====================================================================
struct PlaneParameter
{
	math::Vector3		pos;	//	中心位置
	math::Vector3		rotate;	//	回転
	math::Vector3		normal;	//	半径
};

}	//	physics end
}	//	iruna end

#endif	//	IRUNA_PHYSICS_RIGID_STRUCT_H	end