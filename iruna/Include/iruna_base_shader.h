//*********************************************************************
/*!
	@file	iruna_base_sheder.h
	@brief	シェーダーの管理ベースクラス
	@author	立川 翔野
	@date	2014/01/03	- 作成 DirecX11仕様に変更
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_BASE_SHADER_H
#define IRUNA_BASE_SHADER_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"
#include "../Include/iruna_texture.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	Effect
//! @brief	エフェクト管理クラス
//!
//!=====================================================================
class ShaderBase
{
public:
	// シェーダーバージョン
	enum eShaderVersion
	{
		eShader1_0,
		eShader1_1,
		eShader2_0,
		eShader3_0,
		eShader4_0,
		eShader5_0,
	};
	// シェーダーファイルの種類一覧
	enum eShaderFileType
	{
		eHLSL_Type,
		eFX_Type,
		eShader_Type_Max
	};
	enum eCreateShaderType
	{
		eVertexShader,			//	頂点シェーダー
		ePixcelShader,			//	ピクセルシェーダー
		eGeometryShader,		//	ジオメトリーシェーダー
		eHULLShader,			//	HULLシェーダー
		eDomainShader,			//	ドメインシェーダー
	};
//	プライベート	メンバ変数
protected:
	ID3D11Buffer*				m_pcConstantBuffer;		//!<	コンスタントバッファ用(cbuffer用)
	eCreateShaderType			m_eType;				//!<	作成されたシェーダータイプ

//	プロテクテッド	メンバ変数
protected:

//	パブリック	メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	ShaderBase();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		デストラクタ
	//! 
	//!--------------------------------------------------------------------
	virtual ~ShaderBase();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	シェーダー作成
	//! @param	[in] path		- シェーダーファイル内の頂点シェーダー関数の指定
	//! @param	[in] flag		- 頂点シェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	virtual bool CreateShader( std::string path, std::string strFuncEntry, eShaderVersion eVersion ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファの作成
	//! @param	[in] nBufferSize		- 作成するコンスタントバッファのサイズ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	virtual bool CreateConstantBuffer( int nBufferSize ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファをシェーダーにセット
	//! @param	[in] pBufferData		- コンスタントバッファ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	virtual bool SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファをシェーダーにセット
	//! @param	[in] pBufferData		- コンスタントバッファ
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	virtual bool SetTexture( Texture* pcTex, int nNum = 0 ) = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	作成されているシェーダーをデバイスコンテキストにセット
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	virtual bool SetShader() = 0;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	シェーダータイプの取得
	//! @retval	シェーダータイプ
	//! 
	//!--------------------------------------------------------------------
	eCreateShaderType GetShaderType();

};


}	//	graphics	end
}	//	iruna		end



#endif	//	IRUNA_BASE_SHEDER_H	end