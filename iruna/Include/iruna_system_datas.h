//*********************************************************************
/*!
	@file	iruna_system_datas.h
	@brief	システムを構築するデータ群
	@author	立川 翔野
	@date	2012/05/27	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_SYSTEM_DATAS_H
#define IRUNA_SYSTEM_DATAS_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{

//!=====================================================================
//!
//! @class	SystemCreateDatas
//! @brief	システムの設定用構造体
//!
//!=====================================================================
struct SystemCreateDatas
{
	U_LONG width;		//!<	ウィンドウの横幅
	U_LONG height;		//!<	ウィンドウの高さ
	bool mode;			//!<	ウィンドウのモード(ウィンドウorフルスクリーン)
	LPCSTR name;		//!<	ウィンドウのタイトル
	U_INT speakers;		//!<	スピーカーの構成(デフォルトはSPEAKER_STEREO)
	DWORD style;		//!<	ウィンドウのスタイル(デフォルトはWS_OVERLAPPEDWINDOW)
	DWORD styleEx;		//!<	ウィンドウの拡張スタイル(デフォルトは0)
	WORD iconID;		//!<	ウィンドウのアイコンのリソースID

	SystemCreateDatas()
		:	width( 640 ),
			height( 480 ),
			mode( true ),
			name( "NoName" ),
			speakers( SPEAKER_STEREO ),
			style( WS_OVERLAPPEDWINDOW ),
			styleEx( 0 ),
			iconID( 0 )
	{
		return;
	}

};

}	//	iruna	end

#endif	//	IRUNA_SYSTEM_DATAS_H	end