//*********************************************************************
/*!
	@file	iruna_model_decoder.h
	@brief	モデル読み込みの基底クラス
	@author	立川 翔野
	@date	2011/10/21	- 作成
*/
//*********************************************************************

#ifndef MODEL_DECODER_H
#define MODEL_DECODER_H

/*----インクルード------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_model_data.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	ModelDecoder
//! @brief	モデル読み込みの基底クラス
//!
//!=====================================================================
class ModelDecoder
{
protected:

public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	仮想デストラクタ
	//! 
	//!--------------------------------------------------------------------
	virtual					~ModelDecoder(){}

	//!--------------------------------------------------------------------
	//! 
	//! @brief	解放処理(純粋仮想関数)
	//! 
	//!--------------------------------------------------------------------
	virtual	void			Relese()							= 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	初期化処理(純粋仮想関数)
	//! 
	//!--------------------------------------------------------------------
	virtual	void			Init()								= 0;
		
	//!--------------------------------------------------------------------
	//! 
	//! @brief	指定したモデルファイルの読み込み(純粋仮想関数)
	//! @param	[in] in_path			- モデルファイルのディレクトリ
	//! @param	[in] in_type			- 読み込むモデルタイプ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	virtual bool			Decode( std::string in_path, int in_type )		= 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	読み込んだモデルデータの取得(純粋仮想関数)
	//! @retval	読み込んだモデルデータのポインタ
	//! 
	//!--------------------------------------------------------------------
	virtual ModelData*		GetModelData()						= 0;


};

}	//	graphics	end
}	//	iruna		end

#endif	//	MODEL_DECODER_H	end