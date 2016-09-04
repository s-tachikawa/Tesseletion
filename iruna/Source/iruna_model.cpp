////---------------------------------------------------------
//// 
////	iruna_model.cpp
////	�Œ胁�b�V�����f���N���X
////	�쐬�� 6��27��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Include/iruna_model.h"
//#include "../Source/iruna_device.h"
//
//namespace iruna
//{
//namespace graphics
//{
//// �R���X�g���N�^
//Model::Model()
//		:mesh			( 0 ),
//		material		( 0 ),
//		texture			( 0 ),
//		materialCount	( 0 )
//{
//	return;
//}
//
////	�f�X�g���N�^
//Model::~Model()
//{
//	SafeArrayDelete( material );
//	SafeArrayDelete( texture );
//	SafeRelease( mesh );
//	recoveryPath.clear();
//}
//
////	���f���̓ǂݍ���
//bool Model::Load( std::string path )
//{
//	LPD3DXBUFFER	materialTemp	= 0;
//	D3DXMATERIAL*	materialInfo	= 0;
//
//	if( FAILED( D3DXLoadMeshFromX(
//			path.c_str(),
//			D3DXMESH_SYSTEMMEM,
//			Device::GetDevice(),
//			0,
//			&materialTemp,
//			0,
//			&materialCount,
//			&mesh ) ) )
//	{
//		//	�ǂݍ��ݎ��s
//		return false;
//	}
//
//	//	�ǂݍ���Xfile�����Ƀ��f�����\��
//	materialInfo	= reinterpret_cast< D3DXMATERIAL* >( materialTemp->GetBufferPointer() );
//	material		= new Material[ materialCount ];
//	texture			= new Texture[ materialCount ];
//	recoveryPath	= path;
//
//	//	�}�e���A���̐��������}�e���A���ƃe�N�X�`���[��ǂݍ���
//	for( U_LONG i = 0; i < materialCount; i++ )
//	{
//		material[ i ]			= materialInfo[ i ].MatD3D;
//		material[ i ].ambient	= Color4F( 1.f, 1.f, 1.f, 1.f );
//
//		if( materialInfo[ i ].pTextureFilename != NULL )
//		{
//			std::string	temp	= materialInfo[ i ].pTextureFilename;
//			path.erase( 1 + path.find_last_of( '/' ) );
//
//			texture[ i ].Load( ( path + temp ).c_str() );
//		}
//	}
//
//	SafeRelease( materialTemp );
//
//	//	�ǂݍ��ݐ���
//	return true;
//}
//
////	���f���̕`��
//bool Model::Draw( U_LONG count )
//{
//	return SUCCEEDED( mesh->DrawSubset( count ) );
//}
//
//bool Model::RemakeVertexFormat( const VertexDeclaration::Element* element )
//{
//	LPD3DXMESH meshTemp;
//
//	if( FAILED( mesh->CloneMesh( mesh->GetOptions(),
//								 element,
//								 Device::GetDevice(),
//								 &meshTemp ) ) )
//	{
//		//	���_�t�H�[�}�b�g�̍쐬�Ɏ��s
//		return false;
//	}
//	SafeRelease( mesh );
//
//	//	�V���ɍ쐬�������b�V�����R�s�[
//	mesh	= meshTemp;
//
//	//	���_�t�H�[�}�b�g�̍č쐬�ɐ���
//	return true;
//}
//
////	�}�e���A���̐��擾
//U_LONG Model::GetMaterialCount()
//{
//	return materialCount;
//}
//
//// �}�e���A���̎擾
//const Material* Model::GetMaterial( U_LONG count )
//{
//	// �}�e���A���̐��𒴂��Ă��Ȃ���
//	if( count < materialCount )
//	{
//		return &material[ count ];
//	}
//	return 0;
//}
//
//// �e�N�X�`���[�̎擾
//const LPDIRECT3DTEXTURE9 Model::GetTexture( U_LONG count )
//{
//	// �}�e���A���̐��𒴂��Ă��Ȃ���
//	if( count < materialCount ) 
//	{
//		return texture[ count ].GetTexture();
//	}
//
//	return 0;
//}
//
//}
//}