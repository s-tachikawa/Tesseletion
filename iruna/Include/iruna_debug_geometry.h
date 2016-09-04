//*********************************************************************
/*!
	@file	white_debug_drawing.h
	@brief	3D�����蔻��̃f�o�b�N�p���f�������\���̌Q
	@author	���� �Ė�
	@date	2011/11/13	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_DEBUG_GEOMETRY_H
#define IRUNA_DEBUG_GEOMETRY_H


/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_vector3.h"
#include "../Include/iruna_color4.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{

// �O���錾
namespace graphics
{

class VertexBuffer;

}	// graphics	end


namespace geometry
{
struct Aabb;
struct Sphere;
struct Line;
struct Segment;

//!=====================================================================
//!
//! @struct	DebugVertex
//! @brief	�����蔻��f�o�b�O�\���p�̒��_�o�b�t�@�p�f�[�^�\����
//!
//!=====================================================================
struct DebugVertex
{
	
	math::Vector3		pos;	//!<	���_���W
	graphics::Color4	color;	//!<	���_�F
};


//!=====================================================================
//!
//! @struct	DebugGeometry
//! @brief	�����蔻��f�o�b�O�\���p�̒��_�f�[�^�\����
//!
//!=====================================================================
struct DebugGeometry
{
//	�p�u���b�N�����o�ϐ�
public:
	UINT			count;	//!<	���_��
	DebugVertex*	data;	//!<	���_�f�[�^

//	�p�u���b�N�����o�֐�
public:
	DebugGeometry()
	{
		data = NULL;
		count = 0;
	}

};

/*----�O���[�o���֐��錾------------------------------------------------*/

//!--------------------------------------------------------------------
//! 
//! @brief	�w�肵���W�I���g����VertexData���쐬����
//! @param	[in]	aabb		- �\��������Aabb
//! @param	[inout] data		- �쐬�����W�I���g���[�f�[�^
//! @param	[in]	color		- �\������W�I���g���[�̐F(�f�t�H���g�͔��F)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Aabb& aabb,		DebugGeometry* data, graphics::Color4 color = 0xffffffff );

//!--------------------------------------------------------------------
//! 
//! @brief	�R���X�g���N�^(Sphere�Œ��_�f�[�^���쐬)
//! @param	[in]	sphere		- �\��������Sphere
//! @param	[inout] data		- �쐬�����W�I���g���[�f�[�^
//! @param	[in]	color		- �\������SPHERE�̐F(�f�t�H���g�͔��F)
//! @param	[in]	slices		- SPHERE�̏c�̕�����(�f�t�H���g��16)
//! @param	[in]	stacks		- SPHERE�̉��̕�����(�f�t�H���g��10)
//! @param	[in]	color		- �\������W�I���g���[�̐F(�f�t�H���g�͔��F)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Sphere& sphere,	DebugGeometry* data, UINT slices = 16, UINT stacks = 10, graphics::Color4 color = 0xffffffff );

//!--------------------------------------------------------------------
//! 
//! @brief	�w�肵���W�I���g����VertexData���쐬����
//! @param	[in]	line		- �\��������Line
//! @param	[inout] data		- �쐬�����W�I���g���[�f�[�^
//! @param	[in]	color		- �\������W�I���g���[�̐F(�f�t�H���g�͔��F)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Line& line,		DebugGeometry* data, graphics::Color4 color = 0xffffffff );

//!--------------------------------------------------------------------
//! 
//! @brief	�w�肵���W�I���g����VertexData���쐬����
//! @param	[in]	segment		- �\��������Segment
//! @param	[inout] data		- �쐬�����W�I���g���[�f�[�^
//! @param	[in]	color		- �\������W�I���g���[�̐F(�f�t�H���g�͔��F)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Segment& segment,DebugGeometry* data, graphics::Color4 color = 0xffffffff );



}	//	geometry	end
}	//	iruna		end


#endif	//	IRUNA_DEBUG_GEOMETRY_H	end