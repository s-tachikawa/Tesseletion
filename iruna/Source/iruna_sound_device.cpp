//---------------------------------------------------------
// 
//	iruna_sound_device.cpp
//	Xaudio2の初期化と管理
//	作成日 7月10日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_sound_device.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace sound
{

// 静的メンバ変数の実体
IXAudio2*				SoundDevice::xAudio			= NULL;	
IXAudio2MasteringVoice*	SoundDevice::masterVoice	= NULL;

// コンストラクタ
SoundDevice::SoundDevice()
{
	return;
}
// デストラクタ
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