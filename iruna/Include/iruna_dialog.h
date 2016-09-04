//*********************************************************************
/*!
	@file	iruna_dialog.h
	@brief	システムダイアログを生成する
	@author	立川 翔野
	@date	2011/10/21	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_DIALOG_H
#define IRUNA_DIALOG_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----ネームスペース-------------------------------------------------*/
namespace iruna
{
namespace core
{

/*----グローバル変数定義---------------------------------*/
extern LPCTSTR			CD_FILTER_LOAD_MODEL;	//!<	読み込むファイル(モデル)
extern LPCTSTR			CD_FILTER_SAVE_MODEL;	//!<	書き込むファイル(モデル)
extern LPCTSTR			CD_FILTER_TEXTURE;		//!<	読み込むファイル(テクスチャ)
extern LPCTSTR			CD_FILTER_SHEDER;		//!<	読み込むファイル(シェーダー)

extern const DWORD		CD_FLAGS_SAVE;		//!<	ダイアログフラグ(SAVE)
extern const DWORD		CD_FLAGS_LOAD;		//!<	ダイアログフラグ(LOAD)

/*----グローバル関数定義---------------------------------*/

//!--------------------------------------------------------------------
//! 
//! @brief	名前をつけて保存ダイアログの生成
//! @param	[in] path		- 保存先するディレクトリパス
//! @param	[in] filter		- 読み込み時の拡張子のパス
//! @param	[in] flags		- ダイアログ生成時に他のウィンドウをアクティブにするかどうかのフラグ
//! @param	[in] fullPath	- フルパスを取得するかどうか
//! @retval	結果フラグ
//! 
//!--------------------------------------------------------------------
extern int				SaveDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

//!--------------------------------------------------------------------
//! 
//! @brief	開くダイアログの生成
//! @param	[in] path		- 開く先のディレクトリパス
//! @param	[in] filter		- 読み込み時の拡張子のパス
//! @param	[in] flags		- ダイアログ生成時に他のウィンドウをアクティブにするかどうかのフラグ
//! @param	[in] fullPath	- フルパスを取得するかどうか
//! @retval	結果フラグ
//! 
//!--------------------------------------------------------------------
extern int				LoadDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

}	//	core
}	//	iruna


#endif	//	IRUNA_DIALOG_H	end