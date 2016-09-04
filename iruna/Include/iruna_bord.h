////*********************************************************************
///*!
//	@file	iruna_board.h
//	@brief	板ポリゴン(派生させてビルボードとかにする)
//	@author	立川 翔野
//	@date	2011/06/27	- 作成
//*/
////*********************************************************************
//
///*----多重インクルード防止-------------------------------------------------*/
//#ifndef IRUNA_BORD_H
//#define IRUNA_BORD_H
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_utility.h"
//#include "../Include/iruna_math.h"
//#include "../Include/iruna_color4.h"
//#include "../Include/iruna_vertex_declaration.h"
//#include "../Include/iruna_vertex_buffer.h"
//#include "../Include/iruna_device_controller.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
////!=====================================================================
////!
////! @class	Board
////! @brief	板ポリゴンクラス
////!
////!=====================================================================
//class Board
//{
////	プロテクテッド	メンバ変数
//protected:
//	VertexBuffer*				positionBuffer;	//!< 頂点の座標バッファ
//	VertexBuffer*				texcoordBuffer;	//!< 頂点のuv座標バッファ
//	VertexBuffer*				colorBuffer;	//!< 頂点の色バッファ
//	VertexBuffer*				normalBuffer;	//!< 法線の色バッファ
//	math::Vector3				size[ 4 ];		//!< バックアップ用のボードサイズ
//	math::Vector2				texcoord[ 4 ];	//!< バックアップ用のuv座標
//	math::Vector3				normal[ 4 ];	//!<	バックアップ用法線
//	Color4						color[ 4 ];		//!< バックアップ用の色
//	DeviceController*			render;			//!< 間接的にデバイスを操作する
//	static VertexDeclaration	declaration;	//!< ボードの頂点宣言(静的メンバ変数)
//
////	パブリック	メンバ関数
//public:
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	コンストラクタ
//	//! 
//	//!--------------------------------------------------------------------
//	Board();
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	デストラクタ(仮想関数)
//	//! 
//	//!--------------------------------------------------------------------
//	virtual	~Board();
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	板ポリゴンのサイズを設定する(仮想関数)
//	//! @param	[in] setSize	- 板ポリゴンのサイズ
//	//! 
//	//!--------------------------------------------------------------------
//	virtual	void	SetSize( math::Vector2 setSize );
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	板ポリゴンにテクスチャのどの部分を貼るか(仮想関数)
//	//! @param	[in] uvRect	- テクスチャの部分矩形
//	//! 
//	//!--------------------------------------------------------------------
//	virtual void	SetTexUV( math::RectF uvRect );
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	板ポリゴンの色を設定する(仮想関数)
//	//! @param	[in] setColor	- 板ポリゴンの色
//	//! 
//	//!--------------------------------------------------------------------
//	virtual void	SetColor( Color4 setColor );
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	板ポリゴンを表示する(仮想関数)
//	//! @retval	結果フラグ	ture：成功　false：失敗
//	//! 
//	//!--------------------------------------------------------------------
//	virtual bool	Draw();
//
//};
//
//}	//	graphics	end
//}	//	iruna		end
//
//#endif	//	IRUNA_BORD_H	end