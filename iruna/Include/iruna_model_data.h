//*********************************************************************
/*!
	@file	iruna_model_data.h
	@brief	独自モデルデータ構造体定義
	@author	立川 翔野
	@date	2011/10/21	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_MODEL_DATA_H
#define IRUNA_MODEL_DATA_H

/*----インクルード-------------------------------------------------*/
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

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
//!=====================================================================
//!
//! @struct	GeometryData
//! @brief	ジオメトリの数データ構造体
//!
//!=====================================================================
struct GeometryData
{

	int				vertexCount;	//!<	頂点数
	int				porygonCount;	//!<	ポリゴン数
	int				indexCount;		//!<	インデックス数
	int				materialCount;	//!<	マテリアル数

	GeometryData()
	{
		memset( this, 0, sizeof( GeometryData ) );
	}
};

//!=====================================================================
//!
//! @struct	BoneIndex
//! @brief	頂点に影響を与えるボーンのインデックス番号(最大4つ)
//!
//!=====================================================================
struct BoneIndex
{
	unsigned char indexOne;			//!<	影響するボーン0
	unsigned char indexTwo;			//!<	影響するボーン1
	unsigned char indexThree;		//!<	影響するボーン2
	unsigned char indexFour;		//!<	影響するボーン3

	BoneIndex()
	{
		memset( this, 0, sizeof( BoneIndex ) );
	}
};

//!=====================================================================
//!
//! @struct	VertexData
//! @brief	頂点データ
//!
//!=====================================================================
struct VertexData
{
	math::Vector4 pos;				//!<	頂点座標
	math::Vector3 normal;			//!<	法線
	math::Vector2 uv;				//!<	UV座標
	
	VertexData()
	{
		memset( this, 0, sizeof( VertexData ) );
	}

};

//!=====================================================================
//!
//! @struct	VertexBlending
//! @brief	頂点ブレンディングデータ(最大4つ)
//!
//!=====================================================================
struct VertexBlending
{
	float		wighte[ 4 ];		//!<	頂点ブレンディング
	int			boneIndex[ 4 ];		//!<	影響ボーンインデックス

	VertexBlending()
	{
		memset( this, 0, sizeof( VertexBlending ) );
	}
};

//!=====================================================================
//!
//! @struct	MaterialData
//! @brief	マテリアルデータ
//!
//!=====================================================================
struct MaterialData
{
	Material					material;		//!<	マテリアル
	D3DMATERIAL9				dxMaterial;		//!<	DirectXマテリアル
	int							porygonCount;	//!<	ポリゴンカウント
	IndexBuffer*				indexBuffer;	//!<	インデックスバッファ
	int							indexCount;		//!<	マテリアル内のインデックスカウント
	std::string					texName;		//!<	テクスチャの名前
	Texture*					tex;			//!<	テクスチャ
	float						power;			//!<	スペキュラパワー
	
	MaterialData()
	{
		memset( this, 0, sizeof( MaterialData ) );
	}

};

//!=====================================================================
//!
//! @struct	BufferData
//! @brief	頂点バッファデータ
//!
//!=====================================================================
struct BufferData
{
	VertexBuffer*	vertexBuffer;	//!<	バーテクスバッファ
	IndexBuffer*	indexBuffer;	//!<	インデックスバッファ
	BufferData()
	{
		memset( this, 0, sizeof( BufferData ) );
	}
};

//!=====================================================================
//!
//! @struct	MeshData
//! @brief	メッシュデータ
//!
//!=====================================================================
struct MeshData
{
	int								meshId;			//!<	メッシュID
	int								parentId;		//!<	親メッシュのID
	GeometryData					countData;		//!<	ジオメトリーのカウントデータ
	std::vector< int >				childId;		//!<	子メッシュID
	VertexData*						vertex;			//!<	頂点データ
	VertexBlending*					blending;		//!<	頂点ブレンディング
	int*							index;			//!<	頂点インデックス
	MaterialData*					material;		//!<	マテリアル
	std::vector< math::Matrix >		tran;			//!<	アニメーション平行移動行列(階層アニメーション)
	VertexBuffer*					vertexBuffer;	//!<	頂点バッファ
	IndexBuffer*					indexBuffer;	//!<	インデックスバッファ
	Bone*							bone;			//!<	ボーン構造体
	int								boneCount;		//!<	ボーン数
	IkBone*							ikBone;			//!<	IKボーン構造体
	int								ikBoneCount;	//!<	IKボーン数
	int								animeCount;		//!<	アニメーション数
	
	MeshData()
	{
		memset( this, 0, sizeof( MeshData ) );
	}
};

//!=====================================================================
//!
//! @struct	ModelData
//! @brief	モデルデータ
//!
//!=====================================================================
struct ModelData
{
	int								type;			//!<	モデルデータ
	int								meshCount;		//!<	メッシュ数
	int								animCount;		//!<	アニメーションカウント
	Camera							camera;			//!<	カメラ
	std::vector< MeshData* >		mesh;			//!<	メッシュデータ
};


}	//	graphics	end
}	//	iruna		end

/*
メモ
モデルデータをスマートポインタにしようか検討中
マテリアルの数分だけインデックスバッファを作成しなければけない
ので、モデルデータの構造を再検討(今は仮)
*/



#endif	//	IRUNA_MODEL_DATA_H	end