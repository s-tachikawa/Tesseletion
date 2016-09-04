//---------------------------------------------------------
// 
//	iruna_viewport.cpp
//	�r���[�|�[�g�֘A
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_viewport.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// �R���X�g���N�^
Viewport::Viewport()
{
	ZeroMemory( &m_sViewport, sizeof( m_sViewport ) );

	return;
}

// �R�s�[�R���X�g���N�^
Viewport::Viewport( const Viewport& another )
	: m_sViewport( another.m_sViewport ) 
{
	return;
}

// �f�X�g���N�^
Viewport::~Viewport()
{
	return;
}

// �r���[�|�[�g�̑傫�����w�肷��
void Viewport::SetSize( U_INT width, U_INT height )
{
	m_sViewport.Width			= (FLOAT)width;
	m_sViewport.Height			= (FLOAT)height;

	return;
}

// �r���[�|�[�g�̃f�v�X��ݒ�
void Viewport::SetDepth( float fMax, float fMin )
{
	m_sViewport.MaxDepth = fMax;
	m_sViewport.MinDepth = fMin;

	return;
}

// �r���[�|�[�g���f�o�C�X�ɃZ�b�g
bool Viewport::SetViewport()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	pcDeviceContext->RSSetViewports( 1, &m_sViewport );
	return true;
}

// ������Z�q�I�[�o�[���[�h�AD3D11_VIEWPORT�������߂�悤��
Viewport& Viewport::operator =( D3D11_VIEWPORT setViewport )
{
	m_sViewport	= setViewport;

	return *this;
}

}	// graphics	end
}	// iruna	end
