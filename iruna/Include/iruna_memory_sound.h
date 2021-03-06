//*********************************************************************
/*!
	@file	iruna_memory_sound.h
	@brief	サウンドのメモリ展開再生
	@author	立川 翔野
	@date	2011/09/06	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_MEMORY_SOUND_H
#define IRUNA_MEMORY_SOUND_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"



/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace sound
{

/*----前方宣言-------------------------------------------------*/
class OggDecoder;

//!=====================================================================
//!
//! @class	MemorySound
//! @brief	サウンドファイルのメモリ展開再生
//!
//!=====================================================================
class MemorySound
{

//	プライベート	メンバ変数
private:

	IXAudio2SourceVoice*	voice;					//!<	XAoudio2クラス
	BYTE*					buffer;					//!<	展開するバッファ
	U_INT					bufferSize;				//!<	展開するファイルメモリサイズ

//	プライベート	メンバ変数
private:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コピーコンストラクタ(コピー禁止用)
	//! 
	//!--------------------------------------------------------------------
			MemorySound( const MemorySound& dummy );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	＝演算子のオーバーロード(コピー禁止)
	//! 
	//!--------------------------------------------------------------------
	const	MemorySound&	operator =( const MemorySound& dummy );
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	XAoudio2からサウンドファイルを再生するためのクラスを作成
	//! @param	[in] format	- 読み込むサウンドのフォーマット
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	CreateVoice( const WAVEFORMATEX& format );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	サウンドに必要なメモリバッファを読み込む
	//! @param	[in] decocder	- 読み込むOgg読み込みクラスのポインタ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	LoadBuffer( OggDecoder* decocder );


//	パブリック	メンバ関数
public:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	MemorySound();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~MemorySound();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	サウンドファイルの読み込み
	//! @param	[in] path	-　読み込むサウンドファイルのパス
	//! @retval	結果フラグ	-1：失敗
	//! 
	//!--------------------------------------------------------------------
	int		LoadSound( std::string path );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	サウンドの再生(デフォルトで1回のみ再生)
	//! @param	[in] loopPos	- ループフラグ
	//! @retval	結果フラグ	-1：失敗
	//! 
	//!--------------------------------------------------------------------
	int		PlaySound( int loopPos = -1 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	サウンドの停止
	//! @retval	結果フラグ	-1：失敗
	//! 
	//!--------------------------------------------------------------------
	int		StopSound();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	音量の設定
	//! @param	[in] setVolume	- 設定する音量
	//! @retval	結果フラグ	-1：失敗
	//! 
	//!--------------------------------------------------------------------
	int SetVolume( float setVolume );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	再生スピードの設定
	//! @param	[in] setVolume	- 設定する再生スピード
	//! @retval	結果フラグ	-1：失敗
	//! 
	//!--------------------------------------------------------------------
	int SetSpeedRatio( float ratio );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	サウンドの解放
	//! 
	//!--------------------------------------------------------------------
	void Release();



};

}	//	sound	end
}	//	iruna	end

#endif //	IRUNA_MEMORY_SOUND_H	end