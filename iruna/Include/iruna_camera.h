//*********************************************************************
/*!
	@file	iruna_camera.h
	@brief	カメラ関連、ViewやProjectionなど
	@author	立川 翔野
	@date	2011/06/24	- 作成
	@date	2011/02/12	- 更新(カメラの正射影用プロジェクションの追加)
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_CAMERA_H
#define IRUNA_CAMERA_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	Camera
//! @brief	View行列、Projection行列を管理する
//!
//!=====================================================================
struct Camera
{
//	パブリック	メンバ変数
public:
	float				fovY;		//!< 視野角(ラジアン角)
	float				aspect;		//!< アスペクト比（画面の横幅/高さ）
	float				zNear;		//!< カメラの最近面
	float				zFar;		//!< カメラの最遠面
	math::Vector3		eye;		//!< 視点
	math::Vector3		lookAt;		//!< 注視点
	math::Vector3		upVector;	//!< カメラの上方向

//	パブリック	メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	Camera();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	メンバのfovY,aspect,zNear,zFarから透視投影変換行列を作成する
	//! @retval	作成した透視投影変換行列
	//! 
	//!--------------------------------------------------------------------
	math::Matrix	GetProjection();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	メンバのfovY,aspect,zNear,zFarから正射影変換行列を作成する
	//! @retval	作成した正射影変換行列
	//! 
	//!--------------------------------------------------------------------
	math::Matrix	GetOrtho();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	メンバのeye,lookAt,upVectorからビュー行列を作成する
	//! @retval	作成したビュー行列
	//! 
	//!--------------------------------------------------------------------
	math::Matrix	GetView();
};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_CAMERA_H	end