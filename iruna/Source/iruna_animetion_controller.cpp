
/*----�C���N���[�h------------------------------------------------*/
#include "../Include/iruna_animetion_controller.h"
#include "../Source/iruna_animetion_base.h"
#include "../Source/iruna_animetion_pmd.h"

/*----�f�[�^�^-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
AnimetionController::AnimetionController()
	:	animetion( NULL )
{
	return;
}

//	�f�X�g���N�^
AnimetionController::~AnimetionController()
{
	SafeDelete( animetion );
	return;
}

//	�X�L�j���O�A�j���[�V���������郂�f���f�[�^�̃Z�b�g
void AnimetionController::SetModelData( ModelData* in_data )
{
	foumatType = in_data->type;

	//	�t�H�[�}�b�g�ʂɃA�j���[�V����
	switch( foumatType )
	{
	case Fbx:

		break;
	case Pmd:
		
		animetion = new PmdAnimetion( in_data );
		break;

	case Sgd:
		
		break;

	};
	return;
}

//	�A�j���[�V�����f�[�^�̓ǂݍ���
void AnimetionController::LoadAnimetion( std::string in_path )
{
	int size = in_path.size();
	int npos = in_path.rfind( '.', size );
	int type = -1;
	char temp[ 5 ];
	
	temp[ 4 ] = '\0';

	for(  int i = 0; i < 4;i++ )
	{
		temp[ i ] = in_path[ npos + i ];
	}

	
	if( foumatType == Pmd &&
		strcmp( temp, ".vmd" ) == 0)
	{
		animetion->Load( in_path );
	}

	return;
}

//	�L�[�t���[���̐ݒ�
void AnimetionController::SetKeyFlame( int in_flame )
{
	if( in_flame < 0 )
		return;

	animetion->SetAnimetion( in_flame );
	return;
}

//	�Z�b�g�������f���f�[�^�̕`��
void AnimetionController::CSgdModel(iruna::math::Vector3 pos)
{
	if( animetion == NULL )
		return;

	animetion->Render( pos );
	return;
}

}	//	graphics	end
}	//	iruna		end