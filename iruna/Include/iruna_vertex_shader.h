//*********************************************************************
/*!
	@file	iruna_effect.h
	@brief	�V�F�[�_�[�̊Ǘ�
	@author	���� �Ė�
	@date	2011/06/25	- �쐬
	@date	2011/12/30	- �X�V DirectX�d�l�ɕύX���_�V�F�[�_�[�s�N�Z���V�F�[�_�[�W�I���g���[�V�F�[�_�[���Ǘ�
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_VERTEX_SHADER_H
#define IRUNA_VERTEX_SHADER_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_base_shader.h"
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	class VertexDeclaration;
}
}

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
class VertexShader : public ShaderBase
{
//	�t�����h�N���X
	friend class VertexDeclaration;		//!< ���_�V�F�[�_�[�p�{���u���擾���Ȃ��Ƃ����Ȃ��̂�

//	�v���C�x�[�g	�����o�ϐ�
private:
	ID3D11VertexShader*		m_pcVS;				//!< ���_�V�F�[�_
	ID3DBlob*				m_pcShaderBlob;		//!< ���_���C�A�E�g�쐬���ɕK�v�Ȃ̂Ń����o�[�ϐ�

//	�v���C�x�[�g	�����o�ϐ�
private:

//	�p�u���b�N	�����o�ϐ�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	VertexShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~VertexShader();

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
	//! @param	[in] pData				- �o�b�t�@�Ɋi�[����f�[�^
	//! @param	[in] nRegisterNum		- �V�F�[�_�[���ϐ��̃��W�X�^�ԍ�
	//! @param	[in] nBufferSize		- �ݒ肷��f�[�^�T�C�Y
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@���V�F�[�_�[�ɃZ�b�g
	//! @param	[in] pcTex		- �e�N�X�`���i�[�N���X
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetTexture( Texture* pcTex, int nNum = 0 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�쐬����Ă���V�F�[�_�[���f�o�C�X�R���e�L�X�g�ɃZ�b�g
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetShader();
};


}	//	graphics	end
}	//	iruna		end



#endif	//	IRUNA_VERTEX_SHADER_H	end