//---------------------------------------------------------
// 
//	iruna_stream_sound.cpp
//	�T�E���h�̃X�g���[���Đ�
//	�쐬�� 7��10��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_stream_sound.h"
#include "../Source/iruna_ogg.h"
#include "../Source/iruna_sound_Device.h"

/*----�f�[�^�^�錾-------------------------------------------------*/
namespace iruna
{
namespace sound
{
// �R���X�g���N�^
StreamSound::StreamSound()
{
	voice		= NULL;
	memset( &buffer, 0, ( sizeof buffer[0] ) * BUFFER_NUM );
	return;
}
// �f�X�g���N�^
StreamSound::~StreamSound()
{
	Release();
	return;
}
// �������
void StreamSound::Release()
{
	// ����Ă��Ȃ�
	if( voice == NULL )
	{
		return;
	}

	if( voice )
	{
		voice->DestroyVoice();
		voice = NULL;
	}

	for( int i = 0; i < BUFFER_NUM; i++ )
	{
		SafeArrayDelete( buffer[i] );
	}

	SafeDelete( decoder );

	return;
}
// �T�E���h�t�@�C���̓ǂݍ���
int StreamSound::LoadSound( std::string path )
{
	HRESULT					result;
	WAVEFORMATEX			format;
	decoder					= new OggDecoder;

	
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

	
	result = SoundDevice::GetDevice()->CreateSourceVoice(
		&voice,
		&format,
		0,
		4.0f,
		this,
		NULL,
		NULL
	);


	if( FAILED( result ) )
	{
		return -4;
	}

	// �o�^�����t�H�[�}�b�g����o�b�t�@�̃T�C�Y�����߂�
	bufferSize = format.nAvgBytesPerSec / 10;

	// ���߂��o�b�t�@�̃T�C�Y�����������m��
	for( int i = 0; i < BUFFER_NUM; i++ )
	{
		buffer[i] = new U_CHAR[ bufferSize ];
	}

	// ���߂��o�b�t�@�̏�����T�E���h�t�@�C���̍Đ�
	OnVoiceProcessingPassStart( bufferSize );

	return 0;
}
// �T�E���h�t�@�C���̍Đ�
int StreamSound::PlaySound(int loopPos )
{
	this->loopPos = loopPos;

	return voice->Start();
}
// �T�E���h�t�@�C���̃o�b�t�@�̈ʒu��0�ɖ߂�
void StreamSound::StopSound()
{
	voice->Stop();
	voice->FlushSourceBuffers();
	decoder->Seek( 0 );
}

//	�T�E���h�t�@�C���̒�~
int StreamSound::PauseSound()
{
	return voice->Stop();
}

// ���ʂ̐ݒ�
int StreamSound::SetVolume(float setVolume)
{
	return voice->SetVolume( setVolume );
}
// �Đ��X�s�[�h�̐ݒ�
int StreamSound::SetSpeedRatio( float ratio )
{
	return voice->SetFrequencyRatio( ratio );
}
void WINAPI StreamSound::OnVoiceProcessingPassStart( UINT32 requiredSize )
{
	XAUDIO2_BUFFER		bufInfo		= { 0 };

	if( requiredSize == 0 )
		return;

	std::swap( buffer[0], buffer[1] );

	bufInfo.AudioBytes	= decoder->Decode( buffer[0], bufferSize );
	bufInfo.pAudioData	= buffer[0];

	if( bufInfo.AudioBytes == 0 )
		return;

	if( decoder->EndStream() ){
		if( loopPos < 0 )
			bufInfo.Flags = XAUDIO2_END_OF_STREAM;
		else
			decoder->Seek( loopPos );
	}

	voice->SubmitSourceBuffer( &bufInfo );

	return;
}
void WINAPI StreamSound::OnVoiceProcessingPassEnd()
{
	return;
}
void WINAPI StreamSound::OnStreamEnd()
{
	voice->Stop();
	decoder->Seek( 0 );
	return;
}
void WINAPI StreamSound::OnBufferStart( void* bufContext )
{
	( void* )bufContext;
	return;
}
void WINAPI StreamSound::OnBufferEnd( void* bufContext )
{
	( void* )bufContext;
	return;
}
void WINAPI StreamSound::OnLoopEnd( void* bufContext )
{
	( void* )bufContext;
	return;
}
void WINAPI StreamSound::OnVoiceError( void* bufContext, HRESULT error )
{
	( void* )bufContext;
	( void* )error;
	return;
}

}	//	sound	end
}	//	iruna	end