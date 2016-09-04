//---------------------------------------------------------
// 
//	iruna_stream_sound.cpp
//	サウンドのストリーム再生
//	作成日 7月10日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_stream_sound.h"
#include "../Source/iruna_ogg.h"
#include "../Source/iruna_sound_Device.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace sound
{
// コンストラクタ
StreamSound::StreamSound()
{
	voice		= NULL;
	memset( &buffer, 0, ( sizeof buffer[0] ) * BUFFER_NUM );
	return;
}
// デストラクタ
StreamSound::~StreamSound()
{
	Release();
	return;
}
// 解放処理
void StreamSound::Release()
{
	// 作られていない
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
// サウンドファイルの読み込み
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

	// 登録したフォーマットからバッファのサイズを求める
	bufferSize = format.nAvgBytesPerSec / 10;

	// 求めたバッファのサイズ分メモリを確保
	for( int i = 0; i < BUFFER_NUM; i++ )
	{
		buffer[i] = new U_CHAR[ bufferSize ];
	}

	// 求めたバッファの所からサウンドファイルの再生
	OnVoiceProcessingPassStart( bufferSize );

	return 0;
}
// サウンドファイルの再生
int StreamSound::PlaySound(int loopPos )
{
	this->loopPos = loopPos;

	return voice->Start();
}
// サウンドファイルのバッファの位置を0に戻す
void StreamSound::StopSound()
{
	voice->Stop();
	voice->FlushSourceBuffers();
	decoder->Seek( 0 );
}

//	サウンドファイルの停止
int StreamSound::PauseSound()
{
	return voice->Stop();
}

// 音量の設定
int StreamSound::SetVolume(float setVolume)
{
	return voice->SetVolume( setVolume );
}
// 再生スピードの設定
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