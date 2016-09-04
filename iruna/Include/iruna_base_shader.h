//*********************************************************************
/*!
	@file	iruna_base_sheder.h
	@brief	�V�F�[�_�[�̊Ǘ��x�[�X�N���X
	@author	���� �Ė�
	@date	2014/01/03	- �쐬 DirecX11�d�l�ɕύX
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_BASE_SHADER_H
#define IRUNA_BASE_SHADER_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_texture.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	Effect
//! @brief	�G�t�F�N�g�Ǘ��N���X
//!
//!=====================================================================
class ShaderBase
{
public:
	// �V�F�[�_�[�o�[�W����
	enum eShaderVersion
	{
		eShader1_0,
		eShader1_1,
		eShader2_0,
		eShader3_0,
		eShader4_0,
		eShader5_0,
	};
	// �V�F�[�_�[�t�@�C���̎�ވꗗ
	enum eShaderFileType
	{
		eHLSL_Type,
		eFX_Type,
		eShader_Type_Max
	};
	enum eCreateShaderType
	{
		eVertexShader,			//	���_�V�F�[�_�[
		ePixcelShader,			//	�s�N�Z���V�F�[�_�[
		eGeometryShader,		//	�W�I���g���[�V�F�[�_�[
		eHULLShader,			//	HULL�V�F�[�_�[
		eDomainShader,			//	�h���C���V�F�[�_�[
	};
//	�v���C�x�[�g	�����o�ϐ�
protected:
	ID3D11Buffer*				m_pcConstantBuffer;		//!<	�R���X�^���g�o�b�t�@�p(cbuffer�p)
	eCreateShaderType			m_eType;				//!<	�쐬���ꂽ�V�F�[�_�[�^�C�v

//	�v���e�N�e�b�h	�����o�ϐ�
protected:

//	�p�u���b�N	�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	ShaderBase();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	virtual ~ShaderBase();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[�t�@�C�����̒��_�V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- ���_�V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	virtual bool CreateShader( std::string path, std::string strFuncEntry, eShaderVersion eVersion ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@�̍쐬
	//! @param	[in] nBufferSize		- �쐬����R���X�^���g�o�b�t�@�̃T�C�Y
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	virtual bool CreateConstantBuffer( int nBufferSize ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@���V�F�[�_�[�ɃZ�b�g
	//! @param	[in] pBufferData		- �R���X�^���g�o�b�t�@
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	virtual bool SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@���V�F�[�_�[�ɃZ�b�g
	//! @param	[in] pBufferData		- �R���X�^���g�o�b�t�@
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	virtual bool SetTexture( Texture* pcTex, int nNum = 0 ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�쐬����Ă���V�F�[�_�[���f�o�C�X�R���e�L�X�g�ɃZ�b�g
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	virtual bool SetShader() = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�F�[�_�[�^�C�v�̎擾
	//! @retval	�V�F�[�_�[�^�C�v
	//! 
	//!--------------------------------------------------------------------
	eCreateShaderType GetShaderType();

};


}	//	graphics	end
}	//	iruna		end



#endif	//	IRUNA_BASE_SHEDER_H	end