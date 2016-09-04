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
//#include "../Source/iruna_fbx_decoder.h"
//#include "../Source/iruna_model_decoder.h"
//
///*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
//
//#ifdef _DEBUG
//#pragma comment ( lib, "fbxsdk_md2008d.lib"	)
//
//#else
//#pragma comment ( lib, "fbxsdk_md2008.lib"	)
//
//#endif
//
//#pragma comment ( lib, "wininet.lib"	)
//#pragma comment ( lib, "advapi32.lib"	)
//
//namespace iruna
//{
//namespace graphics
//{
//
////	�R���X�g���N�^
//FbxDecoder::FbxDecoder()
//	:	pSdkManager( NULL ),
//		pFbxScene( NULL ),
//		pImporter( NULL ),
//		saveData( NULL )
//{
//
//	return;
//}
//
//// �f�X�g���N�^
//FbxDecoder::~FbxDecoder()
//{
//	return;
//}
//
//// �������
//void FbxDecoder::Relese()
//{
//	//	SDK�}�l�[�W���[�̉��
//	/*
//		����������g��Ȃ���SDK���ŃG���[���N����
//	*/
//	if( pFbxScene != NULL)
//	{
//		pFbxScene->Destroy();
//		pFbxScene = NULL;
//	}
//	if( pImporter != NULL )
//	{
//		pImporter->Destroy();
//		pImporter = NULL;
//	}
//	if( pSdkManager != NULL )
//	{
//		pSdkManager->Destroy();
//		pSdkManager = NULL;
//	}
//
//	
//	if( saveData != NULL )
//	{
//		if( saveData->mesh.size() > 0 )
//		{
//			for( int i = 0; i < ( int )saveData->mesh.size();i++ )
//			{
//				SafeArrayDelete( saveData->mesh[ i ]->blending );
//				SafeArrayDelete( saveData->mesh[ i ]->vertex );
//				SafeArrayDelete( saveData->mesh[ i ]->index );
//				SafeArrayDelete( saveData->mesh[ i ]->material );
//				SafeArrayDelete( saveData->mesh[ i ]->vertexBuffer );
//				SafeDelete( saveData->mesh[ i ]->indexBuffer );
//
//				if( saveData->mesh[ i ]->bone != NULL)
//					SafeArrayDelete( saveData->mesh[ i ]->bone );
//
//				SafeDelete( saveData->mesh[ i ] );
//			}
//		}
//
//		SafeDelete( saveData );
//	}
//	return;
//}
//
//// ����������
//void FbxDecoder::Init()
//{
//	
//	// FBXManager�N���X�̐��������FBX��SDK���g����悤�ɂȂ�
//	pSdkManager	 =	KFbxSdkManager::Create();
//
//	// FBX�t�@�C����ǂݍ��ނ��߂̃C���|�[�^�[���쐬
//	pImporter	 =	KFbxImporter::Create( pSdkManager, "fbx inpoter" );
//	// �V�[���̍쐬
//	pFbxScene = KFbxScene::Create( pSdkManager , "fbx scene" );
//
//	// ���f���f�[�^�̍쐬
//	saveData = new ModelData;
//
//	saveData->meshCount		= 0;
//
//	return;
//}
//
//// �w�肵��FBX�t�@�C����ǂݍ���
//bool FbxDecoder::Decode( std::string in_path, int in_type )
//{
//	//	���f���^�C�v
//	saveData->type	= in_type;
//
//	if( pSdkManager == NULL ||  pFbxScene == NULL)
//	{
//		MessageBox( 0 , "FBXSDK�̏������Ɏ��s���Ă��܂��B", NULL , MB_OK);
//		return false;
//	}
// 
//	/*
//    FBX�t�@�C���ւ̐�΃p�X���ɓ��{�ꕶ�������݂���ꍇ�C���|�[�^�[�̏�������
//    ���s����̂ŁA��΃p�X���擾����FBX SDK���Ő������ǂ߂�悤�ɕϊ�����
//	*/
//   char		 FileName[514];
//   char		 FullName[514];
//
//  // FBX�t�@�C��������f�B���N�g���̃t���p�X���擾
//	_fullpath( FileName , in_path.c_str() , 514 );
//  
//  // �擾������΃p�X��UTF8�ɕϊ����邱������Ɠ��{��ɂ��Ή��ł���
//	KFBX_ANSI_to_UTF8( FileName ,FullName );
//
//   // �C���|�[�^�[���g�p���ăt�@�C�����[�h
//  const bool lImportStatus = pImporter->Initialize(
//                                    FullName,                        // char�^�z���Unicode�`���Ŋi�[����� FBX �t�@�C���p�X
//                                    -1                              // �t�@�C���t�H�[�}�b�g�͒ʏ�w�肵�Ȃ��B�w�肷��ꍇ�A�g���q�ɂ���ăt�H�[�}�b�g�����肷��B	
//                                    );
//
//    // �������Ɏ��s
//	if( lImportStatus == false )
//	{
//		 return false;
//	}
//
//	// �쐬�����V�[�����C���|�[�g�ɓo�^
//	bool lStatus = pImporter->Import( pFbxScene );
//
//	if( lStatus == false )
//	{
//	   //�o�^���s
//	   return false;
//	}
//
//	// �V�[������FBX�t�@�C�����̃��[�g�m�[�h���擾
//	KFbxNode* pRootNode = pFbxScene->GetRootNode();
//
//	// �V�[���̍쐬�ɐ���������m�[�h�̍쐬
//	if( !CreateNode( pRootNode ) )
//	{
//		// �m�[�h�쐬�Ɏ��s
//		return false;
//	}
//  
//	//�ǂݍ��ݐ���
//	return true;
//}
//
//// �n���ꂽ�m�[�h����e�탂�f���f�[�^���쐬����
//bool FbxDecoder::CreateNode( KFbxNode* pNode, int parentId )
//{
//
//	// �m�[�h���쐬����Ă��Ȃ��B
//	if( pNode == NULL )
//	{
//		return false;
//	}
//	
//	KFbxNodeAttribute* attrib = pNode->GetNodeAttribute();
//
//	if( attrib != NULL )
//	{
//		// �m�[�h�^�C�v�̎擾
//		KFbxNodeAttribute::EAttributeType type = attrib->GetAttributeType();
//
//		if( type == KFbxNodeAttribute::eMESH )
//		{
//			static int meshId = 0;
//			// ���b�V���f�[�^�쐬
//			MeshData* tempMesh		= new MeshData;
//			tempMesh->indexBuffer	= new IndexBuffer;
//			tempMesh->vertexBuffer	= new VertexBuffer[ 5 ];
//
//			tempMesh->meshId = meshId;
//			tempMesh->parentId = parentId;
//			meshId++;
//
//			// ���b�V���̍쐬
//			CreateMesh( attrib, tempMesh );
//
//			// �K�w�A�j���[�V�����̎p���s��̎擾(60�t���[�����擾����)
//			KTime time;
//			for( int i = 0; i < 61; i++ )
//			{
//				time.SetTime( 0, 0, 0, i, 0, KTime::eFRAMES60, 0 );//���̃t���[���ɑ΂��鎞��
//				// �w�肵���t���[�����Ԃ̎p���s����擾
//				KFbxXMatrix mCurrentOrentation = pNode->GetGlobalFromCurrentTake( time );
//				math::Matrix mat;			
//				// �s��̃R�s�[( FBX -> DirectX )
//				for (int x=0; x<4; x++)
//				{
//					for (int y=0; y<4; y++)
//					{
//						mat( x, y ) =  ( float )mCurrentOrentation.Get( x, y );
//					}
//				}
//				
//				tempMesh->tran.push_back( mat );
//				
//			}
//			
//
//			// ���f���f�[�^�Ƀ��b�V���f�[�^���R�s�[
//			saveData->mesh.push_back( tempMesh );
//
//		}
//	}
//	int childNodeNum = pNode->GetChildCount();
//
//	for( int i = 0; i < childNodeNum;i++)
//	{
//		// �q�m�[�h�̍쐬
//		KFbxNode* child = pNode->GetChild( i );
//		CreateNode( child );
//
//	}
//
//	//	���b�V���̐����i�[
//	saveData->meshCount = saveData->mesh.size();
//
//	// �m�[�h�̍쐬�ɐ���
//	 return true;
//
//}
//
////	�n���ꂽ���b�V���m�[�h����f�[�^�𔲂��o��
//bool FbxDecoder::CreateMesh( KFbxNodeAttribute* pAttrib ,MeshData* mesh )
//{
//
//	// ���b�V���Ƀ_�E���L���X�g
//    KFbxMesh* pMesh = (KFbxMesh*)pAttrib;
//
//	/*
//	���_���W,�@��,UV���W�������Ⴄ�ꍇ������̂ŃC���f�b�N�X�����B�Ȃ̂Œ��_��=�C���f�b�N�X����
//	*/
//	int vertexCount					= pMesh->GetControlPointsCount();			//	���_��
//	KFbxVector4* src				= pMesh->GetControlPoints();				//	���_���W�z��
//	
//	mesh->countData.porygonCount	= pMesh->GetPolygonCount();					//	�|���S����
//	mesh->countData.indexCount		= pMesh->GetPolygonVertexCount();			//	�C���f�b�N�X��
//	mesh->countData.vertexCount		= mesh->countData.indexCount;				//	�C���f�b�N�X�������̂�
//	mesh->index						= new int[ mesh->countData.indexCount ];	//	���_�C���f�b�N�X(�������ɂ͍č\�z�����C���f�b�N�X���i�[�����)
//	int* tempIndex					= new int[ mesh->countData.indexCount ];	//	���_�C���f�b�N�X							
//	// ���_�f�[�^�̍쐬
//	mesh->vertex					= new VertexData[ mesh->countData.indexCount ];
//
//	// �o�[�e�N�X�u�����f�B���O�f�[�^
//	mesh->blending					= new VertexBlending[ mesh->countData.indexCount ];
//	math::Vector4*	weight			= new math::Vector4[ mesh->countData.indexCount ];
//	BoneIndex*		boneIndex		= new BoneIndex[ mesh->countData.indexCount ];
//
//	// �u�����f�B���O�f�[�^�̏�����(�{�[���������ꍇ�����邽�ߏ��������K�v)
//	for( int i = 0; i < mesh->countData.indexCount; i++ )
//	{
//		for( int k = 0; k < 4; k++ )
//		{
//			mesh->blending[ i ].boneIndex[ k ] = 0;
//			mesh->blending[ i ].wighte[ k ] = 0.0f;
//		}
//		weight[ i ] = math::Vector4( 0.0f, 0.0f, 0.0f, 0.0f );
//		boneIndex[ i ].indexOne		= 0;
//		boneIndex[ i ].indexTwo		= 0;
//		boneIndex[ i ].indexThree	= 0;
//		boneIndex[ i ].indexFour	= 0;
//
//	}
//
//	// ���̃f�[�^
//	math::Vector3* pos				= new math::Vector3[ vertexCount ];
//
//	for( int i = 0; i < vertexCount; i++ )
//	{
//		pos[ i ].x	= -( float )src[ i ][ 0 ];
//		pos[ i ].y	= ( float )src[ i ][ 1 ];
//		pos[ i ].z	= ( float )src[ i ][ 2 ];
//
//	}
//
//	int index = 0;
//	for( int i = 0; i < mesh->countData.porygonCount; i++ )
//	{
//		int polygonSize = pMesh->GetPolygonSize( i );
//
//		if( polygonSize > 3 )
//		{
//			MessageBox( 0, "3�p�`�ȏ�̃|���S�������݂��܂��B", NULL, MB_OK );
//			return false;
//		}
//		for( int j = 0; j < 3; j++ )
//		{
//			// �C���f�b�N�X�̎擾
//			tempIndex[ index ] = pMesh->GetPolygonVertex( i, j );
//			index++;
//		}
//	}
//
//	// ���_���W���C���f�b�N�X�Q�Ƃō��Ȃ���
//	math::Vector3* posIndex = new math::Vector3[ mesh->countData.indexCount ];
//	for( int i = 0; i < mesh->countData.indexCount; i++ )
//	{
//		posIndex[ i ] = pos[ tempIndex[ i ] ];
//		mesh->vertex[ i ].pos = pos[ tempIndex[ i ] ];
//	}
//	
//	//math::Vector3 temp;
//	//for( int i = 0; i < mesh->countData.indexCount / 3; i++ )
//	//{
//	//	//posIndex[ i * 3 ]		= posIndex[ i * 3];
//	//	temp = posIndex[i * 3 + 2];
//	//	posIndex[ i * 3 + 2 ]	= posIndex[ i * 3 + 1];
//	//	posIndex[ i * 3 + 1 ]	= temp;
//	//}
//
//	// ���_�o�b�t�@�̍쐬
//	mesh->vertexBuffer[ 0 ].Create( VertexBuffer::FLOAT3, mesh->countData.indexCount );
//	mesh->vertexBuffer[ 0 ].SetBuffer( posIndex, 0, mesh->countData.indexCount );
//	SafeArrayDelete( pos );
//	SafeArrayDelete( posIndex  );
//
//	//	�C���f�b�N�X�o�b�t�@�̍쐬
//	//	�C���f�b�N�X���쐬����̂�0�`�C���f�b�N�X���܂ŏ��ɂ����΂���
//	for( int i = 0; i < mesh->countData.indexCount; i++ )
//	{
//		mesh->index[ i ] = i;
//	}
//	mesh->indexBuffer->Create( IndexBuffer::BIT32,mesh->countData.indexCount );
//	mesh->indexBuffer->SetBuffer( mesh->index, 0, mesh->countData.indexCount );
//
//	// ���b�V���̃f�[�^�͕����̃��C���[�Ɋi�[����Ă���
//	int layerCount = pMesh->GetLayerCount();
//
//	for( int i= 0; i < layerCount; i++ )
//	{
//		KFbxLayer* layer					= pMesh->GetLayer( i );
//		// ���b�V�����C���[����e�f�[�^���i�[�������C���[���擾
//		KFbxLayerElementNormal* normalElem	= layer->GetNormals();
//		KFbxLayerElementUV*		uvElem		= layer->GetUVs();
//
//		// �@���̓ǂݍ���
//		if( normalElem != NULL )
//		{
//			KFbxLayerElement::EMappingMode		mappingMode = normalElem->GetMappingMode();
//			KFbxLayerElement::EReferenceMode	refMode		= normalElem->GetReferenceMode();
//			int	normalCount									= normalElem->GetDirectArray().GetCount();
//			int	indexNum									= normalElem->GetIndexArray().GetCount();
//			
//			// �@���f�[�^�̊m��
//			math::Vector3* normal = new math::Vector3[ normalCount ];
//
//			for( int i = 0; i < normalCount; i++ )
//			{
//				normal[ i ].x = -(float)normalElem->GetDirectArray().GetAt( i )[ 0 ];
//				normal[ i ].y = (float)normalElem->GetDirectArray().GetAt( i )[ 1 ];
//				normal[ i ].z = (float)normalElem->GetDirectArray().GetAt( i )[ 2 ];
//			}
//
//			// �@���̃C���f�b�N�X�Q�Ƃōč\�z
//			math::Vector3* normalIndex = new math::Vector3[ mesh->countData.indexCount ];
//			//	���_���ƌ��������ꍇ�A�C���f�b�N�X�����L�ł���
//			if( normalCount == vertexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					normalIndex[ i ]			= normal[ tempIndex[ i ] ];
//					mesh->vertex[ i ].normal	= normal[ tempIndex[ i ] ];
//				}
//			}
//			// �����C���f�b�N�X������ꍇ
//			else if( normalCount == mesh->countData.indexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					normalIndex[ i ]			= normal[ i ];
//					mesh->vertex[ i ].normal	= normal[ i ];
//				}
//			}
//			// �@���C���f�b�N�X������ꍇ
//			else if( indexNum == mesh->countData.indexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					normalIndex[ i ]			= normal[ normalElem->GetIndexArray().GetAt( i ) ];
//					mesh->vertex[ i ].normal	= normal[ normalElem->GetIndexArray().GetAt( i ) ];
//				}
//			}
//
//			//	�@���̃o�b�t�@�쐬
//			mesh->vertexBuffer[ 1 ].Create( VertexBuffer::FLOAT3, mesh->countData.indexCount );
//			mesh->vertexBuffer[ 1 ].SetBuffer( normalIndex, 0, mesh->countData.indexCount );
//			// �Ō�ɂ���Ȃ��Ȃ����̂����
//			SafeArrayDelete( normal );
//			SafeArrayDelete( normalIndex );
//
//		}
//
//		// UV���W�̓ǂݍ���
//		if( uvElem != NULL )
//		{
//			KFbxLayerElement::EMappingMode   mappingMode = uvElem->GetMappingMode();
//			KFbxLayerElement::EReferenceMode	refMode	 = uvElem->GetReferenceMode();
//			int uvCount				= uvElem->GetDirectArray().GetCount();
//			int indexNum			= uvElem->GetIndexArray().GetCount();
//	
//
//			math::Vector2* uv = new math::Vector2[ uvCount ];
//
//			// UV���W�̊m��
//			// FBX����DirectX�ł͍��W�n���Ⴄ�̂ŕς���
//			for( int i = 0; i < uvCount; i++ )
//			{
//				uv[ i ].x =			(float)uvElem->GetDirectArray().GetAt( i )[ 0 ];
//				uv[ i ].y = 1.0f -	(float)uvElem->GetDirectArray().GetAt( i )[ 1 ];
//			}
//			// UV�̍č\�z
//			math::Vector2* uvIndex = new math::Vector2[ mesh->countData.indexCount ];
//			// UV�ƒ��_���W�������ꍇ�̓C���f�b�N�X�����L�ł���
//			if( uvCount == vertexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					uvIndex[ i ]			= uv[ tempIndex[ i ] ];
//					mesh->vertex[ i ].uv	= uv[ tempIndex[ i ] ];
//				}
//			}
//			//	UV���C���f�b�N�X�Ɠ����ꍇ�͂��̂܂ܑ��
//			else if( uvCount == mesh->countData.indexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount;i++ )
//				{
//					uvIndex[ i ]			= uv[ i ];
//					mesh->vertex[ i ].uv	= uv[ i ];
//				}
//			}
//			//	UV�C���f�b�N�X�ƃC���f�b�N�X�������ꍇ��UV�C���f�b�N�X����Q�Ƃ���
//			else  if( indexNum == mesh->countData.indexCount )
//			{
//				for( int i= 0; i < mesh->countData.indexCount; i++ )
//				{
//					uvIndex[ i ]			= uv[ uvElem->GetIndexArray().GetAt( i ) ];
//					mesh->vertex[ i ].uv	= uv[ uvElem->GetIndexArray().GetAt( i ) ];
//				}
//			}
//
//			mesh->vertexBuffer[ 2 ].Create( VertexBuffer::FLOAT2, mesh->countData.indexCount );
//			mesh->vertexBuffer[ 2 ].SetBuffer( uvIndex, 0, mesh->countData.indexCount );
//			SafeArrayDelete( uv );
//			SafeArrayDelete( uvIndex );
//			
//		}
//	}
//
//
//	//	�}�e���A���̎擾
//	KFbxNode* materialNode = pMesh->GetNode();
//
//	//	�}�e���A�����̎擾
//	mesh->countData.materialCount = materialNode->GetMaterialCount();
//
//	//	�}�e���A���f�[�^�̎擾
//	if( mesh->countData.materialCount != 0 )
//	{
//		mesh->material = new MaterialData[ mesh->countData.materialCount ];
//
//		for( int i = 0; i < mesh->countData.materialCount; i++ )
//		{
//			KFbxSurfaceMaterial* material = materialNode->GetMaterial( i );
//
//			// lambert�}�e���A���̏ꍇ
//			if( material->GetClassId().Is( KFbxSurfaceLambert::ClassId ) )
//			{
//				  // Lambert�ɃL���X�g
//				   KFbxSurfaceLambert* lambert = (KFbxSurfaceLambert*)material;
//				   
//				   CreateLambert( lambert, &mesh->material[ i ] );
//				    // �X�y�L����
//				   mesh->material[ i ].material.specular.r = 0.0f;
//				   mesh->material[ i ].material.specular.g = 0.0f;
//				   mesh->material[ i ].material.specular.b = 0.0f;
//				   mesh->material[ i ].material.specular.a = 1.0f;
//				   // ����
//				   mesh->material[ i ].power = 1.0f;
//
//			}
//			//	Phong�}�e���A���̏ꍇ
//			else if( material->GetClassId().Is( KFbxSurfacePhong::ClassId ) )
//			{
//				 // Phong�ɃL���X�g
//				 KFbxSurfacePhong* phong = (KFbxSurfacePhong*)material;
//
//				 // Phong��Lambert��e�Ɏ��̂ő��v
//				 CreateLambert( phong, &mesh->material[ i ] );
//
//				 // �X�y�L����
//				 mesh->material[i].material.specular.r = (float)phong->GetSpecularColor().Get()[ 0 ];
//				 mesh->material[i].material.specular.g = (float)phong->GetSpecularColor().Get()[ 1 ];
//				 mesh->material[i].material.specular.b = (float)phong->GetSpecularColor().Get()[ 2 ];
//
//				 // ����
//				 mesh->material[i].power = (float)phong->GetShininess().Get();
//			}
//		}
//	}
//
//	// �{�[���̓ǂݍ���
//	// �f�t�H�[�}�[�𓾂�
//	int defomerCount = pMesh->GetDeformerCount();
//	KFbxDeformer* pDeformer = pMesh->GetDeformer( 0 );								//	�f�t�H�[�}�[
//	KFbxSkin* pSkinInfo = static_cast< KFbxSkin* >( pDeformer );					//	�X�L��
//	KFbxCluster** m_ppCluster;														//	�{�[���i�[�p�N���X( FBX�p )
//
//	// �{�[���̌��𓾂�
//	int boneCount		=	pSkinInfo->GetClusterCount();
//	mesh->bone			=	NULL;
//	mesh->boneCount		=	0;
//	// 0�ȏ�Ȃ�{�[��������̂œǂݍ��݂�����
//	if( boneCount > 0 )
//	{
//		// �{�[���f�[�^�̃R�s�[
//		mesh->boneCount			= boneCount;											//	�{�[���̐����i�[
//		mesh->bone				= new Bone[ boneCount ];								//	�{�[���N���X�̊m��
//		m_ppCluster				= new KFbxCluster*[ boneCount ];						//	�N���X�^�[�̊m��
//		VertexBlending*	blend	= new VertexBlending[ vertexCount ];					//	���i�[�p���_�u�����f�B���O
//		int*	readCount		= new int[ vertexCount ];
//
//		for( int i = 0; i < vertexCount; i++ )
//		{
//			for( int k = 0; k < 4;k++ )
//			{
//				blend[ i ].boneIndex[ k ]	= 0;	
//				blend[ i ].wighte[ k ]		= 0.0f;
//				readCount[ i ]				= 0;
//			}
//		}
//		
//		// �{�[���̎擾
//		for( int i = 0; i < boneCount; i++ )
//		{
//			m_ppCluster[ i ] = pSkinInfo->GetCluster( i );
//			
//			int		iNumIndex	= m_ppCluster[ i ]->GetControlPointIndicesCount();//���̃{�[���ɉe�����󂯂钸�_��
//			int*	piIndex		= m_ppCluster[ i ]->GetControlPointIndices();		//���̃{�[���ɉe�����󂯂钸�_�C���f�b�N�X
//			double* pdWeight	= m_ppCluster[ i ]->GetControlPointWeights();		//���̃{�[���ɑ΂��钸�_�ւ̉e����
//	
//			//���_�̏d�݂̎擾
//			//���_������C���f�b�N�X�����ǂ��āA���_�T�C�h�Ő�������
//			for(int k = 0; k < iNumIndex; k++ )
//			{
//			
//				blend[ piIndex[ k ] ].boneIndex[ readCount[ piIndex[ k ] ] ]  = i;
//				blend[ piIndex[ k ] ].wighte[ readCount[ piIndex[ k ] ] ] = ( float )pdWeight[ k ];
//
//				if( readCount[ piIndex[ k ] ] < 4 )
//				{
//					readCount[ piIndex[ k ] ]++;
//				}
//
//			}
//		}
//
//		// �{�[���f�[�^���C���f�b�N�X�Q�ƂœW�J
//		for( int i = 0; i < mesh->countData.indexCount; i++ )
//		{
//			mesh->blending[ i ] = blend[ tempIndex[ i ] ];
//
//			weight[ i ] = math::Vector4(
//				mesh->blending[ i ].wighte[ 0 ],
//				mesh->blending[ i ].wighte[ 1 ],
//				mesh->blending[ i ].wighte[ 2 ],
//				mesh->blending[ i ].wighte[ 3 ]);
//			boneIndex[ i ].indexOne		= mesh->blending[ i ].boneIndex[ 0 ];
//			boneIndex[ i ].indexTwo		= mesh->blending[ i ].boneIndex[ 1 ];
//			boneIndex[ i ].indexThree	= mesh->blending[ i ].boneIndex[ 2 ];
//			boneIndex[ i ].indexFour	= mesh->blending[ i ].boneIndex[ 3 ];
//		}
//
//		
//
//		// �{�[���̐�Ύp���̊m��
//		for( int i = 0; i < mesh->boneCount; i++ )
//		{
//			KFbxXMatrix bone_mat;
//			m_ppCluster[ i ]->GetTransformLinkMatrix( bone_mat );
//			for( int x = 0; x < 4; x++ )
//			{
//				for( int y = 0; y < 4; y++ )
//				{
//					mesh->bone[ i ].init( ( float )y, ( float )x ) = bone_mat.Get( y, x );
//				}
//			}
//			
//			// ��Ύp������I�t�Z�b�g�s����쐬����
//			D3DXMatrixInverse( &mesh->bone[ i ].offset, 0, &mesh->bone[ i ].init );
//		}
//
//		// �{�[���p���s��̊m��(60Fps���̊m��)
//		math::Matrix	mat;
//		KTime			time;
//		for( int i = 0; i < 61; i++ )
//		{
//			time.SetTime( 0, 0, 0, i, 0, KTime::eFRAMES60, 0 );//60�t���[��/�b
//
//			for( int k = 0; k < mesh->boneCount; k++ )
//			{		
//				KFbxMatrix fbx_mat = m_ppCluster[ k ]->GetLink()->GetGlobalFromCurrentTake( time );
//
//				for( int x = 0; x < 4; x++ )
//				{
//					for( int y = 0; y < 4; y++ )
//					{
//						mat( y, x ) = ( float )fbx_mat.Get( y, x );
//					}
//
//				}
//				// �{�[���̃t���[�����p���s����i�[
//				mesh->bone[ k ].boneMat.push_back( mat );
//			}
//		}
//
//		//	�g���I����Ă����̂����
//		SafeDelete( readCount );
//		SafeArrayDelete( m_ppCluster );
//		SafeArrayDelete( blend );
//	}
//	//	�u�����f�B���O�o�b�t�@�̍쐬
//	mesh->vertexBuffer[ 3 ].Create( VertexBuffer::FLOAT4,mesh->countData.vertexCount );
//	mesh->vertexBuffer[ 4 ].Create( VertexBuffer::UBYTE4,mesh->countData.vertexCount );
//
//	mesh->vertexBuffer[ 3 ].SetBuffer( weight, 0, mesh->countData.vertexCount );
//	mesh->vertexBuffer[ 4 ].SetBuffer( boneIndex, 0, mesh->countData.vertexCount );
//
//	// ����Ȃ��Ȃ����z��̉��
//	SafeArrayDelete( tempIndex );
//	SafeArrayDelete( weight );
//	SafeArrayDelete( boneIndex );
//
//	// �ǂ݂��ݏI��
//	return true;
//}
////	�n���ꂽ�����o�[�g�}�e���A������f�[�^�𔲂��o���B
//bool FbxDecoder::CreateLambert(KFbxSurfaceLambert* Lambert, MaterialData* mat)
//{
//	// �A���r�G���g
//	mat->material.ambient.r		= (float)Lambert->GetAmbientColor().Get()[ 0 ];
//	mat->material.ambient.g		= (float)Lambert->GetAmbientColor().Get()[ 1 ];
//	mat->material.ambient.b		= (float)Lambert->GetAmbientColor().Get()[ 2 ];
//	mat->material.ambient.a		= 1.0f;
//
//	// �f�B�t���[�Y
//	mat->material.diffuse.r		= (float)Lambert->GetDiffuseColor().Get()[ 0 ];
//	mat->material.diffuse.g		= (float)Lambert->GetDiffuseColor().Get()[ 1 ];
//	mat->material.diffuse.b		= (float)Lambert->GetDiffuseColor().Get()[ 2 ];
//	mat->material.diffuse.a		= 1.0f;
//
//	// �G�~�b�V�u
//	mat->material.emissive.r	= (float)Lambert->GetEmissiveColor().Get()[ 0 ];
//	mat->material.emissive.g	= (float)Lambert->GetEmissiveColor().Get()[ 1 ];
//	mat->material.emissive.b	= (float)Lambert->GetEmissiveColor().Get()[ 2 ];
//	mat->material.emissive.a	= 1.0f;
//
//	return true;
//}
//
////	���f���f�[�^�̎擾
//ModelData*	FbxDecoder::GetModelData()
//{
//	if( saveData != NULL )
//		return saveData;
//
//	return NULL;
//}
//
//}	//	graphics	end
//}	//	iruna		end