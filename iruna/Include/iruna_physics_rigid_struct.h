//*********************************************************************
/*!
	@file	iruna_physics_rigid_struct.h
	@brief	���̂̃p�����[�^�[�������\���̒�`
	@author	���� �Ė�
	@date	2012/05/30	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_PHYSICS_RIGID_STRUCT_H
#define IRUNA_PHYSICS_RIGID_STRUCT_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_math.h"

/*----�f�[�^�^�錾-------------------------------------------------*/
namespace iruna
{
namespace physics
{

//!=====================================================================
//!
//! @class	BoxParameter
//! @brief	����( �{�b�N�X�^ )�p�����[�^�[
//!
//!=====================================================================
struct BoxParameter
{
	float				weight;		//	���̂̏d��
	math::Vector3		pos;		//	�ʒu
	math::Vector3		scale;		//	�傫��
	math::Vector3		center;		//	���S�ʒu
	math::Vector3		rotate;		//	��]
	math::Vector3		halfSize;	//	���a
};

//!=====================================================================
//!
//! @class	BoxParameter
//! @brief	����( �{�b�N�X�^ )�p�����[�^�[
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
//! @brief	����( ���ʌ^ )�p�����[�^�[
//!
//!=====================================================================
struct PlaneParameter
{
	math::Vector3		pos;	//	���S�ʒu
	math::Vector3		rotate;	//	��]
	math::Vector3		normal;	//	���a
};

}	//	physics end
}	//	iruna end

#endif	//	IRUNA_PHYSICS_RIGID_STRUCT_H	end