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
#ifndef IRUNA_EFECT_H
#define IRUNA_EFECT_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----class�O���錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	class VertexDeclaration;
	class Texture;
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
class Effect
{
//	�t�����h�N���X
	friend class VertexDeclaration;		//!< ���_�V�F�[�_�[�p�{���u���擾���Ȃ��Ƃ����Ȃ��̂�

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
	enum eShaderType
	{
		eHLSL_Type,
		eFX_Type,
		eShader_Type_Max
	};
//	�v���C�x�[�g	�����o�ϐ�
private:
	ID3D11VertexShader*			m_pcVS;						//!< ���_�V�F�[�_
	ID3DBlob*					m_pcVertexBlob;				//!< ���_�V�F�[�_�[�p�{���u�A���_���C�A�E�g�ɕK�v�Ȃ̂�
	ID3D11Buffer*				m_pcConstantBuffer;			//!< ���_�V�F�[�_�[�Ŏg�p����R���X�^���g�o�b�t�@�p(cbuffer�p)
	
	ID3D11GeometryShader*		m_pcGS;						//!< �W�I���g���V�F�[�_
	ID3D11PixelShader*			m_pcPS;						//!< �s�N�Z���V�F�[�_
	
	ID3D11HullShader*			m_pcHull;					//!< �n���V�F�[�_�[
	ID3DBlob*					m_pcHullBlob;				//!< �n���V�F�[�_�[�p�{���u�A���_���C�A�E�g�ɕK�v�Ȃ̂�
	ID3D11Buffer*				m_pcHullConstantBuffer;		//!< �n���V�F�[�_�[�Ŏg�p����R���X�^���g�o�b�t�@�p(cbuffer�p)

	ID3D11DomainShader*			m_pcDomain;					//!< �h���C���V�F�[�_�[
	ID3DBlob*					m_pcDomainBlob;				//!< �h���C���V�F�[�_�[�p�{���u�A���_���C�A�E�g�ɕK�v�Ȃ̂�
	ID3D11Buffer*				m_pcDomainConstantBuffer;	//!< �h���C���V�F�[�_�[�Ŏg�p����R���X�^���g�o�b�t�@�p(cbuffer�p)

	std::string					recoveryPath;		//!< �t�@�C���p�X

//	�v���C�x�[�g	�����o�ϐ�
private:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�F�[�_�[�t�@�C���̃`�F�b�N
	//! @param	[in] strPath			- �V�F�[�_�[�t�@�C���̃p�X
	//! @param	[out] eShaderType		- �V�F�[�_�[�t�@�C����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	eShaderType ChackShaderFile( std::string strPath );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�F�[�_�[�t�@�C�����R���p�C������
	//! @param	[in] strPath			- �V�F�[�_�[�t�@�C���̃p�X
	//! @param	[out] eShaderType		- �V�F�[�_�[�t�@�C����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CompileShaderFile( std::string strPath, ID3DBlob* pcShaderBlob );

//	�p�u���b�N	�����o�ϐ�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	Effect();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~Effect();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���_�V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[�t�@�C�����̒��_�V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- ���_�V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateVertexShader( std::string path, std::string strVertexEntry, eShaderVersion eVersion );
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	���_�V�F�[�_�[�ɃR���X�^���g�o�b�t�@��ݒ�
	//! @param	[in] path		- �V�F�[�_�[�t�@�C�����̒��_�V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- ���_�V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateVertexConstantBuffer( int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���_�V�F�[�_�[�ɃR���X�^���g�o�b�t�@��ݒ�
	//! @param	[in] path		- �V�F�[�_�[�t�@�C�����̒��_�V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- ���_�V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateDomainConstantBuffer( int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@�𒸓_�V�F�[�_�[�ɐݒ�
	//! @param	[in] int nRegisterNum - �R���X�^���g�o�b�t�@�̃��W�X�^�ԍ�
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetVertexConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�^���g�o�b�t�@���h���C���V�F�[�_�[�ɐݒ�
	//! @param	[in] int nRegisterNum - �R���X�^���g�o�b�t�@�̃��W�X�^�ԍ�
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetDomainConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�s�N�Z���V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[���s�N�Z���V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- �s�N�Z���V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreatePixelShader( std::string path, std::string strPixelEntry, eShaderVersion eVersion );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�n���V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[���s�N�Z���V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- �s�N�Z���V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateHullShader( std::string path, std::string strHullEntry, eShaderVersion eVersion );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�h���C���V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[���s�N�Z���V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- �s�N�Z���V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateDomainShader( std::string path, std::string strDomainEntry, eShaderVersion eVersion );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����Z�b�g
	//! @param	[in] path		- �V�F�[�_�[���s�N�Z���V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- �s�N�Z���V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetTexture( Texture* pcTex );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�W�I���g���V�F�[�_�[�쐬
	//! @param	[in] path		- �V�F�[�_�[���W�I���g���V�F�[�_�[�֐��̎w��
	//! @param	[in] flag		- �W�I���g���V�F�[�_�[�o�[�W����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool CreateGeometryShader( std::string path, std::string strGeometyEntry, eShaderVersion eVersion );

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



#endif	//	IRUNA_EFECT_H	end