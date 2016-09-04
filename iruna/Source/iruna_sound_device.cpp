//---------------------------------------------------------
// 
//	iruna_sound_device.cpp
//	Xaudio2�̏������ƊǗ�
//	�쐬�� 7��10��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_sound_device.h"

/*----�f�[�^�^�錾-------------------------------------------------*/
namespace iruna
{
namespace sound
{

// �ÓI�����o�ϐ��̎���
IXAudio2*				SoundDevice::xAudio			= NULL;	
IXAudio2MasteringVoice*	SoundDevice::masterVoice	= NULL;

// �R���X�g���N�^
SoundDevice::SoundDevice()
{
	return;
}
// �f�X�g���N�^
SoundDevice::~SoundDevice()
{
	ReleaseSoundDevice();
	return;
}
int SoundDevice::CreateSoundDevice( U_INT speakers )
{
#ifdef _DEBUG
	static const UINT32		flags		= XAUDIO2_DEBUG_ENGINE;
#else
	static const UINT32		flags		= 0;
#endif

	if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
	{
		return -1;
	}

	if( FAILED( XAudio2Create( &xAudio, flags ) ) )
	{
		CoUninitialize();
		return -2;
	}
	if( FAILED( xAudio->CreateMasteringVoice( &masterVoice ) ) )
	{
		CoUninitialize();
		return -3;
	}

	return 0;
}
void SoundDevice::ReleaseSoundDevice()
{
	masterVoice->DestroyVoice();
	xAudio->Release();

	CoUninitialize();

	return;
}
IXAudio2* SoundDevice::GetDevice()
{
	return xAudio;
}
IXAudio2MasteringVoice* SoundDevice::GetMasteringVoice()
{
	return masterVoice;
}

}	//	sound	end
}	//	iruna	end