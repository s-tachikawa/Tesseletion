//---------------------------------------------------------
// 
//	iruna_device_controller.h
//	デバイスの間接操作
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_device_controller.h"
#include "../Source/iruna_device.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_viewport.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// 静的メンバ変数の実体
ID3D11DeviceContext*	DeviceController::m_pcD3dDeviceContext	= 0;

// コンストラクタ
DeviceController::DeviceController()
{
	if( !m_pcD3dDeviceContext )
		m_pcD3dDeviceContext	= Device::GetDeviceContext();

	return;
}

// デストラクタ
DeviceController::~DeviceController()
{
	return;
}

// 描画を実行(頂点データはソフトウェア側版)
bool DeviceController::DrawPrimitive( int nVertexCount, int nIndexCount )
{
	m_pcD3dDeviceContext->Draw( nVertexCount, nIndexCount );
	return true;
}

// インデックスを使った描画を実行(頂点データはハードウェア側版)
bool DeviceController::DrawIndexPrimitive( int nIndexCount, int nStartIndex, int nOffset )
{
	m_pcD3dDeviceContext->DrawIndexed( nIndexCount, nStartIndex, nOffset );
	return true;
}

// 1つのポリゴンが何頂点で構成されるかをデバイスコンテキストに設定
void DeviceController::SetMeshTopology(Primitive::Type type)
{
	m_pcD3dDeviceContext->IASetPrimitiveTopology( static_cast< D3D_PRIMITIVE_TOPOLOGY>( type ) );
}

// Zバッファに描きこむか描きこまないかの設定する
void DeviceController::SetZBufferState( bool flag )
{
	return;
}

// 指定したテクスチャをレンダーターゲットに設定
void DeviceController::SetRnderTerget( ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil )
{
	m_pcD3dDeviceContext->OMSetRenderTargets( 1, &pcRenderTerget, pcDepthStencil );
	return;
}

// デフォルトのレンダーターゲットをセット
void DeviceController::SetDefaultRnderTerget()
{
	ID3D11DepthStencilView* pcDepthStencil = Device::GetDepthStencilView();
	ID3D11RenderTargetView* pcRenderTerget = Device::GetRenderTargetView();
	m_pcD3dDeviceContext->OMSetRenderTargets( 1, &pcRenderTerget, pcDepthStencil );
	return;
}

// デフォルトのビューポートの設定
void DeviceController::SetDefaultViewPort()
{
	D3D11_VIEWPORT* pcViewPort = Device::GetViewPort();
	m_pcD3dDeviceContext->RSSetViewports( 1, pcViewPort );
}

}	//	graphics	end
}	//	iruna		end

/*----グローバル関数 定義----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// 指定したレンダーターゲットをクリアする
bool ClearRenderTerget(math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil)
{
	return Device::ClearBackBuffer( vColor, pcRenderTerget, pcDepthStencil );
}

//	裏画面をクリアし、描画を開始する
bool ClearScreen( float r, float g, float b, float a )
{
	return Device::ClearScreen( r, g, b, a );
}

//	描画を終了し、裏画面に描いたものを表画面へ転送
bool SwapScreen()
{
	return Device::SwapScreen();
}

}	//	graphics	end
}	//	iruna		end