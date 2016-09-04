//---------------------------------------------------------
// 
//	iruna_ogg.cpp
//	Oggの読み込みと管理
//	作成日 7月9日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_ogg.h"

/*----プリプロセッサディレクティブ定義-------------------------------------------------*/
#ifdef _DEBUG
#pragma comment( lib, "libogg_static_d.lib" )
#pragma comment( lib, "libvorbis_static_d.lib" )
#pragma comment( lib, "libvorbisfile_static_d.lib" )
#else
#pragma comment( lib, "libogg_static.lib" )
#pragma comment( lib, "libvorbis_static.lib" )
#pragma comment( lib, "libvorbisfile_static.lib" )
#endif

/*----データ型宣言-------------------------------------------------*/
namespace iruna
{
namespace sound
{
//	コンストラクタ
OggDecoder::OggDecoder()
		:	open( false )
{
	return;
}
//	デストラクタ
OggDecoder::~OggDecoder()
{
	Close();
	return;
}
//	Oggファイルの読み込み
int OggDecoder::Open(std::string path, WAVEFORMATEX& format)
{
	// ファイルポインタの初期化
	FILE*		temp		= NULL;

	// 初期化失敗
	if( open )
	{
		return -1;
	}

	// バイナリデータとして開く
	if( fopen_s( &temp, path.c_str(), "rb" ) )
	{
		return -2;
	}

	// Oggファイルを開きファイルポインタに移す
	if( ov_open( temp, &fpOgg, NULL, 0 ) )
	{
		fclose( temp );
		return -3;
	}

	// フラグを立てる
	open = true;

	// ファイルフォーマットの取得
	GetOutFormat( format );
	// 読み込み成功
	return 0;
}
//	Oggファイルの解放
void OggDecoder::Close()
{
	// Oggのファイルポインタを解放
	ov_clear( &fpOgg );
	// フラグを戻す
	open = false;
	return;
}
// バッファから指定のサイズを読み出す
int OggDecoder::Decode( U_CHAR *buf, U_INT size)
{
	// 読み込むバッファのサイズを初期化
	U_INT	readSize		= 0;

	// ov_read関数が4096づつしかバッファを取得してくれないためその分引く
	size -= 4096;

	// 8回以上回すとストリーム再生時に処理が重くなってしまうので
	for( int i = 0; i < 8; i++ ){
		readSize += ov_read(
			&fpOgg,
			reinterpret_cast<char*>( buf + readSize ),
			size,
			0,
			sizeof WORD,
			1,
			NULL
		);

		//	読み込むサイズが規定サイズより大きくなったら
		if( readSize > size )
			break;
	}

	// 読み込んだサイズを返す
	return readSize;
}
// オフセット分バッファを移動させる
void OggDecoder::Seek(int offset)
{
	// 指定したバッファ分移動させる
	ov_pcm_seek( &fpOgg, offset );
	return;
}
// ストリームが終わったかどうか判定する
bool OggDecoder::EndStream()
{
	if( ov_pcm_total( &fpOgg, 0 ) - ov_pcm_tell( &fpOgg ) < 4096 )
	{
		// 指定されているサイズに来ていたらストリームが終わっている
		return true;
	}

	// まだストリームが終わってない
	return false;
}
// バッファの長さを取得
U_INT OggDecoder::GetLength()
{
	// Oggファイルの長さを返す
	return static_cast<unsigned long>( ov_pcm_total( &fpOgg, -1 ) );
}
// Oggファイルからフォーマットの取得
void OggDecoder::GetOutFormat(WAVEFORMATEX& format)
{
	const vorbis_info*	info	= ov_info( &fpOgg, -1 );

	format.wFormatTag			= WAVE_FORMAT_PCM;
	format.nChannels			= ( WORD )info->channels;								// ビットストリームのチャンネル数
	format.nSamplesPerSec		= info->rate;									// サンプリングレート
	format.nAvgBytesPerSec		= info->channels * info->rate * SAMPLE_BYTES;
	format.nBlockAlign			= ( WORD )info->channels * SAMPLE_BYTES;
	format.wBitsPerSample		= SAMPLE_BITS;
	format.cbSize				= 0;

	return;
}


}	//	sound	end
}	//	iruna	end