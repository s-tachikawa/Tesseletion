//---------------------------------------------------------
// 
//	iruna_system.cpp
//	iruna���C�u�����Ǘ��N���X
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_system.h"
#include "../Include/iruna_flame_manager.h"
#include "../Source/iruna_window.h"
#include "../Source/iruna_device.h"
#include "../Source/iruna_input_device.h"
//#include "../Source/iruna_physics_core.h"
#include "../Include/iruna_text.h"
#include "../Source/iruna_sound_device.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#pragma warning( disable : 4127 )	// while���̏��������萔���ƃ_���Ȃ̂𖳎�����

namespace iruna
{

// �ÓI�����o�ϐ��̎���
System*	System::instance	= 0;

// �R���X�g���N�^(�O������̌ďo���֎~)
System::System()
	: frame	( 0 ),
	  window( 0 ),
	  device( 0 ),
	  input ( 0 ),
	  text	( 0 ),
	  sound	( 0 )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	return;
}

// �f�X�g���N�^
System::~System()
{
	return;
}

// �V�X�e���N���X�̗B��̃C���X�^���X��������֐�
System& System::GetInstance()
{
	if( !instance )
		instance	= new System;
		
	return *instance; 
}

// �E�B���h�E��f�o�C�X�̃Z�b�g�A�b�v������
bool System::Setup( U_LONG width, U_LONG height, bool mode, LPCSTR name, U_INT speakers, DWORD style, DWORD styleEx, WORD iconID )
{
	if( window && device )
		return false;

	// �t���[�����[�g�}�l�[�W���𐶐�
	//frame	= new core::FrameRateManage;
	//core::FrameRateManage::SetFrameRate( 60.f );

	// �E�B���h�E���쐬
	window	= new core::Window;
	window->SetSize( width, height );
	window->SetMode( mode );
	window->SetName( name );
	window->SetStyle( style, styleEx );
	window->SetIcon( iconID );

	if( !window->Create() )
		return false;

	// �f�o�C�X���쐬
	device	= new graphics::Device;
	
	if( !device->Create( window->GetHandle(), width, height ) )
	{
		return false;
	}

	// �C���v�b�g�f�o�C�X���쐬
	input	= new io::InputDevice;

	if( !input->Create( window->GetHandle() ) )
	{
		return false;
	}

	// �T�E���h�f�o�C�X�̍쐬
	//sound	= new sound::SoundDevice;

	//if(sound->CreateSoundDevice( speakers ) != 0)
	//{
	//	return false;
	//}

	//	�����G���W���̏�����
	//physics = new physics::PhysicsCore;
	//physics->PhysicsCoreInit( NULL, NULL );


	// �e�L�X�g�Ǘ��N���X���쐬
	//text	= graphics::Text::GetInstance();
	//text->SetStyle( 16, "HG�n�p�p�߯�ߑ�" );

	return true;
}

// �E�B���h�E��f�o�C�X���폜�E�J��������
void System::Release()
{
	//SafeDelete( text   );
	SafeDelete( input  );
	SafeDelete( device );
	SafeDelete( window );
	//SafeDelete( frame  );
	//SafeDelete( sound  );
	//SafeDelete( physics );
	SafeDelete( instance );

	return;
}

// �V�X�e���̍X�V�A���b�Z�[�W�����Ȃ�
bool System::Run()
{
	//frame->Synchronization();

	while( true )
	{
		MSG		msg;
		memset( &msg, 0, sizeof( MSG ) );

		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if( WM_QUIT == msg.message )
		{
	
			return false;
		}
		break;
	}

	//	�C���v�b�g�f�o�C�X�̍X�V
	input->Update();
	//	�����G���W���̍X�V
	//physics::PhysicsCore::GetDynamicsWorld()->stepSimulation( 1.0f / 60.0f );
	//physics::PhysicsCore::GetDynamicsWorld()->debugDrawWorld();

	return true;
}

// �m���A�N�e�B�u���̃V�X�e���X�V
bool System::Idle()
{
	Sleep( 1 );

	return true;
}

// �E�B���h�E���A�N�e�B�u���m���A�N�e�B�u�����擾����
bool System::IsActive()
{
	return ( window->GetHandle() == GetActiveWindow() );
}

// �N�����ɃE�B���h�E���[�h��؂�ւ���
bool System::ChangeWindowMode( bool mode )
{
	if( window->GetMode() == mode )
		return true;

	//device->SetPresentParameters( window->GetWidth(), window->GetHeight(), mode );

	while( true )
	{
		MSG		msg;
		memset( &msg, 0, sizeof( MSG ) );

		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if( WM_QUIT == msg.message )
			return false;

		break;
	}

	window->SetMode( mode );

	return true;
}

}	//	iruna	end