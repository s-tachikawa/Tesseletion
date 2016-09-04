//---------------------------------------------------------
// 
//	iruna_mouse.cpp
//	�}�E�X�֘A
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_mouse.h"
#include <algorithm>

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace io
{

// �ÓI�����o�ϐ��̎���
DIMOUSESTATE2*	Mouse::nowState	= 0;
DIMOUSESTATE2*	Mouse::oldState	= 0;
POINT			Mouse::position;
HWND			Mouse::hWindow	= 0;

// �R���X�g���N�^
Mouse::Mouse()
	: pDIDevice( 0 )
{
	nowState	= new DIMOUSESTATE2;
	oldState	= new DIMOUSESTATE2;
	
	memset( nowState,  0, sizeof( DIMOUSESTATE2 ) );
	memset( oldState,  0, sizeof( DIMOUSESTATE2 ) );
	memset( &position, 0, sizeof( POINT			) );

	return;
}

// �f�X�g���N�^
Mouse::~Mouse()
{
	SafeDelete( oldState );
	SafeDelete( nowState );

	if( pDIDevice )
	{
		pDIDevice->Unacquire();
		SafeRelease( pDIDevice );
	}

	return;
}

// �}�E�X�f�o�C�X���쐬����
bool Mouse::Create( HWND hWindow, LPDIRECTINPUT8 pDInput )
{
	DIPROPDWORD	dipdw;

	memset( &dipdw, 0 , sizeof( DIPROPDWORD ) );

	dipdw.diph.dwSize		= sizeof( DIPROPDWORD );
	dipdw.diph.dwHeaderSize	= sizeof( DIPROPHEADER );
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= DIPROPAXISMODE_REL; // ���΍��W��

	if( FAILED( pDInput->CreateDevice( GUID_SysMouse, &pDIDevice, 0 ) ) )
	{
		// InputDevice�̐����Ɏ��s
		return false;
	}

	if( FAILED( pDIDevice->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		// �f�o�C�X�Ƀ}�E�X��o�^���s
		return false;
	}

	if( FAILED( pDIDevice->SetProperty( DIPROP_AXISMODE, &dipdw.diph ) ) )
	{
		// �}�E�X�̐ݒ��o�^�Ɏ��s
		return false;
	}

	if( FAILED( pDIDevice->SetCooperativeLevel( hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		// �}�E�X�̊��x�̓o�^�Ɏ��s
		return false;
	}

	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}

	this->hWindow	= hWindow;
	
	return true;
}

// �}�E�X�f�o�C�X���X�V����
bool Mouse::Update()
{
	// �}�E�X�̈ʒu���擾
	GetCursorPos( &position );

	// ���̍X�V
	std::swap( oldState, nowState );
	memset( nowState, 0, sizeof( DIMOUSESTATE2 ) );	// �O�̂���

	// �L�[�̏�Ԃ��擾�Atrue �Ȃ�擾����
	if( SUCCEEDED( pDIDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), nowState ) ) )
	{
		return true;
	}

	// �ēx�擾�����݂�Atrue �Ȃ�擾�ł��Ȃ�����
	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}

	// ������x�擾���Ă݂�Atrue �Ȃ�擾����
	if( SUCCEEDED( pDIDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), nowState ) ) )
	{
		return true;
	}
		
	// �擾�ł��Ȃ�����
	return false;
}

// �w�肵���L�[�̏�Ԃ�Ԃ�(�ÓI�����o�֐�)
INPUT_STATE Mouse::GetState( MouseButton::Type key )
{
	// �ŏ�ʃr�b�g( '0'000 0000 )�Ƀt���O�������Ă�̂ŉE��7���炷
	return INPUT_STATE_TABLE[ nowState->rgbButtons[ key ] >> 7 ][ oldState->rgbButtons[ key ] >> 7 ];
}

// �}�E�X�J�[�\���̈ʒu��Ԃ�(�ÓI�����o�֐�)
POINT Mouse::GetPosition()
{
	POINT	temp = position;

	ScreenToClient( hWindow, &temp );
	return temp; 
}

}	//	io		end
}	//	iruna	end