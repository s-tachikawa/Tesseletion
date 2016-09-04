//*********************************************************************
/*!
	@file	iruna_shader_pmd.h
	@brief	PMD���f���p�X�L�j���O�V�F�[�_�[
	@author	���� �Ė�
	@date	2012/06/14 	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_SHADER_PMD_H
#define IRUNA_SHADER_PMD_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_model_data.h"
#include "../Include/iruna_camera.h"
#include "../Include/iruna_efect.h"
#include "../Include/iruna_vertex_declaration.h"
#include "../Include/iruna_device_controller.h"

/*----�f�[�^�^-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	PmdShader
//! @brief	Pmd��p�V�F�[�_�[�N���X
//!
//!=====================================================================
class PmdShader
{
private:
	Effect* shader;					//!<	�V�F�[�_�[
	VertexDeclaration*	dec;		//!<	���_�f�B�N�����[�V����
	VertexBuffer*		vertex;		//!<	�A�j���[�V�����p�o�[�e�N�X�o�b�t�@
	math::Vector3*		pos;		//!<	�A�j���[�V�����p���_���W
	math::Vector3*		normal;		//!<	�A�j���[�V�����p�@��
	ModelData*			data;		//!<	���f���f�[�^
	DeviceController	render;		//!<	�����_�����O�f�o�C�X

private:

	void Skining(  );

public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	PmdShader( ModelData* in_data );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~PmdShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���f���̕`��
	//! @param	[in] in_data		- �`�悷�郂�f���f�[�^
	//! @param	[in] camera			- �J�����f�[�^
	//! @param	[in] pos			- SGD�t�@�C���̃f�B���N�g��
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	void Render( math::Vector3 pos );

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_SHADER_PMD_H	end