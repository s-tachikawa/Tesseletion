//*********************************************************************
/*!
	@file	iruna_debug.h
	@brief	デバッグ用など
	@author	立川 翔野
	@date	2011/06/22	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_DEBUG_H
#define IRUNA_DEBUG_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_types.h"

/*----関数 定義----------------------------------------------------*/
namespace iruna
{

//!--------------------------------------------------------------------
//! 
//! @brief	デバッグウィンドウに文字と数値を出力する(デバッグ時のみ有効)
//! @param	[in] str	- 出力する文字列
//! @param	[in] ...	- ぶちこみたい数値
//! 
//!--------------------------------------------------------------------
inline void DrawDebugFormatString( LPCSTR str, ... )
{
	va_list		list;
	char		temp[ 256 ];

	va_start( list, str );
	vsprintf_s( temp, 256, str, list );
	va_end( list );
	
	OutputDebugString( temp );

	return;
}

}	// iruna	end
#endif	// IRUNA_DEBUG_H	end