//*********************************************************************
/*!
	@file	iruna_animetion_controller.h
	@brief	モデルアニメーションクラス
	@author	立川 翔野
	@date	2012/06/14 	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_ANIMETION_PMD_H
#define IRUNA_ANIMETION_PMD_H

/*----インクルード------------------------------------------------*/
#include "../Include/iruna_model_data.h"
#include "../Source/iruna_animetion_base.h"
#include "../Source/iruna_shader_pmd.h"
#include "../Include/iruna_camera.h"

/*----データ型-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	VmdMotionData
//! @brief	VMDモーションデータ
//!
//!=====================================================================
struct VmdMotionData
{
	int					freamIndex;		//フレーム番号
	std::string 		boneName;		//ボーン名
	math::Vector4 		mTransform;		//座標変換
	math::Quaternion	mQuaternion;	//クォータニオン
	math::Matrix		mTransformMat;	//変換行列

	//	コンストラクタ
	VmdMotionData()
	{
		D3DXMatrixIdentity( &mTransformMat );
	}
	//	ソートを使用するための演算子のオーバーロード
	bool operator < ( const VmdMotionData& right )
	{
		return this->freamIndex < right.freamIndex;
	}
};

//!=====================================================================
//!
//! @class	PMDのアニメーションデータVMDを読み込み
//! @brief	スキニングアニメーションの操作ベースクラス
//!
//!=====================================================================
class PmdAnimetion : public AnimetionBase
{
private:
	
	typedef std::vector< std::vector< VmdMotionData > >		KeyFlameData;

private:
	
	ModelData*							data;			//!<	アニメーションモデルデータ
	std::vector< math::Vector3 >		bonePos;		//!<	モデルローカル座標
	std::vector< math::Quaternion >		boneRot;		//!<	モデルローカル回転角
	int									max_flame;		//!<	最大フレーム
	KeyFlameData						AnimetionData;	//!<	アニメーションデータ
	PmdShader*							shader;			//!<	PMD用シェーダークラス	

public:
	Camera								camera;			//!<	カメラ

public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	PmdAnimetion( ModelData* in_data );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~PmdAnimetion();
	//!--------------------------------------------------------------------
	//! 
	//! @brief	アニメーションを設定する
	//! @param	[in] flame			- 描画するフレーム
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetAnimetion( int flame );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	アニメーションデータを読み込む
	//! @param	[in] in_paah			- 読み込むアニメーションデータのディレクトリ
	//! @retval	結果フラグ	0：成功　-1：失敗
	//! 
	//!--------------------------------------------------------------------
	int	Load( std::string in_path );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	モデルデータの描画
	//! @param	[in] pos			- 描画する座標
	//! 
	//!--------------------------------------------------------------------
	void Render( math::Vector3 pos );

	

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_ANIMETION_PMD_H	end