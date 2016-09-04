//*********************************************************************
/*!
	@file	iruna_animetion_controller.h
	@brief	���f���A�j���[�V�����N���X
	@author	���� �Ė�
	@date	2012/06/14 	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_ANIMETION_PMD_H
#define IRUNA_ANIMETION_PMD_H

/*----�C���N���[�h------------------------------------------------*/
#include "../Include/iruna_model_data.h"
#include "../Source/iruna_animetion_base.h"
#include "../Source/iruna_shader_pmd.h"
#include "../Include/iruna_camera.h"

/*----�f�[�^�^-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	VmdMotionData
//! @brief	VMD���[�V�����f�[�^
//!
//!=====================================================================
struct VmdMotionData
{
	int					freamIndex;		//�t���[���ԍ�
	std::string 		boneName;		//�{�[����
	math::Vector4 		mTransform;		//���W�ϊ�
	math::Quaternion	mQuaternion;	//�N�H�[�^�j�I��
	math::Matrix		mTransformMat;	//�ϊ��s��

	//	�R���X�g���N�^
	VmdMotionData()
	{
		D3DXMatrixIdentity( &mTransformMat );
	}
	//	�\�[�g���g�p���邽�߂̉��Z�q�̃I�[�o�[���[�h
	bool operator < ( const VmdMotionData& right )
	{
		return this->freamIndex < right.freamIndex;
	}
};

//!=====================================================================
//!
//! @class	PMD�̃A�j���[�V�����f�[�^VMD��ǂݍ���
//! @brief	�X�L�j���O�A�j���[�V�����̑���x�[�X�N���X
//!
//!=====================================================================
class PmdAnimetion : public AnimetionBase
{
private:
	
	typedef std::vector< std::vector< VmdMotionData > >		KeyFlameData;

private:
	
	ModelData*							data;			//!<	�A�j���[�V�������f���f�[�^
	std::vector< math::Vector3 >		bonePos;		//!<	���f�����[�J�����W
	std::vector< math::Quaternion >		boneRot;		//!<	���f�����[�J����]�p
	int									max_flame;		//!<	�ő�t���[��
	KeyFlameData						AnimetionData;	//!<	�A�j���[�V�����f�[�^
	PmdShader*							shader;			//!<	PMD�p�V�F�[�_�[�N���X	

public:
	Camera								camera;			//!<	�J����

public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	PmdAnimetion( ModelData* in_data );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~PmdAnimetion();
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�A�j���[�V������ݒ肷��
	//! @param	[in] flame			- �`�悷��t���[��
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool SetAnimetion( int flame );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�A�j���[�V�����f�[�^��ǂݍ���
	//! @param	[in] in_paah			- �ǂݍ��ރA�j���[�V�����f�[�^�̃f�B���N�g��
	//! @retval	���ʃt���O	0�F�����@-1�F���s
	//! 
	//!--------------------------------------------------------------------
	int	Load( std::string in_path );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	���f���f�[�^�̕`��
	//! @param	[in] pos			- �`�悷����W
	//! 
	//!--------------------------------------------------------------------
	void Render( math::Vector3 pos );

	

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_ANIMETION_PMD_H	end