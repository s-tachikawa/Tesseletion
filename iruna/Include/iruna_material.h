//*********************************************************************
/*!
	@file	iruna_material.h
	@brief	�������̃p�����[�^
	@author	���� �Ė�
	@date	2011/06/23	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_MATERIAL_H
#define IRUNA_MATERIAL_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_color4.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	Material
//! @brief	�������̃p�����[�^���������p��
//!
//!=====================================================================
struct Material
{
//	�p�u���b�N	�����o�ϐ�
public:
	Color4F		diffuse;	//!< �g�U��
	Color4F		ambient;	//!< ����
	Color4F		specular;	//!< ���ʌ�
	Color4F		emissive;	//!< ���ˌ�
	float		power;		//!< ���ʌ��̃n�C���C�g
	
// ���p�u���b�N		�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	Material();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(1���w�肵�ď���������^�C�v)
	//! @param	[in] setDiffuse		- �g�U���ɃZ�b�g����l
	//! @param	[in] setAmbient		- �����ɃZ�b�g����l
	//! @param	[in] setSpecular	- ���ʌ��ɃZ�b�g����l
	//! @param	[in] setEmissive	- ���ˌ��ɃZ�b�g����l
	//! @param	[in] setPower		- ���ʌ��̃n�C���C�g�ɃZ�b�g����l
	//! 
	//!--------------------------------------------------------------------
	Material( Color4F setDiffuse, Color4F setAmbient, Color4F setSpecular, Color4F setEmissive, float setPower );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(D3DMATERIAL9�ŏ���������^�C�v)
	//! @param	[in] setMaterial	- �����p�����[�^�ɃZ�b�g����l
	//! 
	//!--------------------------------------------------------------------
	Material( D3DMATERIAL9 setMaterial );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	D3DMATERIAL9�^�Ŏ擾����
	//! @retval	D3DMATERIAL9�^
	//! 
	//!--------------------------------------------------------------------
	D3DMATERIAL9	GetMaterial() const;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	������D3DMATERIAL9�ȂƂ���ɂ����ނ�D3DMATERIAL9�Ƃ��Ĉ�����
	//! @retval	D3DMATERIAL9�^
	//! 
	//!--------------------------------------------------------------------
	inline	operator D3DMATERIAL9() const;
};

// �C�����C�������o�֐��̎���
// ������D3DMATERIAL9�ȂƂ���ɂ����ނ�D3DMATERIAL9�Ƃ��Ĉ�����
inline Material::operator D3DMATERIAL9() const
{
	return GetMaterial();
}

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_MATERIAL_H	end