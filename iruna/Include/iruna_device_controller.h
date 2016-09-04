//*********************************************************************
/*!
	@file	iruna_device_controller.h
	@brief	デバイスコンテキストを間接的に操作する
	@author	立川 翔野
	@date	2011/06/23	- 作成
	@date	2013/12/31	- 更新	DirectX11用に仕様を変更DeviceではなくDeviceContextを操作するように変更
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_DEVICE_CONTROLLER_H
#define IRUNA_DEVICE_CONTROLLER_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----クラスの前方宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	class Texture;
	class Viewport;
}
}

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	Primitive
//! @brief	ポリゴンの形の一覧
//!
//!=====================================================================
struct Primitive
{
	enum Type
	{
		POINT_LIST		= D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,					//!< D3DPT_POINTLIST
		LINE_LIST		= D3D11_PRIMITIVE_TOPOLOGY_LINELIST,					//!< D3DPT_LINELIST
		LINE_STRIP		= D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,					//!< D3DPT_LINESTRIP
		TRIANGLE_LIST	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,				//!< D3DPT_TRIANGLELIST
		TRIANGLE_STRIP	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,				//!< D3DPT_TRIANGLESTRIP

		CONTROL_POINT_2 = D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
		CONTROL_POINT_3 = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,	//!< 3頂点ドメインコントロールポイント
		CONTROL_POINT_4 = D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,	//!< 4頂点ドメインコントロールポイント
	};
};

//!=====================================================================
//!
//! @class	DeviceController
//! @brief	デバイス操作クラス(モノステート)
//!
//!=====================================================================
class DeviceController
{
//	プライベート	メンバ変数
private:
	static ID3D11DeviceContext*		m_pcD3dDeviceContext;		// デバイスコンテキストへのポインタ
//	パブリック		メンバ関数
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	コンストラクタ
	//! 
	//!--------------------------------------------------------------------
	DeviceController();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デストラクタ
	//! 
	//!--------------------------------------------------------------------
	~DeviceController();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	描画を実行
	//! @param	[in] nVertexCount	- 頂点の数
	//! @param	[in] nIndexCount	- 描画する頂点の最初のインデックス
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	DrawPrimitive( int nVertexCount, int nIndexCount );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	インデックスを使った描画を実行(頂点データはハードウェア側版)
	//! @param	[in] nIndexCount	- インデックス数
	//! @param	[in] nStartIndex	- 描画するインデックス番号
	//! @param	[in] nOffsett		- 描画するインデックス
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	bool	DrawIndexPrimitive( int nIndexCount, int nStartIndex, int nOffset );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	1つのポリゴンが何頂点で構成されるかをデバイスコンテキストに設定
	//! @param	[in] nIndexCount	- インデックス数
	//! @param	[in] nStartIndex	- 描画するインデックス番号
	//! @param	[in] nOffsett		- 描画するインデックス
	//! @retval	結果フラグ	ture：成功　false：失敗
	//! 
	//!--------------------------------------------------------------------
	void	SetMeshTopology( Primitive::Type type );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	Zバッファに描きこむか描きこまないかの設定する
	//! @param	[in] flag			- ture：描きこむ　false：描きこまない
	//! 
	//!--------------------------------------------------------------------
	void	SetZBufferState( bool flag );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	指定したレンダーターゲットをバックバッファに設定
	//! @param	[in] flag			- ture：描きこむ　false：描きこまない
	//! 
	//!--------------------------------------------------------------------
	void	SetRnderTerget( ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デフォルトのレンダーターゲットをバックバッファにセット
	//! 
	//!--------------------------------------------------------------------
	void	SetDefaultRnderTerget();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デフォルトのビューポートを設定
	//! 
	//!--------------------------------------------------------------------
	void	SetDefaultViewPort();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	デバイスがロストしているかロストしてないかを取得する
	//! @retval	ロストフラグ	ture：ロストしている　false：ロストしていない
	//! 
	//!--------------------------------------------------------------------
	bool	IsLostDevice();
};

}	//	graphics	end
}	//	iruna		end

/*----グローバル関数 宣言----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!--------------------------------------------------------------------
//! 
//! @brief	指定したレンダーターゲットをクリアする
//! @retval	結果フラグ	ture：成功　false：失敗
//! 
//!--------------------------------------------------------------------
bool ClearRenderTerget( math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil );

//!--------------------------------------------------------------------
//! 
//! @brief	裏画面をクリアし、描画を開始する
//! @retval	結果フラグ	ture：成功　false：失敗
//! 
//!--------------------------------------------------------------------
bool ClearScreen( float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f );

//!--------------------------------------------------------------------
//! 
//! @brief	描画を終了し、裏画面に描いたものを表画面へ転送
//! @retval	結果フラグ	ture：成功　false：失敗
//! 
//!--------------------------------------------------------------------
bool SwapScreen();

}	//	graphics	end
}	//	iruna		end


#endif	//	IRUNA_DEVICE_CONTROLLER_H	end