//*********************************************************************
/*!
	@file	iruna_physics_rigid_body.h
	@brief	剛体の基底クラス
	@author	立川 翔野
	@date	2012/05/30	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_PHYSICS_RIGID_BODY_H
#define IRUNA_PHYSICS_RIGID_BODY_H

/*----インクルード-------------------------------------------------*/
#include <btBulletDynamicsCommon.h>
#include "../Include/iruna_math.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace physics
{
//!=====================================================================
//!
//! @class	RigidBody
//! @brief	剛体のインターフェース
//!
//!=====================================================================
class RigidBody
{
private:
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	virtual ~RigidBody(){}

	//!--------------------------------------------------------------------
	//! 
	//! @brief	剛体の行列の取得
	//! @param	[inout] dst	- 行列の入ったポインタ
	//! 
	//!--------------------------------------------------------------------
	virtual void		GetMatrix( float* dst ) const = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	剛体に指定した運動ベクトルを設定する
	//! @param	[in] force	- 運動ベクトル
	//! 
	//!--------------------------------------------------------------------
	virtual void		SetForce( const math::Vector3& force ){}

	//!--------------------------------------------------------------------
	//! 
	//! @brief	剛体に指定した運動ベクトルと位置を設定する
	//! @param	[in] force	- 運動ベクトル
	//! @param	[in] pos	- 位置
	//! 
	//!--------------------------------------------------------------------
	virtual void		SetForce( const math::Vector3& force, const math::Vector3& pos ){}
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	回転ベクトルを設定する
	//! @param	[in] torque	- 回転ベクトル
	//! 
	//!--------------------------------------------------------------------
	virtual void		SetTorque( const math::Vector3& torque ){}

};

}	//	physics	end
}	//	iruna	end

#endif	//	IRUNA_PHYSICS_RIGID_BODY_H	end