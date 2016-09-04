//---------------------------------------------------------
// 
//	iruna_memory_sound.h
//	サウンドのメモリ展開再生
//	作成日 9月6日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_memory_sound.h"
#include "../Source/iruna_ogg.h"
#include "../Source/iruna_sound_Device.h"

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace sound
{

// コピー禁止用コピーコンストラクタ
MemorySound::MemorySound( const MemorySound &dummy )
{
	( void )dummy;
	return;
}

// コピー禁止用＝演算子のオーバーロード
const MemorySound& MemorySound::operator =( const MemorySound &dummy )
{
	return dummy;
}

//	コンストラクタ
MemorySound::MemorySound()
{
	voice = NULL;
	return;
}

//	デストラクタ
MemorySound::~MemorySound()
{
	Release();
	return;
}
//	サウンドメモリの解放
void MemorySound::Release()
{
	if( voice == NULL )
		return;

	voice->DestroyVoice();
	voice = NULL;

	SafeArrayDelete( buffer );

	return;

}

// サウンド再生クラスの作成
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

// サウンドに必要なメモリの作成
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

// 指定したサウンドファイルをメモリ領域に格納する
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

//	メモリに展開したサウンドデータの再生
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

// 再生を止める
int MemorySound::StopSound()
{
	return voice->Stop();
}

//	音量を設定する
int MemorySound::SetVolume( float setVolume )
{
	return voice->SetVolume( setVolume );
}

//	再生スピードを設定する
int MemorySound::SetSpeedRatio( float ratio )
{
	return voice->SetFrequencyRatio( ratio );
}

}	//	sound	end
}	//	iruna	end