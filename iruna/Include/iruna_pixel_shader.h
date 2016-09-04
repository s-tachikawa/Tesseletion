//*********************************************************************
/*!
	@file	iruna_pixcel_shader.h
	@brief	シェーダーの管理
	@author	立川 翔野
	@date	2014/01/14	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_PIXCEL_SHADER_H
#define IRUNA_PIXCEL_SHADER_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_base_shader.h"
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_vertex_declaration.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	PixelShader
//! @brief	ピクセルシェーダー管理クラス
//!
//!=====================================================================
class PixelShader : public ShaderBase
{

//	プライベート	メンバ変数
private:
	ID3D11PixelShader*		m_pcPS;				//!< ピクセルシェーダー

//	プライベート	メンバ変数
private:

//	パブリック	メンバ変数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	PixelShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~PixelShader();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点シェーダー作成
	//! @param	[in] path		- シェーダーファイル内の頂点シェーダー関数の指定
	//! @param	[in] flag		- 頂点シェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateShader( std::string path, std::string strVertexEntry, eShaderVersion eVersion );
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファの作成
	//! @param	[in] nBufferSize		- 作成するコンスタントバッファのサイズ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateConstantBuffer( int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点シェーダー作成
	//! @param	[in] path		- シェーダーファイル内の頂点シェーダー関数の指定
	//! @param	[in] flag		- 頂点シェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファをシェーダーにセット
	//! @param	[in] pBufferData		- コンスタントバッファ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetTexture(Texture* pcTex, int nNum = 0 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	作成されているシェーダーをデバイスコンテキストにセット
	//! @param	[in] path		- シェーダー内のパス
	//! @param	[in] texture	- セットするキューブテクスチャ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetShader();
};


}	//	graphics	end
}	//	iruna		end



#endif	//	IRUNA_PIXCEL_SHADER_H	end