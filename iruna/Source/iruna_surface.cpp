////---------------------------------------------------------
//// 
////	iruna_surface.cpp
////	�T�[�t�F�[�X�֘A
////	�쐬�� 6��23��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Include/iruna_surface.h"
//#include "../Source/iruna_device.h"
//
///*----�f�[�^�^ �錾------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// �R���X�g���N�^(���������邾��)
//Surface::Surface()
//	: surface( 0 )
//{
//	return;
//}
//
//// �R�s�[�R���X�g���N�^�A�Q�ƃJ�E���g���C���N�������g����
//Surface::Surface( const Surface& another )
//	: surface( another.surface )
//{
//	surface->AddRef();
//
//	return;
//}
//
//// �f�X�g���N�^�A�Q�ƃJ�E���g���f�N�������g����
//Surface::~Surface()
//{
//	SafeRelease( surface );
//
//	return;
//}
//
//// Z�o�b�t�@���쐬����
//bool Surface::CreateDepth( U_INT width, U_INT height, Z_Format format )
//{
//	// Z�o�b�t�@�T�C�Y�̃e�[�u��
//	static const D3DFORMAT Z_SIZE[] = {
//		D3DFMT_D16,		// Z_D16
//		D3DFMT_D32,		// Z_D32
//	};
//
//	return SUCCEEDED( Device::GetDevice()->CreateDepthStencilSurface(
//							width,
//							height,
//							Z_SIZE[ format ],
//							D3DMULTISAMPLE_NONE,
//							0,
//							true, // SetDepthTarget�ŕύX�����Ƃ��ɔj�����邩�H
//							&surface,
//							0 ) );
//}
//
//// ����ʂ̕`�����ݐ�����̃T�[�t�F�X�ɂ���
//bool Surface::SetRenderTarget( U_LONG index )
//{
//	return SUCCEEDED( Device::GetDevice()->SetRenderTarget( index, surface ) );
//}
//
//// Z�o�b�t�@�̕`�����ݐ�����̃T�[�t�F�X�ɂ���
//bool Surface::SetDepthTarget()
//{
//	return SUCCEEDED( Device::GetDevice()->SetDepthStencilSurface( surface ) );
//}
//
//// ������Z�q�I�[�o�[���[�h�ALPDIRECT3DSURFACE9�������߂�悤��
//Surface& Surface::operator =( LPDIRECT3DSURFACE9 setSurface )
//{
//	surface		= setSurface;
//
//	return *this;
//}
//
//}	// graphics	end
//}	// iruna	end
//
///*----�O���[�o���֐� ��`----------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// ����ʂ̃T�[�t�F�X���擾����
//bool GetRenderTarget( Surface& surface, U_LONG index )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	if( FAILED( Device::GetDevice()->GetRenderTarget(
//									index,
//									&temp ) ) )
//		return false;
//
//	surface	= temp;
//
//	return true;
//}
//// �w�肵�������_�[�^�[�Q�b�g�̏�����
//bool SetRenderTargetFormat( U_LONG target )
//{
//	return SUCCEEDED( Device::GetDevice()->SetRenderTarget( target ,NULL ) );
//}
//
//// Z�o�b�t�@�̃T�[�t�F�X���擾����
//bool GetDepthTarget( Surface& surface )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	// Z�o�b�t�@�̎擾�Ɏ��s
//	if( FAILED( Device::GetDevice()->GetDepthStencilSurface(
//									&temp ) ) )
//		return false;
//
//	surface	= temp;
//
//	return true;
//}
//bool GetBackBuffer( Surface& back_buffer )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	// �o�b�N�o�b�t�@�̎擾�Ɏ��s
//	if( FAILED( Device::GetDevice()->GetBackBuffer(
//										0,
//										0,
//										D3DBACKBUFFER_TYPE_MONO,
//										&temp ) ) )
//	{
//		return false;
//	}
//
//	back_buffer	= temp;
//
//	return true;
//}
//
//}	//	graphics	end
//}	//	iruna		end