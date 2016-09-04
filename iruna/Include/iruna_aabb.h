//*********************************************************************
/*!
	@file	iruna_aabb.h
	@brief	�����蔻��p�����s���E�{�b�N�X( Axis-Aligned Bounding Box )
	@author	���� �Ė�
	@date	2011/11/30	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUAN_AABB_H
#define IRUAN_AABB_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_vector3.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace geometry
{

//!=====================================================================
//!
//! @struct	Aabb
//! @brief	�����s���E�{�b�N�X�\����
//!
//!=====================================================================
struct Aabb
{
//	�v���C�x�[�g�@�����o�ϐ�
public:

	math::Vector3	min;	//!< �ŏ��l�̍��W
	math::Vector3	max;	//!< �ő�l�̍��W

//	�v���C�x�[�g	�����o�֐�
public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	Aabb();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(���S�_�Ɗe���̕��ŏ�����)
	//! @param	[in] setOrigin		- ���S�_
	//! @param	[in] setHalfWidths	- �e���̕�
	//! 
	//!--------------------------------------------------------------------
	Aabb( math::Vector3 setOrigin, math::Vector3 setHalfWidths );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~Aabb();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	AABB�̒��S�_��ݒ肷��
	//! @param	[in] setOrigin		- ���S�_
	//! 
	//!--------------------------------------------------------------------
	void	SetOrigin( math::Vector3 setOrigin );


	//!--------------------------------------------------------------------
	//! 
	//! @brief	AABB�̒��S�_���擾����
	//! @retval	���S�_
	//! 
	//!--------------------------------------------------------------------
	math::Vector3	GetOrigin() const;


	//!--------------------------------------------------------------------
	//! 
	//! @brief	AABB�̊e���̕���ݒ肷��
	//! @param	[in] setHalfWidths	- �e���̕�
	//! 
	//!--------------------------------------------------------------------
	void	SetHalfWidths( math::Vector3 setHalfWidths );


	//!--------------------------------------------------------------------
	//! 
	//! @brief	AABB�̊e���̕����擾����
	//! @retval	�e���̕�
	//! 
	//!--------------------------------------------------------------------
	math::Vector3	GetHalfWidths() const;

};

}	//	geometry	end
}	//	iruna		end


#endif	//	IRUAN_AABB_H	end