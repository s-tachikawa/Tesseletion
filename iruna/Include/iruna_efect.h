//*********************************************************************
/*!
	@file	iruna_effect.h
	@brief	シェーダーの管理
	@author	立川 翔野
	@date	2011/06/25	- 作成
	@date	2011/12/30	- 更新 DirectX仕様に変更頂点シェーダーピクセルシェーダージオメトリーシェーダーを管理
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_EFECT_H
#define IRUNA_EFECT_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----class前方宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	class VertexDeclaration;
	class Texture;
}
}

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
class Effect
{
//	フレンドクラス
	friend class VertexDeclaration;		//!< 頂点シェーダー用ボルブを取得しないといけないので

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
	enum eShaderType
	{
		eHLSL_Type,
		eFX_Type,
		eShader_Type_Max
	};
//	プライベート	メンバ変数
private:
	ID3D11VertexShader*			m_pcVS;						//!< 頂点シェーダ
	ID3DBlob*					m_pcVertexBlob;				//!< 頂点シェーダー用ボルブ、頂点レイアウトに必要なので
	ID3D11Buffer*				m_pcConstantBuffer;			//!< 頂点シェーダーで使用するコンスタントバッファ用(cbuffer用)
	
	ID3D11GeometryShader*		m_pcGS;						//!< ジオメトリシェーダ
	ID3D11PixelShader*			m_pcPS;						//!< ピクセルシェーダ
	
	ID3D11HullShader*			m_pcHull;					//!< ハルシェーダー
	ID3DBlob*					m_pcHullBlob;				//!< ハルシェーダー用ボルブ、頂点レイアウトに必要なので
	ID3D11Buffer*				m_pcHullConstantBuffer;		//!< ハルシェーダーで使用するコンスタントバッファ用(cbuffer用)

	ID3D11DomainShader*			m_pcDomain;					//!< ドメインシェーダー
	ID3DBlob*					m_pcDomainBlob;				//!< ドメインシェーダー用ボルブ、頂点レイアウトに必要なので
	ID3D11Buffer*				m_pcDomainConstantBuffer;	//!< ドメインシェーダーで使用するコンスタントバッファ用(cbuffer用)

	std::string					recoveryPath;		//!< ファイルパス

//	プライベート	メンバ変数
private:

	//!--------------------------------------------------------------------
	//! 
	//! @brief	シェーダーファイルのチェック
	//! @param	[in] strPath			- シェーダーファイルのパス
	//! @param	[out] eShaderType		- シェーダーファイルの
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	eShaderType ChackShaderFile( std::string strPath );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	シェーダーファイルをコンパイルする
	//! @param	[in] strPath			- シェーダーファイルのパス
	//! @param	[out] eShaderType		- シェーダーファイルの
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CompileShaderFile( std::string strPath, ID3DBlob* pcShaderBlob );

//	パブリック	メンバ変数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	Effect();

	//!--------------------------------------------------------------------
	//! 
	//! @brief		デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~Effect();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点シェーダー作成
	//! @param	[in] path		- シェーダーファイル内の頂点シェーダー関数の指定
	//! @param	[in] flag		- 頂点シェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateVertexShader( std::string path, std::string strVertexEntry, eShaderVersion eVersion );
	
	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点シェーダーにコンスタントバッファを設定
	//! @param	[in] path		- シェーダーファイル内の頂点シェーダー関数の指定
	//! @param	[in] flag		- 頂点シェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateVertexConstantBuffer( int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	頂点シェーダーにコンスタントバッファを設定
	//! @param	[in] path		- シェーダーファイル内の頂点シェーダー関数の指定
	//! @param	[in] flag		- 頂点シェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateDomainConstantBuffer( int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファを頂点シェーダーに設定
	//! @param	[in] int nRegisterNum - コンスタントバッファのレジスタ番号
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetVertexConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンスタントバッファをドメインシェーダーに設定
	//! @param	[in] int nRegisterNum - コンスタントバッファのレジスタ番号
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetDomainConstantBuffer( void* pData, int nRegisterNum, int nBufferSize );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ピクセルシェーダー作成
	//! @param	[in] path		- シェーダー内ピクセルシェーダー関数の指定
	//! @param	[in] flag		- ピクセルシェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreatePixelShader( std::string path, std::string strPixelEntry, eShaderVersion eVersion );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ハルシェーダー作成
	//! @param	[in] path		- シェーダー内ピクセルシェーダー関数の指定
	//! @param	[in] flag		- ピクセルシェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateHullShader( std::string path, std::string strHullEntry, eShaderVersion eVersion );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ドメインシェーダー作成
	//! @param	[in] path		- シェーダー内ピクセルシェーダー関数の指定
	//! @param	[in] flag		- ピクセルシェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateDomainShader( std::string path, std::string strDomainEntry, eShaderVersion eVersion );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ピクセルシェーダーにテクスチャをセット
	//! @param	[in] path		- シェーダー内ピクセルシェーダー関数の指定
	//! @param	[in] flag		- ピクセルシェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool SetTexture( Texture* pcTex );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	ジオメトリシェーダー作成
	//! @param	[in] path		- シェーダー内ジオメトリシェーダー関数の指定
	//! @param	[in] flag		- ジオメトリシェーダーバージョン
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool CreateGeometryShader( std::string path, std::string strGeometyEntry, eShaderVersion eVersion );

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



#endif	//	IRUNA_EFECT_H	end