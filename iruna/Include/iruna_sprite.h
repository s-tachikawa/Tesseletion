////*********************************************************************
///*!
//	@file	iruna_sprite.h
//	@brief	2Dスプライト
//	@author	立川 翔野
//	@date	2011/06/24	- 作成
//*/
////*********************************************************************
//
///*----多重インクルード防止-------------------------------------------------*/
//#ifndef IRUNA_SPRITE_H
//#define IRUNA_SPRITE_H
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_utility.h"
//#include "../Include/iruna_math.h"
//#include "../Include/iruna_color4.h"
//#include "../Include/iruna_vertex_declaration.h"
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
////! @class	Sprite
////! @brief	スプライトクラス
////!
////!=====================================================================
//class Sprite
//{
////	プロテクテッド	型定義
//protected:
//	// １頂点分のデータ構造体
//	struct Data{
//		math::Vector4	position;	//!< 頂点の座標
//		Color4			color;		//!< 頂点のuv座標
//		math::Vector2	texcoord;	//!< 頂点の色
//	};
//
////	プロテクテッド	メンバ変数
//protected:
//	Data						data[ 4 ];		//!< スプライトの頂点データ
//	math::Vector2				size;			//!< スプライトのサイズ
//	DeviceController*			render;			//!< 間接的にデバイスを操作する
//	static VertexDeclaration	declaration;	//!< ボードの頂点宣言(静的メンバ変数)
//
////	パブリック		メンバ関数
//public:
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	コンストラクタ
//	//! 
//	//!--------------------------------------------------------------------
//	Sprite();
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	デストラクタ
//	//! 
//	//!--------------------------------------------------------------------
//	~Sprite();
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	スプライトのサイズを設定する
//	//! @param	[in] setSize	- 板ポリゴンのサイズ
//	//! 
//	//!--------------------------------------------------------------------
//	void	SetSize( math::Vector2 setSize );
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	スプライトにテクスチャのどの部分を貼るか
//	//! @param	[in] uvRect	- テクスチャの部分矩形
//	//! 
//	//!--------------------------------------------------------------------
//	void	SetTexUV( math::RectF uvRect );
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	スプライトの色を設定する
//	//! @param	[in] setColor	- 板ポリゴンの色
//	//! 
//	//!--------------------------------------------------------------------
//	void	SetColor( Color4 setColor );
//
//	//!--------------------------------------------------------------------
//	//! 
//	//! @brief	スプライトを表示する(内部でZバッファへの書き込みをOFFにしています)
//	//! @param	[in] position	- 表示する位置(スプライトの左上の座標)
//	//! @retval	結果フラグ	ture：成功　false：失敗
//	//! 
//	//!--------------------------------------------------------------------
//	bool	Draw( math::Vector2 position );
//};
//
//}
//}
//
//#endif	//	IRUNA_SPRITE_H	end
