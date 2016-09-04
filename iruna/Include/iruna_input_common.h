//*********************************************************************
/*!
	@file	iruna_input_common.h
	@brief	インプット 共通ヘッダー
	@author	立川 翔野
	@date	2011/06/24	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_INPUT_COMMON_H
#define IRUNA_INPUT_COMMON_H


/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

namespace iruna
{
namespace io
{
//	インプットデバイスの状態一覧
enum INPUT_STATE{
	INPUT_RELEASE	= 0,	//!< 離している
	INPUT_PUSH		= 1,	//!< 押した瞬間
	INPUT_PUSHED	= 2,	//!< 押している
	INPUT_RELEASED	= 3,	//!< 離した瞬間
};

// インプットデバイスの状態テーブル
const INPUT_STATE	INPUT_STATE_TABLE[ 2 ][ 2 ] = {
	{ INPUT_RELEASE,	INPUT_RELEASED	},
	{ INPUT_PUSH,		INPUT_PUSHED	},
};

//!=====================================================================
//!
//! @struct	MouseButton
//! @brief	マウスのボタンの一覧
//!
//!=====================================================================
struct MouseButton
{
	enum Type{
		LEFT,
		RIGHT,
		CENTER,
		KEY3,
		KEY4,
		KEY5,
		KEY6,
		KEY7
	};
};

}	// io		end
}	// iruna	end

/*----関数 宣言----------------------------------------------------*/
namespace iruna
{
namespace io
{

//!--------------------------------------------------------------------
//! 
//! @brief	キーボードの指定したキーの状態を返す
//! @param	[in] key	- 調べたいキー
//! @retval	押されたキーの状態
//! 
//!--------------------------------------------------------------------
INPUT_STATE		CheckKeyState( U_LONG key );

//!--------------------------------------------------------------------
//! 
//! @brief	マウスの指定したキーの状態を返す
//! @param	[in] key	- 調べたいキー
//! @retval	押されたキーの状態
//! 
//!--------------------------------------------------------------------
INPUT_STATE		CheckMouseState( MouseButton::Type key );

//!--------------------------------------------------------------------
//! 
//! @brief	マウスカーソルの位置を取得する
//! @retval	マウスカーソルの位置
//! 
//!--------------------------------------------------------------------
POINT			GetMousePosition();

}	//	io		end
}	//	iruna	end
#endif //	IRUNA_INPUT_COMMON_H	end