//---------------------------------------------------------
// 
//	iruna_camera.cpp
//	カメラ関連	VIEWやPROJECTIONなど行列の作成
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_camera.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
Camera::Camera()
{
	fovY	= 0;
	aspect	= 0;
	zNear	= 0;
	zFar	= 0;
	memset( &eye,		 0, sizeof( math::Vector3 ) );
	memset( &lookAt,	 0, sizeof( math::Vector3 ) );
	memset( &upVector,	 0, sizeof( math::Vector3 ) );

	return;
}

// メンバのfovY,aspect,zNear,zFarからプロジェクション行列を作成する
math::Matrix Camera::GetProjection()
{
	math::Matrix	temp;

	D3DXMatrixPerspectiveFovLH( 
			&temp,
			fovY,
			aspect,
			zNear,
			zFar );

	return temp;
}

// メンバのfovY,aspect,zNear,zFarから正射影用プロジェクション行列を作成する
math::Matrix Camera::GetOrtho()
{
	// 近平面の縦幅 = zNear * tan( Y方向の視野角 / 2 ) * 2
	float			nearHeight = zNear * tan( fovY * 0.5f ) * 2.0f;

	// 近平面の横幅 = 近平面の縦幅 * アスペクト比
	float			nearWidth = nearHeight * aspect;

	math::Matrix	temp;

	D3DXMatrixOrthoLH( 
			&temp,
			nearWidth,
			nearHeight,
			zNear,
			zFar ); 

	return temp;
}

// メンバのeye,lookAt,upVectorからビュー行列を作成する
math::Matrix Camera::GetView()
{
	math::Matrix	temp;

	D3DXMatrixLookAtLH(
			&temp,
			&eye,
			&lookAt,
			&upVector );

	return temp;
}

}	//	graphics	end
}	//	iruna		end