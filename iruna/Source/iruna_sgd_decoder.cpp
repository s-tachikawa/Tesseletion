//---------------------------------------------------------
// 
//	iruna_fbx_decoder.cpp
//	FBXファイル読み込みクラス実装部
//	作成日 10月21日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード---------------------------------*/
#include "../Source/iruna_sgd_decoder.h"


namespace iruna
{
namespace graphics
{

//	コンストラクタ
SgdDecoder::SgdDecoder()
	:	saveData( NULL )
{
	return;
}
SgdDecoder::~SgdDecoder()
{

	Relese();

	return;
}

//	デストラクタ
void SgdDecoder::Relese()
{
	if( saveData != NULL )
	{
		if( saveData->mesh.size() > 0 )
		{
			for( int i = 0; i < ( int )saveData->mesh.size();i++ )
			{
				SafeArrayDelete( saveData->mesh[ i ]->blending );
				SafeArrayDelete( saveData->mesh[ i ]->vertex );
				SafeArrayDelete( saveData->mesh[ i ]->index );
				SafeArrayDelete( saveData->mesh[ i ]->material );
				SafeArrayDelete( saveData->mesh[ i ]->vertexBuffer );
				SafeDelete( saveData->mesh[ i ]->indexBuffer );

				if( saveData->mesh[ i ]->bone != NULL)
					SafeArrayDelete( saveData->mesh[ i ]->bone );

				SafeDelete( saveData->mesh[ i ] );
			}
		}

		SafeDelete( saveData );
	}

	return;
}

// モデル関連の初期化
void SgdDecoder::Init()
{
	
	saveData	= new ModelData;

	saveData->meshCount = 0;

	return;
}
bool SgdDecoder::Decode( std::string in_path, int in_type )
{
	FILE* fp;

	fp = fopen( in_path.c_str(), "rb" );

	//	メッシュカウント
	fread( &saveData->meshCount, sizeof( int ), 1, fp );
	
	//	アニメーションカウント
	fread(&saveData->animCount, sizeof(int), 1, fp);

	//	モデルタイプ
	saveData->type = in_type;

	for( int i = 0; i < saveData->meshCount; i++ )
	{
		MeshData* mesh = new MeshData;

		// 頂点数の読み込み
		fread( &mesh->countData.vertexCount, sizeof( int ), 1, fp );
		// 頂点データの読み込み
		math::Vector4*	pos				= new math::Vector4[ mesh->countData.vertexCount ];
		math::Vector3*	normal			= new math::Vector3[ mesh->countData.vertexCount ];
		math::Vector2*	uv				= new math::Vector2[ mesh->countData.vertexCount ];
		math::Vector4*	weight			= new math::Vector4[ mesh->countData.vertexCount ];
		BoneIndex*		boneIndex		= new BoneIndex[ mesh->countData.vertexCount ];

		mesh->vertex	= new VertexData[ mesh->countData.vertexCount ];
		mesh->blending	= new VertexBlending[ mesh->countData.vertexCount ];
		
		for( int k = 0; k < mesh->countData.vertexCount; k++ )
		{
			fread( pos[ k ], sizeof( float ) * 3, 1, fp );
			fread( normal[ k ], sizeof( float ) * 3, 1, fp );
			fread( uv[ k ], sizeof( float ) * 2, 1, fp );
			fread( mesh->blending[ k ].boneIndex, sizeof( int ) * 4, 1, fp );
			fread( mesh->blending[ k ].wighte, sizeof( float ) * 4, 1, fp );

			mesh->vertex[ k ].pos		= pos[ k ];
			mesh->vertex[ k ].normal	= normal[ k ];
			mesh->vertex[ k ].uv		= uv[ k ];
			weight[ k ] = math::Vector4( 
				mesh->blending[ k ].wighte[ 0 ],
				mesh->blending[ k ].wighte[ 1 ],
				mesh->blending[ k ].wighte[ 2 ],
				mesh->blending[ k ].wighte[ 3 ]);

			boneIndex[ k ].indexOne		= mesh->blending[ k ].boneIndex[ 0 ]; 
			boneIndex[ k ].indexTwo		= mesh->blending[ k ].boneIndex[ 1 ]; 
			boneIndex[ k ].indexThree	= mesh->blending[ k ].boneIndex[ 2 ]; 
			boneIndex[ k ].indexFour	= mesh->blending[ k ].boneIndex[ 3 ]; 

		}

		mesh->vertexBuffer = new VertexBuffer[ 5 ];


		mesh->vertexBuffer[0].SetBuffer( pos );
		mesh->vertexBuffer[1].SetBuffer(normal );
		mesh->vertexBuffer[2].SetBuffer(uv );
		mesh->vertexBuffer[3].SetBuffer(weight);
		mesh->vertexBuffer[4].SetBuffer(boneIndex);

		int nPosBufferSize			= sizeof(pos[0]);
		int nNormalBufferSize		= sizeof(normal[0]);
		int nUVBufferSize			= sizeof(uv[0]);
		int nWeightBufferSize		= sizeof(weight[0]);
		int nBoneIndexBufferSize	= sizeof(boneIndex[0]);

		mesh->vertexBuffer[0].Create(nPosBufferSize, mesh->countData.vertexCount);
		mesh->vertexBuffer[1].Create(nNormalBufferSize, mesh->countData.vertexCount);
		mesh->vertexBuffer[2].Create(nUVBufferSize, mesh->countData.vertexCount);
		mesh->vertexBuffer[3].Create(nWeightBufferSize, mesh->countData.vertexCount);
		mesh->vertexBuffer[4].Create(nBoneIndexBufferSize, mesh->countData.vertexCount);


		SafeArrayDelete( pos );
		SafeArrayDelete( normal );
		SafeArrayDelete( uv );
		SafeArrayDelete( weight );
		SafeArrayDelete( boneIndex );

		// インデックス,ポリゴン数の読み込み
		fread( &mesh->countData.indexCount, sizeof( int ), 1, fp );
		fread( &mesh->countData.porygonCount, sizeof( int ), 1, fp );

		mesh->index = new int[ mesh->countData.indexCount ];
		
		// インデックスデータの読み込み
		for( int k = 0; k < mesh->countData.indexCount; k++ )
		{
			fread( &mesh->index[ k ], sizeof( int ), 1, fp );
		}

		mesh->indexBuffer = new IndexBuffer;
		mesh->indexBuffer->SetBuffer( mesh->index );
		mesh->indexBuffer->Create( IndexBuffer::BIT32, mesh->countData.indexCount );
		

		// マテリアルの読み込み
		fread( &mesh->countData.materialCount, sizeof( int ), 1, fp );

		mesh->material = new MaterialData[ mesh->countData.materialCount ];

		for( int k = 0; k < mesh->countData.materialCount; k++ )
		{
			fread( &mesh->material[ k ].material.diffuse, sizeof( float ) * 4, 1, fp );
			fread( &mesh->material[ k ].material.ambient, sizeof( float ) * 4, 1, fp );
			fread( &mesh->material[ k ].material.specular, sizeof( float ) * 4, 1, fp );
			fread( &mesh->material[ k ].material.emissive, sizeof( float ) * 4, 1, fp );
			fread( &mesh->material[ k ].power, sizeof( float ), 1, fp );
		}
		// ボーン関連の初期化
		mesh->bone			=	NULL;
		mesh->boneCount		=	0;
		// ボーン数の読み込み
		fread( &mesh->boneCount, sizeof( int ), 1, fp );

		// ボーンが無い場合は読み込まない
		if( mesh->boneCount > 0 )
		{
			mesh->bone = new Bone[ mesh->boneCount ];

			//	ボーンデータの読み込み
			for( int k = 0; k < mesh->boneCount; k++)
			{
				fread( &mesh->bone[ k ].parentId, sizeof( int ), 1, fp );
				fread( &mesh->bone[ k ].init, sizeof( float ) * 16, 1, fp );
				D3DXMatrixInverse( &mesh->bone[ k ].offset, 0, &mesh->bone[ k ].init  );

				// スキニングアニメーションデータ
				for( int j = 0; j < 61; j++ )
				{
					math::Matrix mat;
					fread( &mat, sizeof( float ) * 16, 1, fp );
					mesh->bone[ k ].boneMat.push_back( mat );
				}

			}

		}

		// 階層アニメーションデータ
		for( int k = 0; k < 61; k++ )
		{
			math::Matrix mat;
			fread( &mat, sizeof( float ) * 16, 1, fp );
			mesh->tran.push_back( mat );
		}

		saveData->mesh.push_back( mesh );
	}
	fclose( fp );
	return true;
}

// モデルデータ
ModelData* SgdDecoder::GetModelData()
{
	if( saveData != NULL )
		return saveData;

	return NULL;
}

}	//	graphics	end
}	//	iruna		end