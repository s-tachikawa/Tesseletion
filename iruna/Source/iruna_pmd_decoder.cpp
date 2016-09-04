////---------------------------------------------------------
//// 
////	iruna_fbx_decoder.cpp
////	FBX�t�@�C���ǂݍ��݃N���X������
////	�쐬�� 10��21��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h---------------------------------*/
//#include "../Source/iruna_pmd_decoder.h"
//
//
//namespace iruna
//{
//namespace graphics
//{
//
////	�R���X�g���N�^
//PmdDecoder::PmdDecoder()
//	:	saveData( NULL )
//{
//	return;
//}
//PmdDecoder::~PmdDecoder()
//{
//
//	Relese();
//
//	return;
//}
//
////	�f�X�g���N�^
//void PmdDecoder::Relese()
//{
//	if( saveData == NULL )return;
//
//	for( int i = 0; i < ( int )saveData->mesh.size(); i++ )
//	{
//		SafeArrayDelete( saveData->mesh[ i ]->blending );
//		SafeArrayDelete( saveData->mesh[ i ]->vertex );
//		SafeArrayDelete( saveData->mesh[ i ]->index );
//		for( int k = 0; k < saveData->mesh[ i ]->countData.materialCount; k++ )
//		{
//			SafeDelete( saveData->mesh[ i ]->material[ k ].indexBuffer );
//			
//			if( saveData->mesh[ i ]->material[ k ].tex != NULL )
//				SafeDelete( saveData->mesh[ i ]->material[ k ].tex );
//		}
//		SafeArrayDelete( saveData->mesh[ i ]->material );
//		SafeArrayDelete( saveData->mesh[ i ]->vertexBuffer );
//		SafeArrayDelete( saveData->mesh[ i ]->bone );
//		SafeArrayDelete( saveData->mesh[ i ]->ikBone );
//		//SafeDelete( saveData->mesh[ i ]->indexBuffer );
//
//		SafeDelete( saveData->mesh[ i ] );
//	}
//
//	SafeDelete( saveData );
//	return;
//}
//
//// ���f���֘A�̏�����
//void PmdDecoder::Init()
//{
//	
//	saveData	= new ModelData;
//
//	saveData->meshCount = 0;
//
//	return;
//}
//bool PmdDecoder::Decode( std::string in_path, int in_type )
//{
//	FILE* fp;
//
//	fp = fopen( in_path.c_str(), "rb" );
//
//	//�w�b�_�p�̕ϐ�
//	char			magic[ 3 ];			//	PMD�t�H�[�}�b�g
//	float			version;			//	PMD�t�@�C���̃o�[�W����
//	char			model_name[ 20 ];	//	���f���l�[��
//	char			comment[ 256 ];		//	���f���΂���R�����g
//
//	//	PMD���f���ɓǂݍ���
//	fp = fopen(  in_path.c_str(), "rb");
//
//	//	�ǂݍ��ݎ��s
//	if(fp == NULL)return false;
//	
//	//�w�b�_�̓ǂݍ���
//	fread( magic, sizeof( char ), 3, fp );
//	fread( &version, sizeof( float ), 1, fp );
//	fread( model_name, sizeof( char ), 20, fp );
//	fread( comment, sizeof( char ) ,256 ,fp );
//	//	���b�V���J�E���g(PMD�͂��Ԃ񃁃b�V����1�����Ȃ��Ǝv��)
//	saveData->meshCount = 1;
//	//	���f���^�C�v
//	saveData->type		= in_type;
//
//	MeshData* tempMesh = new MeshData;
//
//	//���_���̓ǂݍ���
//	DWORD vertexCount = 0;
//	fread( &vertexCount, sizeof( DWORD ),1,fp);
//	tempMesh->countData.vertexCount = vertexCount;
//
//	//	���_�f�[�^�̓ǂݍ���
//	tempMesh->vertex		= new VertexData[ vertexCount ];
//	tempMesh->blending	= new VertexBlending[ vertexCount ];
//
//	math::Vector3*	pos				= new math::Vector3[ vertexCount ];
//	math::Vector3*	normal			= new math::Vector3[ vertexCount ];
//	math::Vector2*	uv				= new math::Vector2[ vertexCount ];
//	math::Vector4*	weight			= new math::Vector4[vertexCount ];
//	BoneIndex*		boneIndex		= new BoneIndex[ vertexCount ];
//
//	for( int i = 0; i < tempMesh->countData.vertexCount; i++ )
//	{
//		//	���_�f�[�^
//		fread( pos[ i ],	sizeof( float ) * 3, 1, fp );
//		fread( normal[ i ],	sizeof( float ) * 3, 1, fp );
//		fread( uv[ i ],		sizeof( float ) * 2, 1, fp );
//
//		tempMesh->vertex[ i ].pos	= pos[ i ];
//		tempMesh->vertex[ i ].normal = normal[ i ];
//		tempMesh->vertex[ i ].uv		= uv[ i ];
//		
//		//	���_�E�F�C�g(PMD�͒��_�ɉe����^����{�[����2�܂ł����Ȃ�)
//		WORD indexTemp[ 2 ] = { 0 };
//		BYTE whigtTemp = 0;
//
//		fread( indexTemp,									sizeof( WORD ) * 2, 1, fp );
//		fread( &whigtTemp,									sizeof( BYTE ), 1, fp );
//		
//		tempMesh->blending[ i ].boneIndex[ 0 ] = indexTemp[ 0 ];
//		tempMesh->blending[ i ].boneIndex[ 1 ] = indexTemp[ 1 ];
//		boneIndex[ i ].indexOne = ( int )indexTemp[ 0 ];
//		boneIndex[ i ].indexTwo = ( int )indexTemp[ 1 ];
//
//		tempMesh->blending[ i ].wighte[ 0 ]	= whigtTemp * 0.01f;
//		tempMesh->blending[ i ].wighte[ 1 ] = 1.0f - tempMesh->blending[ i ].wighte[ 0 ];
//		
//		weight[ i ]							= math::Vector4( whigtTemp, 1.0f - whigtTemp, 0.0f, 0.0f );
//
//		//�G�b�W�t���O�̓ǂݍ���(�ǂݔ�΂�)
//		BYTE e;
//		fread(&e,sizeof( BYTE ) ,1,fp);
//	}
//	//	VertexBuffer�̍쐬
//	tempMesh->vertexBuffer = new VertexBuffer[ 5 ];
//	tempMesh->vertexBuffer[ 0 ].Create( VertexBuffer::FLOAT3, vertexCount );
//	tempMesh->vertexBuffer[ 1 ].Create( VertexBuffer::FLOAT3, vertexCount );
//	tempMesh->vertexBuffer[ 2 ].Create( VertexBuffer::FLOAT2, vertexCount );
//	tempMesh->vertexBuffer[ 3 ].Create( VertexBuffer::FLOAT4, vertexCount );
//	tempMesh->vertexBuffer[ 4 ].Create( VertexBuffer::UBYTE4, vertexCount );
//
//	//	Buffer�ɃZ�b�g
//	tempMesh->vertexBuffer[ 0 ].SetBuffer( pos,			0, vertexCount );
//	tempMesh->vertexBuffer[ 1 ].SetBuffer( normal,		0, vertexCount );
//	tempMesh->vertexBuffer[ 2 ].SetBuffer( uv,			0, vertexCount );
//	tempMesh->vertexBuffer[ 3 ].SetBuffer( weight,		0, vertexCount );
//	tempMesh->vertexBuffer[ 4 ].SetBuffer( boneIndex,	0, vertexCount );
//
//	SafeArrayDelete( pos );
//	SafeArrayDelete( normal );
//	SafeArrayDelete( uv );
//	SafeArrayDelete( weight );
//	SafeArrayDelete( boneIndex );
//	
//	//	�C���f�b�N�X�����擾
//	DWORD index_count = 0;
//	fread( &index_count,	sizeof( int ), 1, fp );
//	tempMesh->countData.indexCount = index_count;
//	tempMesh->index = new int[ index_count ];
//	WORD* index_buf_temp = new WORD[ index_count ];
//
//	//	�C���f�b�N�X�f�[�^�̎擾
//	for( int i = 0; i < ( int )index_count; i++ )
//	{
//		fread( &index_buf_temp[ i ], sizeof( WORD ), 1, fp );
//	}
//
//	
//	
//	//�}�e���A���̐��i�[
//	DWORD material_count = 0;
//	fread( &material_count ,sizeof( DWORD ), 1, fp);
//	tempMesh->countData.materialCount = material_count;
//
//	//�}�e���A���̓ǂݍ���
//	BYTE			toonIndex,edgeFlag;
//	DWORD			IndexVertex = 0;
//	tempMesh->material = new MaterialData[ material_count ];
//
//	for( int i = 0; i < ( int )material_count; i++ )
//	{
//		D3DCOLORVALUE	color;
//		float			power;
//
//		//	�f�B�t���[�Y
//		fread( &color, sizeof( float ) * 4, 1, fp );
//		color.a = 1.0f;
//		tempMesh->material[ i ].dxMaterial.Diffuse = color;
//
//		//	�X�y�L�����[�p���[
//		fread( &power, sizeof( float ), 1, fp );
//		tempMesh->material[ 0 ].dxMaterial.Power = power;
//
//		//	�X�y�L�����[
//		fread( &color, sizeof( float ) * 3, 1, fp );
//		color.a = power;
//		tempMesh->material[ i ].dxMaterial.Specular = color;
//		
//		//	�A���r�G���g
//		fread( &color, sizeof( float ) * 3, 1, fp);
//		color.a = 1.0f;
//		tempMesh->material[ i ].dxMaterial.Ambient = color;
//
//		//	�G�~�b�V�u
//		//tempMesh->material[ i ].material.emissive = Color4F( 1.0f,1.0f,1.0f, 1.0f );
//
//		//	�g�D�[���e�N�X�`���ւ̃C���f�b�N�X�ƃG�b�W�t�B���^�[�p�t���O
//		fread(&toonIndex,sizeof( BYTE ),1,fp);
//		fread(&edgeFlag,sizeof( BYTE ),1,fp);
//
//		//	�}�e���A���ɉ������C���f�b�N�X�o�b�t�@���쐬
//		DWORD indes_count = 0;
//		fread(&indes_count,sizeof( DWORD ),1,fp );
//		tempMesh->material[ i ].indexCount = indes_count;
//		//	�|���S�����̎Z�o
//		tempMesh->material[ i ].porygonCount = indes_count / 3;
//		tempMesh->material[ i ].indexBuffer = new IndexBuffer;
//		tempMesh->material[ i ].indexBuffer->Create( IndexBuffer::BIT16, indes_count );
//		tempMesh->material[ i ].indexBuffer->SetBuffer( &index_buf_temp[ IndexVertex ], 0, indes_count );
//
//		//	�C���f�b�N�X�̈ʒu��i�܂���
//		IndexVertex += indes_count;
//		
//		//	�e�N�X�`����
//		char buf[21] = { 0 };
//		fread( buf, sizeof( char ), 20, fp );
//
//		//	�e�N�X�`���̍쐬(�t�@�C�������Ȃ���΃e�N�X�`�����쐬���Ȃ�)
//		if( strcmp( buf, "" ) != 0 )
//		{
//			std::string fileName = buf; 
//			//tempMesh->material[ i ].texName = fileName;
//			tempMesh->material[ i ].tex = new Texture;
//			tempMesh->material[ i ].tex->Load( ( std::string("../Resource/Texture/") + fileName.c_str() ).c_str() );
//		}
//		
//	}
//
//	SafeArrayDelete( index_buf_temp );
//
//	//	�{�[���̐��擾
//	WORD boneCount = 0;
//	fread(&boneCount,sizeof( WORD ),1,fp);
//	tempMesh->boneCount = boneCount;
//
//	//	�{�[���̎擾
//	tempMesh->bone = new Bone[ boneCount ];
//
//	for( int i = 0; i < boneCount; i++ )
//	{
//		WORD parentBoneId = -1;
//		WORD childBoneId = -1;
//		BYTE boneType = 0;
//
//		//���O�̎擾
//		char bone_buf[ 20 ];
//		fread( bone_buf ,sizeof( char ), 20, fp );
//		tempMesh->bone[ i ].boneName	= bone_buf;
//		tempMesh->bone[ i ].id			= i;
//		
//		//�e�{�[���ԍ��̎擾
//		fread( &parentBoneId , sizeof( WORD ), 1, fp );
//		
//		//�q�{�[���ԍ��̎擾
//		fread( &childBoneId ,sizeof( WORD ), 1, fp );
//		tempMesh->bone[ i ].parentId	= parentBoneId;
//		tempMesh->bone[ i ].childId		= childBoneId;
//		
//		//�{�[���̃^�C�v�擾
//		fread( &boneType, sizeof( BYTE ), 1, fp );
//		
//		//IK�ԍ��̎擾
//		WORD ik_parent_bone_index = 0;
//		fread( &ik_parent_bone_index , sizeof( WORD ),1,fp );
//		tempMesh->bone[ i ].IkId = ik_parent_bone_index;
//
//		//�{�[���̃��[�J�����W�擾
//		math::Vector3 bonePos;
//		fread( &bonePos , sizeof( float ) * 3,1,fp );
//
//		//	�����p���̍s��̍쐬
//		tempMesh->bone[ i ].SetInitMatrix( bonePos );
//		tempMesh->bone[ i ].originePos = bonePos;
//	}
//
//	//	�{�[���̐e�q�֌W���쐬
//	for( int i = 0; i < boneCount; i++ )
//	{
//		//�e������Ȃ�
//		if(tempMesh->bone[ i ].parentId < boneCount)
//		{
//			//���̐e�Ɏ������q�{�[���Ƃ��ēo�^
//			tempMesh->bone[ tempMesh->bone[ i ].parentId ].child.push_back( &tempMesh->bone[ i ] );
//		}
//	}
//
//	//	���[�g�{�[������{�[���S�̂𑊑΍��W�ɕς���
//	tempMesh->bone[ 0 ].BoneRun( NULL );
//
//	//	IK�{�[���̐��̓ǂݍ���
//	WORD ikCount = 0;
//	fread( &ikCount, sizeof( WORD ), 1, fp );
//	tempMesh->ikBone = new IkBone[ ikCount ];
//	tempMesh->ikBoneCount = ikCount;
//
//	
//	//	IK�{�[���f�[�^�̓ǂݍ���
//	for( int i = 0; i < ikCount; i++ )
//	{
//		WORD ikIndex		= 0;
//		WORD ikTargetIndex	= 0;
//		BYTE chain			= 0;
//		WORD iterations		= 0;
//		float weight		= 0.0f;
//		//	IK�ԍ�
//		fread( &ikIndex, sizeof( WORD ), 1, fp );
//		//	IK�^�[�Q�b�g�{�[��
//		fread( &ikTargetIndex, sizeof( WORD ), 1, fp );
//		//	IK�{�[���e���̐[��
//		fread( &chain, sizeof( BYTE ), 1, fp );
//		//	�ċA��
//		fread( &iterations, sizeof( WORD ), 1, fp );
//		//	IK�{�[������̉e���x
//		fread( &weight, sizeof( float ), 1, fp );
//		//	IK�{�[���e������{�[���ԍ�
//		for( int k = 0; k < ( int )chain; k++ )
//		{
//			WORD childIndex = 0;
//			fread( &childIndex, sizeof( WORD ), 1, fp );
//			tempMesh->ikBone[ i ].child.push_back( childIndex );
//		}
//		//	�f�[�^���i�[
//		tempMesh->ikBone[ i ].index			= ikIndex;
//		tempMesh->ikBone[ i ].targetIndex	= ikTargetIndex;
//		tempMesh->ikBone[ i ].length		= chain;
//		tempMesh->ikBone[ i ].iterations	= iterations;
//		tempMesh->ikBone[ i ].weight		= weight;
//		tempMesh->ikBone[ i ].boneCount		= tempMesh->boneCount;
//	}
//
//	//	���b�V����ǉ�
//	saveData->mesh.push_back( tempMesh );
//
//	fclose( fp );
//	return true;
//}
//
//// ���f���f�[�^
//ModelData* PmdDecoder::GetModelData()
//{
//	if( saveData != NULL )
//		return saveData;
//
//	return NULL;
//}
//
//}	//	graphics	end
//}	//	iruna		end