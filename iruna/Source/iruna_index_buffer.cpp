//---------------------------------------------------------
// 
//	iruna_index_buffer.cpp
//	インデックスバッファのラップ
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_index_buffer.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
IndexBuffer::IndexBuffer()
	:	m_pcBuffer		( NULL ),
		indexCnt		( 0 ),
		stride			( 0 ),
		format			( UNKNOWN )
{
	return;
}

// コピーコンストラクタ(コピー禁止)
IndexBuffer::IndexBuffer( const IndexBuffer& another )
	:	m_pcBuffer		( NULL ),
		indexCnt		( another.indexCnt ),
		stride			( another.stride ),
		format			( another.format )
{
	return;
}

// デストラクタ
IndexBuffer::~IndexBuffer()
{
	Release();

	return;
}

// インデックスバッファを作成する
bool IndexBuffer::CreateIndexBuffer()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;
	hr = pcDevice->CreateBuffer( &m_sBufferDesc, &m_sSubResourceData, &m_pcBuffer );

	//	インデックスバッファ作成失敗
	if( FAILED( hr ) )
	{
		return false;
	}

	// インデックスバッファ作成成功
	return true;
}

// インデックバッファデスクの作成
bool IndexBuffer::Create( Format indexFormat, U_LONG indexCount )
{
	//インデックスバッファサイズ
	static const int INDEX_SIZE[] = {
		sizeof( short ),	// D3DFMT_INDEX16
		sizeof( int )		// D3DFMT_INDEX32
	};
	
	// UNKNOWNは-1なのではじく
	if( UNKNOWN == indexFormat )
	{
		return false;
	}

	m_sBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	m_sBufferDesc.ByteWidth = INDEX_SIZE[ indexFormat ] * indexCount;
	m_sBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_sBufferDesc.CPUAccessFlags = 0;
	m_sBufferDesc.MiscFlags = 0;
	m_sBufferDesc.StructureByteStride = 0;
	
	// 作成した情報を格納
	indexCnt	= indexCount;
	stride		= INDEX_SIZE[ indexFormat ];
	format		= indexFormat;

	return CreateIndexBuffer();
}

// バッファにデータをセットする
bool IndexBuffer::SetBuffer( const void* data )
{
	m_sSubResourceData.pSysMem = data;
	m_sSubResourceData.SysMemPitch = 0;
	m_sSubResourceData.SysMemSlicePitch = 0;
	return true;
}

// バッファをストリームに流す
bool IndexBuffer::IntoIndices()
{
	// インデックスバッファフォーマット
	DXGI_FORMAT eBufferFormat[] = 
	{
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R32_UINT,
	};

	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	pcDeviceContext->IASetIndexBuffer( m_pcBuffer,eBufferFormat[ format ], 0  );
	
	return true;
}

// バッファを解放する
void IndexBuffer::Release()
{
	SafeRelease( m_pcBuffer );
	m_sBufferDesc.BindFlags				= 0;
	m_sBufferDesc.ByteWidth				= 0;
	m_sBufferDesc.CPUAccessFlags		= 0;
	m_sBufferDesc.MiscFlags				= 0;
	m_sBufferDesc.StructureByteStride	= 0;
	m_sBufferDesc.Usage					= D3D11_USAGE_DEFAULT;

	m_sSubResourceData.pSysMem			= NULL;
	m_sSubResourceData.SysMemPitch		= 0;
	m_sSubResourceData.SysMemSlicePitch = 0;

	indexCnt	= 0;
	stride		= 0;
	format		= UNKNOWN;

	return;
}

}	//	graphics	end
}	//	iruna		end