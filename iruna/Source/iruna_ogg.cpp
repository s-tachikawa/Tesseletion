//---------------------------------------------------------
// 
//	iruna_ogg.cpp
//	Ogg�̓ǂݍ��݂ƊǗ�
//	�쐬�� 7��9��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_ogg.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u��`-------------------------------------------------*/
#ifdef _DEBUG
#pragma comment( lib, "libogg_static_d.lib" )
#pragma comment( lib, "libvorbis_static_d.lib" )
#pragma comment( lib, "libvorbisfile_static_d.lib" )
#else
#pragma comment( lib, "libogg_static.lib" )
#pragma comment( lib, "libvorbis_static.lib" )
#pragma comment( lib, "libvorbisfile_static.lib" )
#endif

/*----�f�[�^�^�錾-------------------------------------------------*/
namespace iruna
{
namespace sound
{
//	�R���X�g���N�^
OggDecoder::OggDecoder()
		:	open( false )
{
	return;
}
//	�f�X�g���N�^
OggDecoder::~OggDecoder()
{
	Close();
	return;
}
//	Ogg�t�@�C���̓ǂݍ���
int OggDecoder::Open(std::string path, WAVEFORMATEX& format)
{
	// �t�@�C���|�C���^�̏�����
	FILE*		temp		= NULL;

	// ���������s
	if( open )
	{
		return -1;
	}

	// �o�C�i���f�[�^�Ƃ��ĊJ��
	if( fopen_s( &temp, path.c_str(), "rb" ) )
	{
		return -2;
	}

	// Ogg�t�@�C�����J���t�@�C���|�C���^�Ɉڂ�
	if( ov_open( temp, &fpOgg, NULL, 0 ) )
	{
		fclose( temp );
		return -3;
	}

	// �t���O�𗧂Ă�
	open = true;

	// �t�@�C���t�H�[�}�b�g�̎擾
	GetOutFormat( format );
	// �ǂݍ��ݐ���
	return 0;
}
//	Ogg�t�@�C���̉��
void OggDecoder::Close()
{
	// Ogg�̃t�@�C���|�C���^�����
	ov_clear( &fpOgg );
	// �t���O��߂�
	open = false;
	return;
}
// �o�b�t�@����w��̃T�C�Y��ǂݏo��
int OggDecoder::Decode( U_CHAR *buf, U_INT size)
{
	// �ǂݍ��ރo�b�t�@�̃T�C�Y��������
	U_INT	readSize		= 0;

	// ov_read�֐���4096�Â����o�b�t�@���擾���Ă���Ȃ����߂��̕�����
	size -= 4096;

	// 8��ȏ�񂷂ƃX�g���[���Đ����ɏ������d���Ȃ��Ă��܂��̂�
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

		//	�ǂݍ��ރT�C�Y���K��T�C�Y���傫���Ȃ�����
		if( readSize > size )
			break;
	}

	// �ǂݍ��񂾃T�C�Y��Ԃ�
	return readSize;
}
// �I�t�Z�b�g���o�b�t�@���ړ�������
void OggDecoder::Seek(int offset)
{
	// �w�肵���o�b�t�@���ړ�������
	ov_pcm_seek( &fpOgg, offset );
	return;
}
// �X�g���[�����I��������ǂ������肷��
bool OggDecoder::EndStream()
{
	if( ov_pcm_total( &fpOgg, 0 ) - ov_pcm_tell( &fpOgg ) < 4096 )
	{
		// �w�肳��Ă���T�C�Y�ɗ��Ă�����X�g���[�����I����Ă���
		return true;
	}

	// �܂��X�g���[�����I����ĂȂ�
	return false;
}
// �o�b�t�@�̒������擾
U_INT OggDecoder::GetLength()
{
	// Ogg�t�@�C���̒�����Ԃ�
	return static_cast<unsigned long>( ov_pcm_total( &fpOgg, -1 ) );
}
// Ogg�t�@�C������t�H�[�}�b�g�̎擾
void OggDecoder::GetOutFormat(WAVEFORMATEX& format)
{
	const vorbis_info*	info	= ov_info( &fpOgg, -1 );

	format.wFormatTag			= WAVE_FORMAT_PCM;
	format.nChannels			= ( WORD )info->channels;								// �r�b�g�X�g���[���̃`�����l����
	format.nSamplesPerSec		= info->rate;									// �T���v�����O���[�g
	format.nAvgBytesPerSec		= info->channels * info->rate * SAMPLE_BYTES;
	format.nBlockAlign			= ( WORD )info->channels * SAMPLE_BYTES;
	format.wBitsPerSample		= SAMPLE_BITS;
	format.cbSize				= 0;

	return;
}


}	//	sound	end
}	//	iruna	end