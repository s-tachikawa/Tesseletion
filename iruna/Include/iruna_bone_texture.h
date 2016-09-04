//*********************************************************************
/*!
	@file	iruna_bone_texture.h
	@brief	�{�[���f�[�^�i�[�����e�N�X�`���̊Ǘ�
	@author	���� �Ė�
	@date	2012/07/17 	- �쐬
*/
//*********************************************************************
#ifndef IRUNA_BONE_TEXTURE_H
#define IRUNA_BONE_TEXTURE_H


#include "../Include/iruna_texture.h"
#include "../Include/iruna_surface.h"
#include "../Include/iruna_viewport.h"
#include "../Include/iruna_device_controller.h"
#include "../Include/iruna_vertex_buffer.h"
#include "../Include/iruna_vertex_declaration.h"
#include "../Include/iruna_efect.h"

/*----�f�[�^�^-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	BoneTexture
//! @brief	�{�[���f�[�^�p���_�e�N�X�`���Ǘ��N���X
//!
//!=====================================================================
class BoneTexture
{
private:

	Effect*				shader;		//	���_�e�N�X�`�������p�e�N�X�`��
	Texture*			tran;		//	���s�ړ������i�[�p�e�N�X�`��
	Texture*			rot;		//	������]�����i�[�p�e�N�X�`��
	Surface*			tranRt;		//	���s�ړ��p�����_�����O�^�[�Q�b�g
	Surface*			rotRt;		//	������]�p�����_�����O�^�[�Q�b�g
	DeviceController*	render;		//	�����_�����O�f�o�C�X

	int					width;		//	�E�B���h�E�̉���
	int					height;		//	�E�B���h�E�̏c��

public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	BoneTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~BoneTexture();

	void SetWindowSize( int in_width, int in_height );
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�{�[���e�N�X�`���̍X�V
	//! 
	//!--------------------------------------------------------------------
	void TextureUpDate( math::Matrix* skinData );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���s�ړ������e�N�X�`���̎擾
	//! @retval	Texture�N���X�|�C���^	
	//! 
	//!--------------------------------------------------------------------
	Texture* GetTransTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	������]�����e�N�X�`���̎擾
	//! @retval	Texture�N���X�|�C���^	
	//! 
	//!--------------------------------------------------------------------
	Texture* GetRotTexture();

	

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_BONE_TEXTURE_H	end