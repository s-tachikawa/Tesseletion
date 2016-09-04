//---------------------------------------------------------
// 
//	iruna_input_device.cpp
//	InputDevice�̊Ǘ��Ɛ���
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_input_device.h"
#include "../Source/iruna_keyboard.h"
#include "../Source/iruna_mouse.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib"  )

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace io
{

// �R���X�g���N�^
InputDevice::InputDevice()
	: pDInput ( 0 ),
	  keyboard( 0 ),
	  mouse	  ( 0 )
{
	return;
}

// �f�X�g���N�^
InputDevice::~InputDevice()
{
	SafeDelete(  mouse	  );
	SafeDelete(  keyboard );
	SafeRelease( pDInput  );

	return;
}

// �e�C���v�b�g�f�o�C�X���쐬����
bool InputDevice::Create( HWND hWindow )
{
	if( pDInput )
	{
		return false;
	}

	// �f�o�C�X�̐���
	if( FAILED( DirectInput8Create(
					static_cast< HINSTANCE >( GetModuleHandle( 0 ) ),
					DIRECTINPUT_VERSION,
					IID_IDirectInput8,
					reinterpret_cast< LPVOID* >( &pDInput ),
					0 ) ) )
	{
		return false;
	}
	// �L�[�{�[�h�̐���
	keyboard	= new Keyboard;
	if( !keyboard->Create( hWindow, pDInput ) )
	{
		return false;
	}
	// �}�E�X�̐���
	mouse		= new Mouse;
	if( !mouse->Create( hWindow, pDInput ) )
	{
		return false;
	}

	return true;
}

// �e�C���v�b�g�f�o�C�X���X�V����
bool InputDevice::Update()
{
	if( !keyboard->Update() )
	{
		return false;
	}

	if( !mouse->Update() )
	{
		return false;
	}

	return true;
}

}	//	io		end
}	//	iruna	end