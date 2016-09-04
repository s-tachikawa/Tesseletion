//*********************************************************************
/*!
	@file	iruna_release.h
	@brief	解放関数
	@author	立川 翔野
	@date	2011/06/22	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_RELEASE_H
#define IRUNA_RELEASE_H

/*----関数 定義----------------------------------------------------*/
namespace iruna
{

//!--------------------------------------------------------------------
//! 
//! @brief	COMのReleaseを呼び出し、安全にリリースする
//! @param	[in] instance	- インスタンス
//! 
//!--------------------------------------------------------------------
template< class T >
inline void SafeRelease( T& instance )
{
	if( instance )
		instance->Release();

	instance	= 0;

	return;
}

//!--------------------------------------------------------------------
//! 
//! @brief	インスタンスを安全に解放する
//! @param	[in] instance	- インスタンス
//! 
//!--------------------------------------------------------------------
template< class T >
inline void SafeDelete( T& instance )
{
	delete instance;
	instance	= 0;

	return;
}

//!--------------------------------------------------------------------
//! 
//! @brief	インスタンスを安全に解放する(配列版)
//! @param	[in] instance	- インスタンス
//! 
//!--------------------------------------------------------------------
template< class T >
inline void SafeArrayDelete( T& instance )
{
	delete[] instance;
	instance	= 0;

	return;
}

}	//	iruna end
#endif	//	IRUNA_RELEASE_H	end