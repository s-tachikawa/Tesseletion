//---------------------------------------------------------
// 
//	iruna_keyboard.cpp
//	�L�[�{�[�h�֘A
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_keyboard.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace io
{

// �ÓI�����o�ϐ��̎���
BYTE*	Keyboard::nowState	= 0;
BYTE*	Keyboard::oldState	= 0;

// �R���X�g���N�^
Keyboard::Keyboard()
	: pDIDevice( 0 )
{
	nowState	= new BYTE[ 256 ];
	oldState	= new BYTE[ 256 ];

	memset( nowState, 0, sizeof( BYTE ) * 256 );
	memset( oldState, 0, sizeof( BYTE ) * 256 );

	return;
}

// �f�X�g���N�^
Keyboard::~Keyboard()
{
	SafeArrayDelete( oldState );
	SafeArrayDelete( nowState );

	if( pDIDevice )
	{
		pDIDevice->Unacquire();
		SafeRelease( pDIDevice );
	}

	return;
}

// �L�[�{�[�h�f�o�C�X���쐬����
bool Keyboard::Create( HWND hWindow, LPDIRECTINPUT8 pDInput )
{
	if( FAILED( pDInput->CreateDevice( GUID_SysKeyboard, &pDIDevice, 0 ) ) )
	{
		//	�L�[�{�[�h�f�o�C�X�̐����Ɏ��s
		return false;
	}

	if( FAILED( pDIDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		// �f�o�C�X�ɃL�[�{�[�h��o�^���s
		return false;
	}

	if( FAILED( pDIDevice->SetCooperativeLevel( hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		// �L�[�{�[�h�̊��x�̐ݒ�����s
		return false;
	}

	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}

	return true;
}

// �L�[�{�[�h�f�o�C�X���X�V����
bool Keyboard::Update()
{
	std::swap( oldState, nowState );
	memset( nowState, 0, sizeof( BYTE ) * 256 );	// �O�̂���

	// �L�[�̏�Ԃ��擾�Atrue �Ȃ�擾����
	if( SUCCEEDED( pDIDevice->GetDeviceState( 256, nowState ) ) )
	{
		return true;
	}
	// �ēx�擾�����݂�Atrue �Ȃ�擾�ł��Ȃ�����
	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}
	// ������x�擾���Ă݂�Atrue �Ȃ�擾����
	if( SUCCEEDED( pDIDevice->GetDeviceState( 256, nowState ) ) )
	{	
		return true;
	}	
	// �擾�ł��Ȃ�����
	return false;
}

// �w�肵���L�[�̏�Ԃ�Ԃ�(�ÓI�����o�֐�)
INPUT_STATE Keyboard::GetState( U_LONG key )
{
	// �ŏ�ʃr�b�g( '0'000 0000 )�Ƀt���O�������Ă�̂ŉE��7���炷
	return INPUT_STATE_TABLE[ nowState[ key ] >> 7 ][ oldState[ key ] >> 7 ];
}

}	//	io		end
}	//	iruna	end