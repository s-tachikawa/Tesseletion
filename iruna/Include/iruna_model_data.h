//*********************************************************************
/*!
	@file	iruna_model_data.h
	@brief	�Ǝ����f���f�[�^�\���̒�`
	@author	���� �Ė�
	@date	2011/10/21	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_MODEL_DATA_H
#define IRUNA_MODEL_DATA_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_model_types.h"
#include "../Include/iruna_bone.h"
#include "../Include/iruna_ik_bone.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_material.h"
#include "../Include/iruna_vertex_buffer.h"
#include "../Include/iruna_index_buffer.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_camera.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
//!=====================================================================
//!
//! @struct	GeometryData
//! @brief	�W�I���g���̐��f�[�^�\����
//!
//!=====================================================================
struct GeometryData
{

	int				vertexCount;	//!<	���_��
	int				porygonCount;	//!<	�|���S����
	int				indexCount;		//!<	�C���f�b�N�X��
	int				materialCount;	//!<	�}�e���A����

	GeometryData()
	{
		memset( this, 0, sizeof( GeometryData ) );
	}
};

//!=====================================================================
//!
//! @struct	BoneIndex
//! @brief	���_�ɉe����^����{�[���̃C���f�b�N�X�ԍ�(�ő�4��)
//!
//!=====================================================================
struct BoneIndex
{
	unsigned char indexOne;			//!<	�e������{�[��0
	unsigned char indexTwo;			//!<	�e������{�[��1
	unsigned char indexThree;		//!<	�e������{�[��2
	unsigned char indexFour;		//!<	�e������{�[��3

	BoneIndex()
	{
		memset( this, 0, sizeof( BoneIndex ) );
	}
};

//!=====================================================================
//!
//! @struct	VertexData
//! @brief	���_�f�[�^
//!
//!=====================================================================
struct VertexData
{
	math::Vector4 pos;				//!<	���_���W
	math::Vector3 normal;			//!<	�@��
	math::Vector2 uv;				//!<	UV���W
	
	VertexData()
	{
		memset( this, 0, sizeof( VertexData ) );
	}

};

//!=====================================================================
//!
//! @struct	VertexBlending
//! @brief	���_�u�����f�B���O�f�[�^(�ő�4��)
//!
//!=====================================================================
struct VertexBlending
{
	float		wighte[ 4 ];		//!<	���_�u�����f�B���O
	int			boneIndex[ 4 ];		//!<	�e���{�[���C���f�b�N�X

	VertexBlending()
	{
		memset( this, 0, sizeof( VertexBlending ) );
	}
};

//!=====================================================================
//!
//! @struct	MaterialData
//! @brief	�}�e���A���f�[�^
//!
//!=====================================================================
struct MaterialData
{
	Material					material;		//!<	�}�e���A��
	D3DMATERIAL9				dxMaterial;		//!<	DirectX�}�e���A��
	int							porygonCount;	//!<	�|���S���J�E���g
	IndexBuffer*				indexBuffer;	//!<	�C���f�b�N�X�o�b�t�@
	int							indexCount;		//!<	�}�e���A�����̃C���f�b�N�X�J�E���g
	std::string					texName;		//!<	�e�N�X�`���̖��O
	Texture*					tex;			//!<	�e�N�X�`��
	float						power;			//!<	�X�y�L�����p���[
	
	MaterialData()
	{
		memset( this, 0, sizeof( MaterialData ) );
	}

};

//!=====================================================================
//!
//! @struct	BufferData
//! @brief	���_�o�b�t�@�f�[�^
//!
//!=====================================================================
struct BufferData
{
	VertexBuffer*	vertexBuffer;	//!<	�o�[�e�N�X�o�b�t�@
	IndexBuffer*	indexBuffer;	//!<	�C���f�b�N�X�o�b�t�@
	BufferData()
	{
		memset( this, 0, sizeof( BufferData ) );
	}
};

//!=====================================================================
//!
//! @struct	MeshData
//! @brief	���b�V���f�[�^
//!
//!=====================================================================
struct MeshData
{
	int								meshId;			//!<	���b�V��ID
	int								parentId;		//!<	�e���b�V����ID
	GeometryData					countData;		//!<	�W�I���g���[�̃J�E���g�f�[�^
	std::vector< int >				childId;		//!<	�q���b�V��ID
	VertexData*						vertex;			//!<	���_�f�[�^
	VertexBlending*					blending;		//!<	���_�u�����f�B���O
	int*							index;			//!<	���_�C���f�b�N�X
	MaterialData*					material;		//!<	�}�e���A��
	std::vector< math::Matrix >		tran;			//!<	�A�j���[�V�������s�ړ��s��(�K�w�A�j���[�V����)
	VertexBuffer*					vertexBuffer;	//!<	���_�o�b�t�@
	IndexBuffer*					indexBuffer;	//!<	�C���f�b�N�X�o�b�t�@
	Bone*							bone;			//!<	�{�[���\����
	int								boneCount;		//!<	�{�[����
	IkBone*							ikBone;			//!<	IK�{�[���\����
	int								ikBoneCount;	//!<	IK�{�[����
	int								animeCount;		//!<	�A�j���[�V������
	
	MeshData()
	{
		memset( this, 0, sizeof( MeshData ) );
	}
};

//!=====================================================================
//!
//! @struct	ModelData
//! @brief	���f���f�[�^
//!
//!=====================================================================
struct ModelData
{
	int								type;			//!<	���f���f�[�^
	int								meshCount;		//!<	���b�V����
	int								animCount;		//!<	�A�j���[�V�����J�E���g
	Camera							camera;			//!<	�J����
	std::vector< MeshData* >		mesh;			//!<	���b�V���f�[�^
};


}	//	graphics	end
}	//	iruna		end

/*
����
���f���f�[�^���X�}�[�g�|�C���^�ɂ��悤��������
�}�e���A���̐��������C���f�b�N�X�o�b�t�@���쐬���Ȃ���΂��Ȃ�
�̂ŁA���f���f�[�^�̍\�����Č���(���͉�)
*/



#endif	//	IRUNA_MODEL_DATA_H	end