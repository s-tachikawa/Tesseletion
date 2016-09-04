//*********************************************************************
/*!
	@file	iruna_physics.h
	@brief	�����G���W���֘A�ꊇ�C���N���[�h
	@author	���� �Ė�
	@date	2012/05/27	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h------------------------------------------------*/
#ifndef IRUNA_PHYSICS_H
#define IRUNA_PHYSICS_H

/*----�C���N���[�h------------------------------------------------*/
#include "../Include/iruna_physics_rigid_box.h"
#include "../Include/iruna_physics_rigid_struct.h"
#include "../Include/iruna_physics_rigid_static_plane.h"
#include "../Include/iruna_physics_rigid_spher.h"

#ifdef _DEBUG
#pragma comment( lib, "BulletCollision_debug.lib" )
#pragma comment( lib, "BulletDynamics_debug.lib" )
#pragma comment( lib, "BulletSoftBody_debug.lib" )
#pragma comment( lib, "ConvexDecomposition_debug.lib" )
#pragma comment( lib, "LinearMath_debug.lib" )
#pragma comment( lib, "OpenGLSupport_debug.lib" )
#pragma comment( lib, "HACD_debug.lib" )
#else
#pragma comment( lib, "BulletCollision.lib" )
#pragma comment( lib, "BulletDynamics.lib" )
#pragma comment( lib, "BulletSoftBody.lib" )
#pragma comment( lib, "ConvexDecomposition.lib" )
#pragma comment( lib, "LinearMath.lib" )
#pragma comment( lib, "OpenGLSupport.lib" )
#pragma comment( lib, "HACD.lib" )
#endif

#endif	//	IRUNA_PHYSICS_H	end