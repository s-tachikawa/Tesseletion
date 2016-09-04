//---------------------------------------------------------
// 
//	iruna_vertex_buffer.cpp
//	バーテクスバッファのラップ
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_vertex_buffer.h"
#include "../Source/iruna_device.h"
#include <xnamath.h>

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
VertexBuffer::VertexBuffer()
	:	m_pcBuffer( NULL ),
		m_nStride		( 0 )
{
	ZeroMemory( &m_cBufferDesc, sizeof( m_cBufferDesc ) );
	ZeroMemory( &m_cInitData, sizeof( m_cInitData ) );
	return;
}

// コピーコンストラクタ(コピー禁止)
VertexBuffer::VertexBuffer( const VertexBuffer& another )
	:	m_pcBuffer		(  NULL ),
		m_nStride		( another.m_nStride )
{
	return;
}

// デストラクタ
VertexBuffer::~VertexBuffer()
{
	Release();

	return;
}

// 頂点バッファを作成する
bool VertexBuffer::CreateVertexBuffer()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// 頂点情報が設定されていない
	if( m_cInitData.pSysMem == NULL )
	{
		return false;
	}

	hr = pcDevice->CreateBuffer( &m_cBufferDesc, &m_cInitData, &m_pcBuffer );
	// 頂点バッファの作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	// 頂点バッファ作成成功
	return true;
}

// バッファを作成
bool VertexBuffer::Create( int nBufferSize, int nVertexCount )
{

	//	作成するバッファの設定
	m_cBufferDesc.Usage				= D3D11_USAGE_DEFAULT;				// VertexBufferを書き込み専用にするか動的に書き換えが可能にするかどうかなどのフラグ
	m_cBufferDesc.ByteWidth			= nBufferSize * nVertexCount;		// VertexBufferのサイズ
	m_cBufferDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;			// VertexBuffer用にバッファをバインドする
	m_cBufferDesc.CPUAccessFlags	= 0;								// VertexBufferをCPUからアクセスできるようにするかどうか
	m_cBufferDesc.MiscFlags			= 0;
	
	// 作成した情報を格納
	m_nStride		= nBufferSize;								// 頂点1つ分の長さをセット

	return CreateVertexBuffer();
}

// バッファに描きこむ
bool VertexBuffer::SetBuffer( const void* data )
{
	// 頂点情報を設定
	m_cInitData.pSysMem = data;
	m_cInitData.SysMemPitch = 0;
	m_cInitData.SysMemSlicePitch = 0;
	return true;
}

// バッファをストリームに流す
bool VertexBuffer::IntoStream( U_LONG streamNum )
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	UINT nOffset = 0;
	pcDeviceContext->IASetVertexBuffers( streamNum, 1, &m_pcBuffer, &m_nStride, &nOffset );
	return false;
}

// バッファを解放する
void VertexBuffer::Release()
{
	SafeRelease( m_pcBuffer );
	ZeroMemory( &m_cInitData, sizeof( m_cInitData ) );
	ZeroMemory( &m_cInitData, sizeof( m_cInitData ) );
	m_nStride		= 0;
	return;
}

}	//	graphics	end
}	//	iruna		end