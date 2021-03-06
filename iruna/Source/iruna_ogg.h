//*********************************************************************
/*!
	@file	iruna_ogg.h
	@brief	Oggの読み込みと管理
	@author	立川 翔野
	@date	2011/07/09	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_OGG_H
#define IRUNA_OGG_H

/*----インクルード-------------------------------------------------*/
#include <vorbis/vorbisfile.h>
#include "../Include/iruna_utility.h"


/*----マクロ定義-------------------------------------------------*/
#define		SAMPLE_BITS			 16
#define		SAMPLE_BYTES		 SAMPLE_BITS / 8
#define		SOUND_PLAY_ONCE		 -1

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace sound
{

//!=====================================================================
//!
//! @class	OggDecoder
//! @brief	Ogg拡張子のサウンドファイルの読み込みと管理
//!
//!=====================================================================
class OggDecoder
{
//	プライベート	メンバ変数
private:

	OggVorbis_File			fpOgg;	//!<	Oggファイル読み込み用ポインタ
	bool					open;	//!<	ファイル読み込みフラグ

// プライベート	メンバ関数
private:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	Oggファイルからフォーマットの取得
	//! @param	[in] format	- 読み込むサウンドのフォーマット
	//! 
	//!--------------------------------------------------------------------
	void GetOutFormat( WAVEFORMATEX& format );

//	パブリック	メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	OggDecoder();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~OggDecoder();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	Oggファイルの読み込み
	//! @param	[in] path		- 読み込むOggファイルのパス
	//! @param	[out] format	- Oggファイルのフォーマット
	//! @retval	結果フラグ	-1	: 初期化失敗	-2	: ファイルポインタの作成失敗	-3	: Oggファイルポインタの作成失敗
	//! 
	//!--------------------------------------------------------------------
	int Open( std::string path, WAVEFORMATEX& format );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	Oggファイルの解放
	//! 
	//!--------------------------------------------------------------------
	void Close();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	バッファから指定のサイズを読み出す
	//! @param	[in] buf	- 読み込むバッファ
	//! @param	[out] size	- 読み込んだバッファから取り出すサイズ
	//! @retval	読み込んだサイズ
	//! 
	//!--------------------------------------------------------------------
	int	Decode( U_CHAR* buf, U_INT size );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	オフセット分バッファを移動させる
	//! @param	[in] offset	- バッファをどのくらい移動させるか
	//! 
	//!--------------------------------------------------------------------
	void Seek( int offset );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ストリームが終わったかどうか判定する
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool EndStream();
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	バッファの長さを取得
	//! @retval	バッファの長さ
	//! 
	//!--------------------------------------------------------------------
	U_INT GetLength();


};

}	//	sound	end
}	//	iruna	end



#endif	//	IRUNA_OGG_H