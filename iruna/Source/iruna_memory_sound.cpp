//---------------------------------------------------------
// 
//	iruna_memory_sound.h
//	�T�E���h�̃������W�J�Đ�
//	�쐬�� 9��6��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_memory_sound.h"
#include "../Source/iruna_ogg.h"
#include "../Source/iruna_sound_Device.h"

/*----�f�[�^�^�錾-------------------------------------------------*/
namespace iruna
{
namespace sound
{

// �R�s�[�֎~�p�R�s�[�R���X�g���N�^
MemorySound::MemorySound( const MemorySound &dummy )
{
	( void )dummy;
	return;
}

// �R�s�[�֎~�p�����Z�q�̃I�[�o�[���[�h
const MemorySound& MemorySound::operator =( const MemorySound &dummy )
{
	return dummy;
}

//	�R���X�g���N�^
MemorySound::MemorySound()
{
	voice = NULL;
	return;
}

//	�f�X�g���N�^
MemorySound::~MemorySound()
{
	Release();
	return;
}
//	�T�E���h�������̉��
void MemorySound::Release()
{
	if( voice == NULL )
		return;

	voice->DestroyVoice();
	voice = NULL;

	SafeArrayDelete( buffer );

	return;

}

// �T�E���h�Đ��N���X�̍쐬
bool MemorySound::CreateVoice(const WAVEFORMATEX &format)
{
	HRESULT					result;

	result = SoundDevice::GetDevice()->CreateSourceVoice(
		&voice,
		&format,
		0,
		4.0f
	);
	return false;
}

// �T�E���h�ɕK�v�ȃ������̍쐬
bool MemorySound::LoadBuffer( OggDecoder *decocder )
{
	U_CHAR*			tempBuf		= buffer;
	U_INT			size		= bufferSize;
	U_INT			temp		= 0;

	
	do
	{
		temp = decocder->Decode( tempBuf, size );

		size	-= temp;
		tempBuf	+= temp;

	}
	while( temp );
	

	return false;
}

// �w�肵���T�E���h�t�@�C�����������̈�Ɋi�[����
int MemorySound::LoadSound( std::string path )
{
	OggDecoder* decoder = new OggDecoder;
	WAVEFORMATEX format;

	if( voice )
	{
		return -1;
	}
	
	if( decoder == NULL )
	{
		return -2;
	}

	if(  decoder->Open( path, format ) )
	{
		return -3;
	}

	if( CreateVoice( format ) )
	{
		return -4;
	}

	bufferSize			= format.nBlockAlign * decoder->GetLength();
	buffer				= new U_CHAR[ bufferSize ];
 
	LoadBuffer( decoder );
	SafeDelete( decoder );

	return 0;
}

//	�������ɓW�J�����T�E���h�f�[�^�̍Đ�
int MemorySound::PlaySound( int loopPos )
{
	XAUDIO2_BUFFER			bufInfo	= { 0 };
	XAUDIO2_VOICE_STATE		state;

	voice->GetState( &state );

	if( state.BuffersQueued )
	{
		return voice->Start();
	}

	bufInfo.Flags		= XAUDIO2_END_OF_STREAM;
	bufInfo.AudioBytes	= bufferSize;
	bufInfo.pAudioData	= buffer;

	if( loopPos >= 0 )
	{
		bufInfo.LoopCount	= XAUDIO2_LOOP_INFINITE;
		bufInfo.LoopBegin	= loopPos;
	}

	voice->SubmitSourceBuffer( &bufInfo );

	return voice->Start();
}

// �Đ����~�߂�
int MemorySound::StopSound()
{
	return voice->Stop();
}

//	���ʂ�ݒ肷��
int MemorySound::SetVolume( float setVolume )
{
	return voice->SetVolume( setVolume );
}

//	�Đ��X�s�[�h��ݒ肷��
int MemorySound::SetSpeedRatio( float ratio )
{
	return voice->SetFrequencyRatio( ratio );
}

}	//	sound	end
}	//	iruna	end