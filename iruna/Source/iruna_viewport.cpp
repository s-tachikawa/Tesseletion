//---------------------------------------------------------
// 
//	iruna_viewport.cpp
//	ビューポート関連
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_viewport.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// コンストラクタ
Viewport::Viewport()
{
	ZeroMemory( &m_sViewport, sizeof( m_sViewport ) );

	return;
}

// コピーコンストラクタ
Viewport::Viewport( const Viewport& another )
	: m_sViewport( another.m_sViewport ) 
{
	return;
}

// デストラクタ
Viewport::~Viewport()
{
	return;
}

// ビューポートの大きさを指定する
void Viewport::SetSize( U_INT width, U_INT height )
{
	m_sViewport.Width			= (FLOAT)width;
	m_sViewport.Height			= (FLOAT)height;

	return;
}

// ビューポートのデプスを設定
void Viewport::SetDepth( float fMax, float fMin )
{
	m_sViewport.MaxDepth = fMax;
	m_sViewport.MinDepth = fMin;

	return;
}

// ビューポートをデバイスにセット
bool Viewport::SetViewport()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	pcDeviceContext->RSSetViewports( 1, &m_sViewport );
	return true;
}

// 代入演算子オーバーロード、D3D11_VIEWPORTをつっこめるように
Viewport& Viewport::operator =( D3D11_VIEWPORT setViewport )
{
	m_sViewport	= setViewport;

	return *this;
}

}	// graphics	end
}	// iruna	end
