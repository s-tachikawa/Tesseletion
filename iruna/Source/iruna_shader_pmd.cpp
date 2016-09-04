//
//#include "../Source/iruna_shader_pmd.h"
//
///*----�f�[�^�^-------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
////	�R���X�g���N�^
//PmdShader::PmdShader( ModelData* in_data )
//:	shader( NULL ),
//	dec( NULL ),
//	vertex( NULL ),
//	data( in_data )
//{
//	//���_�f�N�����[�V�����̐ݒ�
//	static VertexDeclaration::Element PMD_MODEL_ELEMENT[] = {
//				{0 , 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_POSITION , 0 },
//
//				{1 , 0 , D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_NORMAL , 0 },
//
//				{2 , 0 , D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_TEXCOORD , 0 },
//
//				{3 , 0 , D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_BLENDWEIGHT , 0 },
//
//				{4 , 0 , D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT , D3DDECLUSAGE_BLENDINDICES , 0 },
//				D3DDECL_END()	
//	 };
//
//	//	���_�f�B�N�����[�V�����̍쐬
//	dec = new VertexDeclaration;
//	dec->Create( PMD_MODEL_ELEMENT );
//	
//	//	�V�F�[�_�[�̍쐬
//	shader = new Effect;
//	shader->Create( "../iruna/Include/Shader/PmdShader.fx", 0 );
//
//	//	�A�j���[�V�����p�o�[�e�N�X�o�b�t�@�̍쐬
//	vertex = new VertexBuffer[ 2 ];
//	vertex[ 0 ].Create( VertexBuffer::FLOAT3, data->mesh[ 0 ]->countData.vertexCount );
//	vertex[ 1 ].Create( VertexBuffer::FLOAT3, data->mesh[ 0 ]->countData.vertexCount );
//	
//	pos		= new math::Vector3[ data->mesh[ 0 ]->countData.vertexCount ];
//	normal	= new math::Vector3[ data->mesh[ 0 ]->countData.vertexCount ];
//
//	return;
//}
//
////	�f�X�g���N�^
//PmdShader::~PmdShader()
//{
//	SafeArrayDelete( pos );
//	SafeArrayDelete( normal );
//	SafeArrayDelete( vertex );
//	SafeDelete( shader );
//	SafeDelete( dec );
//	return;
//}
//
////	�X�L�j���O
//void PmdShader::Skining()
//{
//	int vertexCount = data->mesh[ 0 ]->countData.vertexCount;
//	
//	//���_�������[�v
//	for(int i = 0; i < vertexCount;i++)
//	{
//		//�ϊ����W
//		math::Vector4 tempPos		= math::Vector4(0,0,0,0);
//		math::Vector4 tempNormal	= math::Vector4(0,0,0,0);
//		//���_���󂯂�{�[���̐������[�v
//		for(int k = 0;k < 2;k++)
//		{
//			//�X�L�j���O�s��Œ��_�ϊ�
//			math::Vector4 v = math::Vector4( 0,0,0,0 );
//			math::Vector4 z = math::Vector4(	data->mesh[ 0 ]->vertex[ i ].normal.x, 
//												data->mesh[ 0 ]->vertex[ i ].normal.y, 
//												data->mesh[ 0 ]->vertex[ i ].normal.z,
//												0 );
//			
//			D3DXVec3Transform(	&v,
//								&data->mesh[ 0 ]->vertex[ i ].pos,
//								&data->mesh[ 0 ]->bone[ data->mesh[ 0 ]->blending[ i ].boneIndex[ k ] ].skin );
//			
//			D3DXVec4Transform(	&z ,
//								&z ,
//								&data->mesh[ 0 ]->bone[ data->mesh[ 0 ]->blending[ i ].boneIndex[ k ] ].skin );
//			
//			//�d�݂𑫂��Ă���
//			tempPos		+= (v * data->mesh[ 0 ]->blending[ i ].wighte[ k ] );
//			tempNormal	+= (z * data->mesh[ 0 ]->blending[ i ].wighte[ k ] );
//		}
//		//�A�j���[�V�����p�̍��W�Ɋi�[
//		pos[ i ]	= math::Vector3(tempPos.x,tempPos.y,tempPos.z);
//		normal[ i ] = math::Vector3( tempNormal.x,tempNormal.y,tempNormal.z );
//		
//
//	}
//	//�A�j���[�V�����p�̍��W���o�b�t�@�ɃZ�b�g
//	vertex[ 0 ].SetBuffer( pos, 0, vertexCount );
//	vertex[ 1 ].SetBuffer( normal , 0, vertexCount);
//	return;
//}
//
////	���f���̕`��
//void PmdShader::Render( math::Vector3 pos )
//{
//	Skining();
//
//	vertex[ 0 ].IntoStream( 0 );
//	vertex[ 1 ].IntoStream( 1 );
//	data->mesh[ 0 ]->vertexBuffer[ 2 ].IntoStream( 2 );
//	dec->Set();
//
//	math::WoldMatrix world;
//	world.SetTranslation( pos.x, pos.y, pos.z );
//	shader->SetMatrix( "world", world.GetWoldMatrix() );
//	shader->SetMatrix( "view", data->camera.GetView() );
//	shader->SetMatrix( "projection", data->camera.GetProjection() );
//
//	shader->Begin( 0, 0 );
//	for( int i = 0; i < data->mesh[ 0 ]->countData.materialCount; i++ )
//	{
//		data->mesh[ 0 ]->material[ i ].indexBuffer->IntoIndices();
//		
//		//	�e�N�X�`������
//		if( data->mesh[ 0 ]->material[ i ].tex != NULL )
//		{
//			shader->SetTexture( "tex",  data->mesh[ 0 ]->material[ i ].tex->GetTexture() );
//			shader->BeginPass( 0 );
//		}
//		//	�e�N�X�`���Ȃ�
//		else
//		{
//			math::Vector4 color = math::Vector4(	data->mesh[ 0 ]->material[ i ].dxMaterial.Diffuse.r,
//													data->mesh[ 0 ]->material[ i ].dxMaterial.Diffuse.g,
//													data->mesh[ 0 ]->material[ i ].dxMaterial.Diffuse.b,
//													data->mesh[ 0 ]->material[ i ].dxMaterial.Diffuse.a );
//			shader->SetVector( "diffuse",color );
//			shader->BeginPass( 1 );
//		
//		}
//
//		render.DrawIndexPrimitive(	Primitive::TRIANGLE_LIST,
//									data->mesh[ 0 ]->countData.vertexCount,
//									data->mesh[ 0 ]->material[ i ].porygonCount );
//		shader->EndPass();
//		
//	}
//	shader->End();
//
//
//	return;
//}
//
//}	//	graphics	end
//}	//	iruna		end