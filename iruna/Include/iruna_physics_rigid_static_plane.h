//*********************************************************************
/*!
	@file	iruna_physics_rigid_static_plane.h
	@brief	剛体( 平面型 )
	@author	立川 翔野
	@date	2012/05/27	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_PHYSICS_RIGID_STATIC_PLANE_H
#define IRUNA_PHYSICS_RIGID_STATIC_PLANE_H

/*----インクルード-------------------------------------------------*/
#include <btBulletDynamicsCommon.h>
#include "../Include/iruna_math.h"
#include "../Include/iruna_physics_rigid_body.h"
#include "../Include/iruna_physics_rigid_struct.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace physics
{
//!=====================================================================
//!
//! @class	RigidBox
//! @brief	ボックス型の剛体
//!
//!=====================================================================
class StaticPlane : public RigidBody
{
private:
	btMotionState*			motionState;		//	モーションステート
	btCollisionShape*		collisionShape;		//	当たり判定の形
	btRigidBody*			rigidBody;			//	剛体情報

public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	StaticPlane( PlaneParameter& parameter );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~StaticPlane();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	剛体の行列の取得
	//! @param	[inout] dst	- 行列の入ったポインタ
	//! 
	//!--------------------------------------------------------------------
	void		GetMatrix( float* dst ) const;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	剛体に指定した運動ベクトルを設定する
	//! @param	[in] force	- 運動ベクトル
	//! 
	//!--------------------------------------------------------------------
	void		SetForce( const math::Vector3& force );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	剛体に指定した運動ベクトルと位置を設定する
	//! @param	[in] force	- 運動ベクトル
	//! @param	[in] pos	- 位置
	//! 
	//!--------------------------------------------------------------------
	void		SetForce( const math::Vector3& force, const math::Vector3& pos );
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	回転ベクトルを設定する
	//! @param	[in] torque	- 回転ベクトル
	//! 
	//!--------------------------------------------------------------------
	void		SetTorque( const math::Vector3& torque );
};

}	//	physics	end
}	//	iruna	end
#endif	//	IRUNA_PHYSICS_RIGID_STATIC_PLANE_H	end