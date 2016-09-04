////---------------------------------------------------------
//// 
////	iruna_fbx_decoder.cpp
////	FBXファイル読み込みクラス実装部
////	作成日 10月21日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード---------------------------------*/
//#include "../Source/iruna_pmd_decoder.h"
//
//
//namespace iruna
//{
//namespace graphics
//{
//
////	コンストラクタ
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
////	デストラクタ
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
//// モデル関連の初期化
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
//	//ヘッダ用の変数
//	char			magic[ 3 ];			//	PMDフォーマット
//	float			version;			//	PMDファイルのバージョン
//	char			model_name[ 20 ];	//	モデルネーム
//	char			comment[ 256 ];		//	モデル対するコメント
//
//	//	PMDモデルに読み込み
//	fp = fopen(  in_path.c_str(), "rb");
//
//	//	読み込み失敗
//	if(fp == NULL)return false;
//	
//	//ヘッダの読み込み
//	fread( magic, sizeof( char ), 3, fp );
//	fread( &version, sizeof( float ), 1, fp );
//	fread( model_name, sizeof( char ), 20, fp );
//	fread( comment, sizeof( char ) ,256 ,fp );
//	//	メッシュカウント(PMDはたぶんメッシュが1つしかないと思う)
//	saveData->meshCount = 1;
//	//	モデルタイプ
//	saveData->type		= in_type;
//
//	MeshData* tempMesh = new MeshData;
//
//	//頂点数の読み込み
//	DWORD vertexCount = 0;
//	fread( &vertexCount, sizeof( DWORD ),1,fp);
//	tempMesh->countData.vertexCount = vertexCount;
//
//	//	頂点データの読み込み
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
//		//	頂点データ
//		fread( pos[ i ],	sizeof( float ) * 3, 1, fp );
//		fread( normal[ i ],	sizeof( float ) * 3, 1, fp );
//		fread( uv[ i ],		sizeof( float ) * 2, 1, fp );
//
//		tempMesh->vertex[ i ].pos	= pos[ i ];
//		tempMesh->vertex[ i ].normal = normal[ i ];
//		tempMesh->vertex[ i ].uv		= uv[ i ];
//		
//		//	頂点ウェイト(PMDは頂点に影響を与えるボーンが2つまでしかない)
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
//		//エッジフラグの読み込み(読み飛ばす)
//		BYTE e;
//		fread(&e,sizeof( BYTE ) ,1,fp);
//	}
//	//	VertexBufferの作成
//	tempMesh->vertexBuffer = new VertexBuffer[ 5 ];
//	tempMesh->vertexBuffer[ 0 ].Create( VertexBuffer::FLOAT3, vertexCount );
//	tempMesh->vertexBuffer[ 1 ].Create( VertexBuffer::FLOAT3, vertexCount );
//	tempMesh->vertexBuffer[ 2 ].Create( VertexBuffer::FLOAT2, vertexCount );
//	tempMesh->vertexBuffer[ 3 ].Create( VertexBuffer::FLOAT4, vertexCount );
//	tempMesh->vertexBuffer[ 4 ].Create( VertexBuffer::UBYTE4, vertexCount );
//
//	//	Bufferにセット
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
//	//	インデックス数を取得
//	DWORD index_count = 0;
//	fread( &index_count,	sizeof( int ), 1, fp );
//	tempMesh->countData.indexCount = index_count;
//	tempMesh->index = new int[ index_count ];
//	WORD* index_buf_temp = new WORD[ index_count ];
//
//	//	インデックスデータの取得
//	for( int i = 0; i < ( int )index_count; i++ )
//	{
//		fread( &index_buf_temp[ i ], sizeof( WORD ), 1, fp );
//	}
//
//	
//	
//	//マテリアルの数格納
//	DWORD material_count = 0;
//	fread( &material_count ,sizeof( DWORD ), 1, fp);
//	tempMesh->countData.materialCount = material_count;
//
//	//マテリアルの読み込み
//	BYTE			toonIndex,edgeFlag;
//	DWORD			IndexVertex = 0;
//	tempMesh->material = new MaterialData[ material_count ];
//
//	for( int i = 0; i < ( int )material_count; i++ )
//	{
//		D3DCOLORVALUE	color;
//		float			power;
//
//		//	ディフューズ
//		fread( &color, sizeof( float ) * 4, 1, fp );
//		color.a = 1.0f;
//		tempMesh->material[ i ].dxMaterial.Diffuse = color;
//
//		//	スペキュラーパワー
//		fread( &power, sizeof( float ), 1, fp );
//		tempMesh->material[ 0 ].dxMaterial.Power = power;
//
//		//	スペキュラー
//		fread( &color, sizeof( float ) * 3, 1, fp );
//		color.a = power;
//		tempMesh->material[ i ].dxMaterial.Specular = color;
//		
//		//	アンビエント
//		fread( &color, sizeof( float ) * 3, 1, fp);
//		color.a = 1.0f;
//		tempMesh->material[ i ].dxMaterial.Ambient = color;
//
//		//	エミッシブ
//		//tempMesh->material[ i ].material.emissive = Color4F( 1.0f,1.0f,1.0f, 1.0f );
//
//		//	トゥーンテクスチャへのインデックスとエッジフィルター用フラグ
//		fread(&toonIndex,sizeof( BYTE ),1,fp);
//		fread(&edgeFlag,sizeof( BYTE ),1,fp);
//
//		//	マテリアルに応じたインデックスバッファを作成
//		DWORD indes_count = 0;
//		fread(&indes_count,sizeof( DWORD ),1,fp );
//		tempMesh->material[ i ].indexCount = indes_count;
//		//	ポリゴン数の算出
//		tempMesh->material[ i ].porygonCount = indes_count / 3;
//		tempMesh->material[ i ].indexBuffer = new IndexBuffer;
//		tempMesh->material[ i ].indexBuffer->Create( IndexBuffer::BIT16, indes_count );
//		tempMesh->material[ i ].indexBuffer->SetBuffer( &index_buf_temp[ IndexVertex ], 0, indes_count );
//
//		//	インデックスの位置を進ませる
//		IndexVertex += indes_count;
//		
//		//	テクスチャ名
//		char buf[21] = { 0 };
//		fread( buf, sizeof( char ), 20, fp );
//
//		//	テクスチャの作成(ファイル名がなければテクスチャを作成しない)
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
//	//	ボーンの数取得
//	WORD boneCount = 0;
//	fread(&boneCount,sizeof( WORD ),1,fp);
//	tempMesh->boneCount = boneCount;
//
//	//	ボーンの取得
//	tempMesh->bone = new Bone[ boneCount ];
//
//	for( int i = 0; i < boneCount; i++ )
//	{
//		WORD parentBoneId = -1;
//		WORD childBoneId = -1;
//		BYTE boneType = 0;
//
//		//名前の取得
//		char bone_buf[ 20 ];
//		fread( bone_buf ,sizeof( char ), 20, fp );
//		tempMesh->bone[ i ].boneName	= bone_buf;
//		tempMesh->bone[ i ].id			= i;
//		
//		//親ボーン番号の取得
//		fread( &parentBoneId , sizeof( WORD ), 1, fp );
//		
//		//子ボーン番号の取得
//		fread( &childBoneId ,sizeof( WORD ), 1, fp );
//		tempMesh->bone[ i ].parentId	= parentBoneId;
//		tempMesh->bone[ i ].childId		= childBoneId;
//		
//		//ボーンのタイプ取得
//		fread( &boneType, sizeof( BYTE ), 1, fp );
//		
//		//IK番号の取得
//		WORD ik_parent_bone_index = 0;
//		fread( &ik_parent_bone_index , sizeof( WORD ),1,fp );
//		tempMesh->bone[ i ].IkId = ik_parent_bone_index;
//
//		//ボーンのローカル座標取得
//		math::Vector3 bonePos;
//		fread( &bonePos , sizeof( float ) * 3,1,fp );
//
//		//	初期姿勢の行列の作成
//		tempMesh->bone[ i ].SetInitMatrix( bonePos );
//		tempMesh->bone[ i ].originePos = bonePos;
//	}
//
//	//	ボーンの親子関係を作成
//	for( int i = 0; i < boneCount; i++ )
//	{
//		//親がいるなら
//		if(tempMesh->bone[ i ].parentId < boneCount)
//		{
//			//その親に自分を子ボーンとして登録
//			tempMesh->bone[ tempMesh->bone[ i ].parentId ].child.push_back( &tempMesh->bone[ i ] );
//		}
//	}
//
//	//	ルートボーンからボーン全体を相対座標に変える
//	tempMesh->bone[ 0 ].BoneRun( NULL );
//
//	//	IKボーンの数の読み込み
//	WORD ikCount = 0;
//	fread( &ikCount, sizeof( WORD ), 1, fp );
//	tempMesh->ikBone = new IkBone[ ikCount ];
//	tempMesh->ikBoneCount = ikCount;
//
//	
//	//	IKボーンデータの読み込み
//	for( int i = 0; i < ikCount; i++ )
//	{
//		WORD ikIndex		= 0;
//		WORD ikTargetIndex	= 0;
//		BYTE chain			= 0;
//		WORD iterations		= 0;
//		float weight		= 0.0f;
//		//	IK番号
//		fread( &ikIndex, sizeof( WORD ), 1, fp );
//		//	IKターゲットボーン
//		fread( &ikTargetIndex, sizeof( WORD ), 1, fp );
//		//	IKボーン影響の深さ
//		fread( &chain, sizeof( BYTE ), 1, fp );
//		//	再帰回数
//		fread( &iterations, sizeof( WORD ), 1, fp );
//		//	IKボーンからの影響度
//		fread( &weight, sizeof( float ), 1, fp );
//		//	IKボーン影響するボーン番号
//		for( int k = 0; k < ( int )chain; k++ )
//		{
//			WORD childIndex = 0;
//			fread( &childIndex, sizeof( WORD ), 1, fp );
//			tempMesh->ikBone[ i ].child.push_back( childIndex );
//		}
//		//	データを格納
//		tempMesh->ikBone[ i ].index			= ikIndex;
//		tempMesh->ikBone[ i ].targetIndex	= ikTargetIndex;
//		tempMesh->ikBone[ i ].length		= chain;
//		tempMesh->ikBone[ i ].iterations	= iterations;
//		tempMesh->ikBone[ i ].weight		= weight;
//		tempMesh->ikBone[ i ].boneCount		= tempMesh->boneCount;
//	}
//
//	//	メッシュを追加
//	saveData->mesh.push_back( tempMesh );
//
//	fclose( fp );
//	return true;
//}
//
//// モデルデータ
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