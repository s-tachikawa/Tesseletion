//---------------------------------------------------------
// 
//	iruna_device_controller.h
//	�f�o�C�X�̊Ԑڑ���
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_device_controller.h"
#include "../Source/iruna_device.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_viewport.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	// �ÓI�����o�ϐ��̎���
ID3D11DeviceContext*	DeviceController::m_pcD3dDeviceContext	= 0;

// �R���X�g���N�^
DeviceController::DeviceController()
{
	if( !m_pcD3dDeviceContext )
		m_pcD3dDeviceContext	= Device::GetDeviceContext();

	return;
}

// �f�X�g���N�^
DeviceController::~DeviceController()
{
	return;
}

// �`������s(���_�f�[�^�̓\�t�g�E�F�A����)
bool DeviceController::DrawPrimitive( int nVertexCount, int nIndexCount )
{
	m_pcD3dDeviceContext->Draw( nVertexCount, nIndexCount );
	return true;
}

// �C���f�b�N�X���g�����`������s(���_�f�[�^�̓n�[�h�E�F�A����)
bool DeviceController::DrawIndexPrimitive( int nIndexCount, int nStartIndex, int nOffset )
{
	m_pcD3dDeviceContext->DrawIndexed( nIndexCount, nStartIndex, nOffset );
	return true;
}

// 1�̃|���S���������_�ō\������邩���f�o�C�X�R���e�L�X�g�ɐݒ�
void DeviceController::SetMeshTopology(Primitive::Type type)
{
	m_pcD3dDeviceContext->IASetPrimitiveTopology( static_cast< D3D_PRIMITIVE_TOPOLOGY>( type ) );
}

// Z�o�b�t�@�ɕ`�����ނ��`�����܂Ȃ����̐ݒ肷��
void DeviceController::SetZBufferState( bool flag )
{
	return;
}

// �w�肵���e�N�X�`���������_�[�^�[�Q�b�g�ɐݒ�
void DeviceController::SetRnderTerget( ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil )
{
	m_pcD3dDeviceContext->OMSetRenderTargets( 1, &pcRenderTerget, pcDepthStencil );
	return;
}

// �f�t�H���g�̃����_�[�^�[�Q�b�g���Z�b�g
void DeviceController::SetDefaultRnderTerget()
{
	ID3D11DepthStencilView* pcDepthStencil = Device::GetDepthStencilView();
	ID3D11RenderTargetView* pcRenderTerget = Device::GetRenderTargetView();
	m_pcD3dDeviceContext->OMSetRenderTargets( 1, &pcRenderTerget, pcDepthStencil );
	return;
}

// �f�t�H���g�̃r���[�|�[�g�̐ݒ�
void DeviceController::SetDefaultViewPort()
{
	D3D11_VIEWPORT* pcViewPort = Device::GetViewPort();
	m_pcD3dDeviceContext->RSSetViewports( 1, pcViewPort );
}

}	//	graphics	end
}	//	iruna		end

/*----�O���[�o���֐� ��`----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �w�肵�������_�[�^�[�Q�b�g���N���A����
bool ClearRenderTerget(math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil)
{
	return Device::ClearBackBuffer( vColor, pcRenderTerget, pcDepthStencil );
}

//	����ʂ��N���A���A�`����J�n����
bool ClearScreen( float r, float g, float b, float a )
{
	return Device::ClearScreen( r, g, b, a );
}

//	�`����I�����A����ʂɕ`�������̂�\��ʂ֓]��
bool SwapScreen()
{
	return Device::SwapScreen();
}

}	//	graphics	end
}	//	iruna		end