//*********************************************************************
/*!
	@file	iruna_bone_texture.h
	@brief	ボーンデータ格納したテクスチャの管理
	@author	立川 翔野
	@date	2012/07/17 	- 作成
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

/*----データ型-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	BoneTexture
//! @brief	ボーンデータ用頂点テクスチャ管理クラス
//!
//!=====================================================================
class BoneTexture
{
private:

	Effect*				shader;		//	頂点テクスチャ生成用テクスチャ
	Texture*			tran;		//	平行移動成分格納用テクスチャ
	Texture*			rot;		//	合成回転成分格納用テクスチャ
	Surface*			tranRt;		//	平行移動用レンダリングターゲット
	Surface*			rotRt;		//	合成回転用レンダリングターゲット
	DeviceController*	render;		//	レンダリングデバイス

	int					width;		//	ウィンドウの横幅
	int					height;		//	ウィンドウの縦幅

public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	BoneTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~BoneTexture();

	void SetWindowSize( int in_width, int in_height );
	//!--------------------------------------------------------------------
	//! 
	//! @brief	ボーンテクスチャの更新
	//! 
	//!--------------------------------------------------------------------
	void TextureUpDate( math::Matrix* skinData );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	平行移動成分テクスチャの取得
	//! @retval	Textureクラスポインタ	
	//! 
	//!--------------------------------------------------------------------
	Texture* GetTransTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	合成回転成分テクスチャの取得
	//! @retval	Textureクラスポインタ	
	//! 
	//!--------------------------------------------------------------------
	Texture* GetRotTexture();

	

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_BONE_TEXTURE_H	end