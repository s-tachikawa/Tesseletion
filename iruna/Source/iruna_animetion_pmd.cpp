
/*----�C���N���[�h------------------------------------------------*/
#include "../Source/iruna_animetion_pmd.h"
#include "../Include/iruna_math.h"

/*----�f�[�^�^-------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
PmdAnimetion::PmdAnimetion( ModelData* in_data )
{
	data = in_data;

	shader = new PmdShader( in_data );
	
	return;
}

//	�f�X�g���N�^
PmdAnimetion::~PmdAnimetion()
{
	SafeDelete( shader );
	return;
}

//	�A�j���[�V�����f�[�^�̓ǂݍ���
int PmdAnimetion::Load( std::string in_path )
{

	FILE* fp = NULL;

	fp = fopen( in_path.c_str() , "rb" );

	if( fp == NULL )
		return -1;

	const int FLAME_LATE = 60;		//	�{�v���O�����̃t���[�����[�g
	const int MMD_FLAME_RATE = 30;	//	MMD��ł̃t���[�����[�g

	//�ǂݍ��݊J�n
	//���[�V�����J�E���g�̎擾
	char vmdHeder[ 30 ];
	char vmdModel[ 20 ];
	//�w�b�_�[�̓ǂݍ���
	fread( vmdHeder , sizeof( char ),30,fp );
	//���f�����̓ǂݍ���
	fread( vmdModel , sizeof( char ),20,fp );
	//���[�V�����J�E���g
	DWORD motionCount;
	
	fread( &motionCount , sizeof( DWORD ),1,fp );

	int boneCount = data->mesh[ 0 ]->boneCount;

	AnimetionData.resize( boneCount );

	for( int i = 0;i <  (int)motionCount;i++)
	{
		VmdMotionData tempData;

		math::Matrix rote;
		math::Matrix scl;
		math::Matrix trn;
		//	�K��������{�[�����̓ǂݍ���
		char buf[ 15 ];
		fread( buf,sizeof( char ),15,fp );
		tempData.boneName = buf;

		//	�t���[���ԍ��̓ǂݍ���
		fread( &tempData.freamIndex,sizeof( DWORD ),1,fp );
		tempData.freamIndex *= FLAME_LATE / MMD_FLAME_RATE;

		math::Vector3 tempVec;
		fread( &tempVec,sizeof( float ) * 3,1,fp );
		tempData.mTransform = math::Vector4( tempVec.x, tempVec.y, tempVec.z, 1.0f );
		tempData.mTransform.w = 1.0f;

		fread( &tempData.mQuaternion,sizeof( float ) * 4,1,fp );
		//�⊮�̃p�����[�^�ǂݍ���
		unsigned char num[ 64 ];
		fread( num , sizeof( unsigned char ),64,fp );

		//��]�s��̍쐬
		D3DXMatrixRotationQuaternion( &rote,&tempData.mQuaternion );

		D3DXMatrixTranslation( &trn,	tempData.mTransform.x,
										tempData.mTransform.y,
										tempData.mTransform.z);
		
		tempData.mTransformMat = rote * trn;
		//�f�[�^�̊i�[(�{�[���ɑΉ��������[�V�����f�[�^���i�[)
		for( int  k = 0; k < boneCount; k++ )
		{
			std::string tempName = data->mesh[ 0 ]->bone[ k ].boneName;
			if( tempData.boneName == data->mesh[ 0 ]->bone[ k ].boneName )
			{
				AnimetionData[ k ].push_back( tempData );

			}
		}
		//�ő�t���[�����̎Z�o
		if( tempData.freamIndex >  max_flame)
			max_flame = tempData.freamIndex;
	}
	
	//	�e�{�[���̃��[�V�����f�[�^���t���[�����Ƀ\�[�g
	for( int i = 0; i < boneCount; i++ )
	{
		for( int k = 0; k < ( int )AnimetionData[ i ].size(); k++ )
		{
			std::sort( AnimetionData[ i ].begin(), AnimetionData[ i ].end() );

		}

		bonePos.push_back( math::Vector3( 0, 0, 0 ) );
		boneRot.push_back( math::Quaternion( 0, 0, 0, 0 ) );
	}

	//�ǂݍ��ݏI��
	fclose( fp );

	return 0;
}

//	�A�j���[�V�����̐ݒ肷��
bool PmdAnimetion::SetAnimetion( int flame )
{
	int boneCount = data->mesh[ 0 ]->boneCount;

	//	�{�[���̍X�V
	math::WoldMatrix world;
	for( int i = 0; i < data->mesh[ 0 ]->boneCount; i++ )
	{
		if( data->mesh[ 0 ]->bone[ i ].parentId == 0xffff )
			data->mesh[ 0 ]->bone[ i ].BoneUpDate( world.GetWoldMatrix() );
	}

	//	�w�肳�ꂽ�t���[��������`��ԂƋ��ʐ��`��Ԃ�����
	for( int i = 0; i < boneCount; i++ )
	{
		int t0 = 0, t1 = 0;
		int	framePos = 0;
		math::Quaternion q0, q1;
		math::Vector3 p0, p1;

		for( int k = 0; k < ( int )AnimetionData[ i ].size(); k++ )
		{
			//	���݂̃t���[������t0�̈ʒu�����߂�
			if( flame >= AnimetionData[ i ][  k ].freamIndex )
			{
				t0 = AnimetionData[ i ][  k ].freamIndex;
				bonePos[ i ] = p0 = math::Vector3(	AnimetionData[ i ][ k ].mTransform.x,
													AnimetionData[ i ][ k ].mTransform.y,
													AnimetionData[ i ][ k ].mTransform.z);
				boneRot[ i ] = q0 = AnimetionData[ i ][ k ].mQuaternion;
				framePos = k;
			}

			if( ( int )AnimetionData[ i ].size() > framePos + 1 )
			{
				t1 = AnimetionData[ i ][  framePos + 1 ].freamIndex;
				q1 = AnimetionData[ i ][  framePos + 1 ].mQuaternion;
				p1 = math::Vector3( AnimetionData[ i ][  framePos + 1 ].mTransform.x,
									AnimetionData[ i ][  framePos + 1 ].mTransform.y,
									AnimetionData[ i ][  framePos + 1 ].mTransform.z);
			}
			else
			{
				t1 = AnimetionData[ i ][  framePos ].freamIndex;
				q1 = AnimetionData[ i ][  framePos ].mQuaternion;
				p1 = math::Vector3( AnimetionData[ i ][  framePos ].mTransform.x,
									AnimetionData[ i ][  framePos ].mTransform.y,
									AnimetionData[ i ][  framePos ].mTransform.z);
			}

			//	�t���[������`��Ԃ���
			float s = ( float )( flame - t0 ) / ( float )( t1 - t0 );
			//	���`��Ԃ������Ԃŕ��s�ړ��s��Ɖ�]�s����쐬����
			D3DXQuaternionSlerp( &boneRot[ i ], &q0, &q1, s );		//	�N�H�[�^�j�I���̕��
			bonePos[ i ] = p0 + ( p1 - p0 ) * s;					//	���s�ړ��̐��`���
		}
		math::Matrix rot, trans;
		D3DXMatrixRotationQuaternion( &rot, &boneRot[ i ] );
		D3DXMatrixTranslation( &trans,	bonePos[ i ].x,
										bonePos[ i ].y,
										bonePos[ i ].z);

		data->mesh[ 0 ]->bone[ i ].tran = rot * trans * data->mesh[ 0 ]->bone[ i ].init;
		math::Matrix temp = data->mesh[ 0 ]->bone[ i ].tran;

	}

	//	IK�{�[���̍X�V
	for( int i = 0; i < data->mesh[ 0 ]->ikBoneCount; i++ )
		data->mesh[ 0 ]->ikBone[ i ].IkUpdate( data->mesh[ 0 ]->bone );

	//	�X�L�j���O�s��̍쐬
	for( int i = 0; i < data->mesh[ 0 ]->boneCount; i++ )
	{
		if( data->mesh[ 0 ]->bone[ i ].parentId == 0xffff )
			data->mesh[ 0 ]->bone[ i ].BoneUpDate( world.GetWoldMatrix() );
	}

	return true;
}

//	���f���̃����_�����O
void PmdAnimetion::Render( math::Vector3 pos )
{
	shader->Render( pos );
	return;
}


}	//	graphics	end
}	//	iruna		end