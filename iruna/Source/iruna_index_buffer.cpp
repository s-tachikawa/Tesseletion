//---------------------------------------------------------
// 
//	iruna_index_buffer.cpp
//	�C���f�b�N�X�o�b�t�@�̃��b�v
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_index_buffer.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
IndexBuffer::IndexBuffer()
	:	m_pcBuffer		( NULL ),
		indexCnt		( 0 ),
		stride			( 0 ),
		format			( UNKNOWN )
{
	return;
}

// �R�s�[�R���X�g���N�^(�R�s�[�֎~)
IndexBuffer::IndexBuffer( const IndexBuffer& another )
	:	m_pcBuffer		( NULL ),
		indexCnt		( another.indexCnt ),
		stride			( another.stride ),
		format			( another.format )
{
	return;
}

// �f�X�g���N�^
IndexBuffer::~IndexBuffer()
{
	Release();

	return;
}

// �C���f�b�N�X�o�b�t�@���쐬����
bool IndexBuffer::CreateIndexBuffer()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;
	hr = pcDevice->CreateBuffer( &m_sBufferDesc, &m_sSubResourceData, &m_pcBuffer );

	//	�C���f�b�N�X�o�b�t�@�쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}

	// �C���f�b�N�X�o�b�t�@�쐬����
	return true;
}

// �C���f�b�N�o�b�t�@�f�X�N�̍쐬
bool IndexBuffer::Create( Format indexFormat, U_LONG indexCount )
{
	//�C���f�b�N�X�o�b�t�@�T�C�Y
	static const int INDEX_SIZE[] = {
		sizeof( short ),	// D3DFMT_INDEX16
		sizeof( int )		// D3DFMT_INDEX32
	};
	
	// UNKNOWN��-1�Ȃ̂ł͂���
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
	
	// �쐬���������i�[
	indexCnt	= indexCount;
	stride		= INDEX_SIZE[ indexFormat ];
	format		= indexFormat;

	return CreateIndexBuffer();
}

// �o�b�t�@�Ƀf�[�^���Z�b�g����
bool IndexBuffer::SetBuffer( const void* data )
{
	m_sSubResourceData.pSysMem = data;
	m_sSubResourceData.SysMemPitch = 0;
	m_sSubResourceData.SysMemSlicePitch = 0;
	return true;
}

// �o�b�t�@���X�g���[���ɗ���
bool IndexBuffer::IntoIndices()
{
	// �C���f�b�N�X�o�b�t�@�t�H�[�}�b�g
	DXGI_FORMAT eBufferFormat[] = 
	{
		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R32_UINT,
	};

	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	pcDeviceContext->IASetIndexBuffer( m_pcBuffer,eBufferFormat[ format ], 0  );
	
	return true;
}

// �o�b�t�@���������
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