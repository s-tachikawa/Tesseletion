//---------------------------------------------------------
// 
//	iruna_vertex_buffer.cpp
//	�o�[�e�N�X�o�b�t�@�̃��b�v
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_vertex_buffer.h"
#include "../Source/iruna_device.h"
#include <xnamath.h>

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
VertexBuffer::VertexBuffer()
	:	m_pcBuffer( NULL ),
		m_nStride		( 0 )
{
	ZeroMemory( &m_cBufferDesc, sizeof( m_cBufferDesc ) );
	ZeroMemory( &m_cInitData, sizeof( m_cInitData ) );
	return;
}

// �R�s�[�R���X�g���N�^(�R�s�[�֎~)
VertexBuffer::VertexBuffer( const VertexBuffer& another )
	:	m_pcBuffer		(  NULL ),
		m_nStride		( another.m_nStride )
{
	return;
}

// �f�X�g���N�^
VertexBuffer::~VertexBuffer()
{
	Release();

	return;
}

// ���_�o�b�t�@���쐬����
bool VertexBuffer::CreateVertexBuffer()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// ���_��񂪐ݒ肳��Ă��Ȃ�
	if( m_cInitData.pSysMem == NULL )
	{
		return false;
	}

	hr = pcDevice->CreateBuffer( &m_cBufferDesc, &m_cInitData, &m_pcBuffer );
	// ���_�o�b�t�@�̍쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}

	// ���_�o�b�t�@�쐬����
	return true;
}

// �o�b�t�@���쐬
bool VertexBuffer::Create( int nBufferSize, int nVertexCount )
{

	//	�쐬����o�b�t�@�̐ݒ�
	m_cBufferDesc.Usage				= D3D11_USAGE_DEFAULT;				// VertexBuffer���������ݐ�p�ɂ��邩���I�ɏ����������\�ɂ��邩�ǂ����Ȃǂ̃t���O
	m_cBufferDesc.ByteWidth			= nBufferSize * nVertexCount;		// VertexBuffer�̃T�C�Y
	m_cBufferDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;			// VertexBuffer�p�Ƀo�b�t�@���o�C���h����
	m_cBufferDesc.CPUAccessFlags	= 0;								// VertexBuffer��CPU����A�N�Z�X�ł���悤�ɂ��邩�ǂ���
	m_cBufferDesc.MiscFlags			= 0;
	
	// �쐬���������i�[
	m_nStride		= nBufferSize;								// ���_1���̒������Z�b�g

	return CreateVertexBuffer();
}

// �o�b�t�@�ɕ`������
bool VertexBuffer::SetBuffer( const void* data )
{
	// ���_����ݒ�
	m_cInitData.pSysMem = data;
	m_cInitData.SysMemPitch = 0;
	m_cInitData.SysMemSlicePitch = 0;
	return true;
}

// �o�b�t�@���X�g���[���ɗ���
bool VertexBuffer::IntoStream( U_LONG streamNum )
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	UINT nOffset = 0;
	pcDeviceContext->IASetVertexBuffers( streamNum, 1, &m_pcBuffer, &m_nStride, &nOffset );
	return false;
}

// �o�b�t�@���������
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