//*********************************************************************
/*!
	@file	iruna_index_buffer.h
	@brief	インデックスバッファをラップ
	@author	立川 翔野
	@date	2011/06/23	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_INDEX_BUFFER_H
#define IRUNA_INDEX_BUFFER_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	IndexBuffer
//! @brief	インデックスバッファ
//!
//!=====================================================================
class IndexBuffer
{
//	パブリック	型定義
public:
	//	インデックスのデータ型一覧
	enum Format{
		UNKNOWN	= -1,	//!<	未定義
		BIT16	=  0,	//!<	D3DFMT_INDEX16
		BIT32	=  1,	//!<	D3DFMT_INDEX32
	};

//	プライベート	メンバ変数
private:
	ID3D11Buffer*				m_pcBuffer;			//!<	インデックスバッファ
	D3D11_BUFFER_DESC			m_sBufferDesc;		//!<	インデックスバッファデスク
	D3D11_SUBRESOURCE_DATA		m_sSubResourceData;	//!<	バッファ格納用構造体
	U_LONG						indexCnt;			//!<	インデックスの数
	U_LONG						stride;				//!<	インデックス１個分のサイズ
	Format						format;				//!<	インデックスのデータ型

//	プライベート	メンバ関数
private:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	インデックスバッファを作成する
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	CreateIndexBuffer();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コピーコンストラクタ(コピー禁止)
	//! 
	//!--------------------------------------------------------------------
	IndexBuffer( const IndexBuffer& another );

//	パブリック		メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	IndexBuffer();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~IndexBuffer();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	バッファを作成し、フォーマット等をとっておく
	//! @param	[in] indexFormat	- 頂点のフォーマット
	//! @param	[in] indexCount		- 頂点の数
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	Create( Format indexFormat, U_LONG indexCount );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	バッファ全体に書き込む
	//! @param	[in] data		- 書き込むデータ
	//! @param	[in] num		- 書きこむ頂点の数
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	SetBuffer( const void* data );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	バッファをストリームに流す
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	IntoIndices();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	バッファを解放する
	//! 
	//!--------------------------------------------------------------------
	void	Release();
};

}	//	graphics	end
}	//	iruna		end


#endif	//	IRUNA_INDEX_BUFFER_H