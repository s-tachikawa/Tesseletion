//*********************************************************************
/*!
	@file	iruna_cube_texture.h
	@brief	キューブテクスチャの管理
	@author	立川 翔野
	@date	2011/06/28	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_CUBE_TEXTURE_H
#define IRUNA_CUBE_TEXTURE_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_surface.h"
#include "../Include/iruna_color4.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	CubeTexture
//! @brief	キューブテクスチャの管理
//!
//!=====================================================================
class CubeTexture
{

//	プライベート	メンバ変数
private:
	LPDIRECT3DCUBETEXTURE9	texture;		//!< テクスチャ
	std::string				recoveryPath;	//!< テクスチャのパス

//	パブリック		メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	CubeTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~CubeTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ファイルからキューブテクスチャを読み込む
	//! @param	[in] path		- ファイルへのパス
	//! @param	[in] color		- カラーキー、透過色の設定(デフォルトは0)
	//! @param	[in] mipLevel	- ミップマップレベル、0〜8を指定(デフォルトは1)
	//! @param	[in] filter		- フィルタリング(デフォルトはD3DX_FILTER_LINEAR
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool Load( std::string path, Color4 color = 0, U_INT mipLevel = 0, DWORD filter = D3DX_FILTER_LINEAR );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	テクスチャの解放
	//! 
	//!--------------------------------------------------------------------
	void Release();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	キューブテクスチャの取得
	//! @retval	テクスチャのポインタ
	//! 
	//!--------------------------------------------------------------------
	const LPDIRECT3DCUBETEXTURE9& GetTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	キューブテクスチャからさーフェースを取得
	//! @param	[in] num		-	どの面のテクスチャサーフェースを取得するか
	//! @param	[out] surface	-	サーフェースを格納するクラスポインタ
	//! 
	//!--------------------------------------------------------------------
	bool	GetSurface( U_INT num, Surface& surface );

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_CUBE_TEXTURE_H