//*********************************************************************
/*!
	@file	iruna_vertex_declaration.h
	@brief	頂点宣言をラップ
	@author	立川 翔野
	@date	2011/06/23	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_VERTEX_DECLARATION_H
#define IRUNA_VERTEX_DECLARATION_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----クラス前方宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	class ShaderBase;
	class VertexShader;
}
}
/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	VertexDeclaration
//! @brief	頂点宣言、頂点がどういうデータで構成されているか
//!
//!=====================================================================
class VertexDeclaration
{
//	フレンドクラス
	friend class VertexShader;	//	頂点シェーダーのボルブを取得しないといけないので

//	パブリック	型定義
public:
	
	typedef D3D11_INPUT_ELEMENT_DESC	Element;	//!< 頂点エレメント、これを使って頂点宣言を作る

//	プライベート	メンバ変数
private:
	
	Element*						element;				//!<	頂点エレメントへのポインタ
	ID3D11InputLayout*				m_pcVertexLayout;		//!<	頂点バッファのレイアウト

//	パブリック	メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	VertexDeclaration();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コピーコンストラクタ、参照カウントをインクリメント
	//! 
	//!--------------------------------------------------------------------
	VertexDeclaration( const VertexDeclaration& another );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~VertexDeclaration();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点宣言を作成する、同じエレメントを突っ込んだ場合参照カウントをインクリメント
	//! @param	[in] element	- 頂点エレメント、頂点の構成
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	Create( Element* vertexElement,int nElementCount, ShaderBase* pcShader );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点宣言をセット
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	Set();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点宣言を解放する、参照カウントが0になったら削除する
	//! 
	//!--------------------------------------------------------------------
	void	Release();
};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_VERTEX_DECLARATION_H	end