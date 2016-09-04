//*********************************************************************
/*!
	@file	iruna_domain_shader.h
	@brief	�V�F�[�_�[�̊Ǘ�
	@author	���� �Ė�
	@date	2014/01/14	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_DOMAIN_SHADER_H
#define IRUNA_DOMAIN_SHADER_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_base_shader.h"
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_vertex_declaration.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	DomainShader
//! @brief	�h���C���V�F�[�_�[�Ǘ��N���X
//!
//!=====================================================================
class DomainShader : public ShaderBase
{
//	�v���C�x�[�g	�����o�ϐ�
private:
	ID3D11DomainShader*		m_pcDS;				//!< �h���C���V�F�[�_�[

//	�v���C�x�[�g	�����o�ϐ�
private:

//	�p�u���b�N	�����o�ϐ�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	DomainShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~DomainShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���_�V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[�t�@�C�����̒��_�V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- ���_�V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateShader( std::string path, std::string strVertexEntry, eShaderVersion eVersion );
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@�̍쐬
	//! @param	[in] nBufferSize		- �쐬����R���X�^���g�o�b�t�@�̃T�C�Y
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateConstantBuffer( int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���_�V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[�t�@�C�����̒��_�V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- ���_�V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@���V�F�[�_�[�ɃZ�b�g
	//! @param	[in] pBufferData		- �R���X�^���g�o�b�t�@
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetTexture( Texture* pcTex, int nNum = 0 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�쐬����Ă���V�F�[�_�[���f�o�C�X�R���e�L�X�g�ɃZ�b�g
	//! @param	[in] path		- �V�F�[�_�[���̃p�X
	//! @param	[in] texture	- �Z�b�g����L���[�u�e�N�X�`��
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetShader();
};


}	//	graphics	end
}	//	iruna		end



#endif	//	IRUNA_DOMAIN_SHADER_H	end