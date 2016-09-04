//*********************************************************************
/*!
	@file	iruna_shader_pmd.h
	@brief	PMDモデル用スキニングシェーダー
	@author	立川 翔野
	@date	2012/06/14 	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_SHADER_PMD_H
#define IRUNA_SHADER_PMD_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_model_data.h"
#include "../Include/iruna_camera.h"
#include "../Include/iruna_efect.h"
#include "../Include/iruna_vertex_declaration.h"
#include "../Include/iruna_device_controller.h"

/*----データ型-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	PmdShader
//! @brief	Pmd専用シェーダークラス
//!
//!=====================================================================
class PmdShader
{
private:
	Effect* shader;					//!<	シェーダー
	VertexDeclaration*	dec;		//!<	頂点ディクラレーション
	VertexBuffer*		vertex;		//!<	アニメーション用バーテクスバッファ
	math::Vector3*		pos;		//!<	アニメーション用頂点座標
	math::Vector3*		normal;		//!<	アニメーション用法線
	ModelData*			data;		//!<	モデルデータ
	DeviceController	render;		//!<	レンダリングデバイス

private:

	void Skining(  );

public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	PmdShader( ModelData* in_data );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~PmdShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	モデルの描画
	//! @param	[in] in_data		- 描画するモデルデータ
	//! @param	[in] camera			- カメラデータ
	//! @param	[in] pos			- SGDファイルのディレクトリ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	void Render( math::Vector3 pos );

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_SHADER_PMD_H	end