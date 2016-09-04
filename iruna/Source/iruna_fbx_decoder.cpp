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
//#include "../Source/iruna_fbx_decoder.h"
//#include "../Source/iruna_model_decoder.h"
//
///*----プリプロセッサディレクティブ---------------------------------*/
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
////	コンストラクタ
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
//// デストラクタ
//FbxDecoder::~FbxDecoder()
//{
//	return;
//}
//
//// 解放処理
//void FbxDecoder::Relese()
//{
//	//	SDKマネージャーの解放
//	/*
//		解放処理を使わないとSDK内でエラーが起こる
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
//// 初期化処理
//void FbxDecoder::Init()
//{
//	
//	// FBXManagerクラスの生成これでFBXのSDKが使えるようになる
//	pSdkManager	 =	KFbxSdkManager::Create();
//
//	// FBXファイルを読み込むためのインポーターを作成
//	pImporter	 =	KFbxImporter::Create( pSdkManager, "fbx inpoter" );
//	// シーンの作成
//	pFbxScene = KFbxScene::Create( pSdkManager , "fbx scene" );
//
//	// モデルデータの作成
//	saveData = new ModelData;
//
//	saveData->meshCount		= 0;
//
//	return;
//}
//
//// 指定したFBXファイルを読み込む
//bool FbxDecoder::Decode( std::string in_path, int in_type )
//{
//	//	モデルタイプ
//	saveData->type	= in_type;
//
//	if( pSdkManager == NULL ||  pFbxScene == NULL)
//	{
//		MessageBox( 0 , "FBXSDKの初期化に失敗しています。", NULL , MB_OK);
//		return false;
//	}
// 
//	/*
//    FBXファイルへの絶対パス内に日本語文字が存在する場合インポーターの初期化に
//    失敗するので、絶対パスを取得してFBX SDK内で正しく読めるように変換する
//	*/
//   char		 FileName[514];
//   char		 FullName[514];
//
//  // FBXファイルがあるディレクトリのフルパスを取得
//	_fullpath( FileName , in_path.c_str() , 514 );
//  
//  // 取得した絶対パスをUTF8に変換するこうすると日本語にも対応できる
//	KFBX_ANSI_to_UTF8( FileName ,FullName );
//
//   // インポーターを使用してファイルロード
//  const bool lImportStatus = pImporter->Initialize(
//                                    FullName,                        // char型配列のUnicode形式で格納される FBX ファイルパス
//                                    -1                              // ファイルフォーマットは通常指定しない。指定する場合、拡張子によってフォーマットを決定する。	
//                                    );
//
//    // 初期化に失敗
//	if( lImportStatus == false )
//	{
//		 return false;
//	}
//
//	// 作成したシーンをインポートに登録
//	bool lStatus = pImporter->Import( pFbxScene );
//
//	if( lStatus == false )
//	{
//	   //登録失敗
//	   return false;
//	}
//
//	// シーンからFBXファイル内のルートノードを取得
//	KFbxNode* pRootNode = pFbxScene->GetRootNode();
//
//	// シーンの作成に成功したらノードの作成
//	if( !CreateNode( pRootNode ) )
//	{
//		// ノード作成に失敗
//		return false;
//	}
//  
//	//読み込み成功
//	return true;
//}
//
//// 渡されたノードから各種モデルデータを作成する
//bool FbxDecoder::CreateNode( KFbxNode* pNode, int parentId )
//{
//
//	// ノードが作成されていない。
//	if( pNode == NULL )
//	{
//		return false;
//	}
//	
//	KFbxNodeAttribute* attrib = pNode->GetNodeAttribute();
//
//	if( attrib != NULL )
//	{
//		// ノードタイプの取得
//		KFbxNodeAttribute::EAttributeType type = attrib->GetAttributeType();
//
//		if( type == KFbxNodeAttribute::eMESH )
//		{
//			static int meshId = 0;
//			// メッシュデータ作成
//			MeshData* tempMesh		= new MeshData;
//			tempMesh->indexBuffer	= new IndexBuffer;
//			tempMesh->vertexBuffer	= new VertexBuffer[ 5 ];
//
//			tempMesh->meshId = meshId;
//			tempMesh->parentId = parentId;
//			meshId++;
//
//			// メッシュの作成
//			CreateMesh( attrib, tempMesh );
//
//			// 階層アニメーションの姿勢行列の取得(60フレーム分取得する)
//			KTime time;
//			for( int i = 0; i < 61; i++ )
//			{
//				time.SetTime( 0, 0, 0, i, 0, KTime::eFRAMES60, 0 );//そのフレームに対する時間
//				// 指定したフレーム時間の姿勢行列を取得
//				KFbxXMatrix mCurrentOrentation = pNode->GetGlobalFromCurrentTake( time );
//				math::Matrix mat;			
//				// 行列のコピー( FBX -> DirectX )
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
//			// モデルデータにメッシュデータをコピー
//			saveData->mesh.push_back( tempMesh );
//
//		}
//	}
//	int childNodeNum = pNode->GetChildCount();
//
//	for( int i = 0; i < childNodeNum;i++)
//	{
//		// 子ノードの作成
//		KFbxNode* child = pNode->GetChild( i );
//		CreateNode( child );
//
//	}
//
//	//	メッシュの数を格納
//	saveData->meshCount = saveData->mesh.size();
//
//	// ノードの作成に成功
//	 return true;
//
//}
//
////	渡されたメッシュノードからデータを抜き出す
//bool FbxDecoder::CreateMesh( KFbxNodeAttribute* pAttrib ,MeshData* mesh )
//{
//
//	// メッシュにダウンキャスト
//    KFbxMesh* pMesh = (KFbxMesh*)pAttrib;
//
//	/*
//	頂点座標,法線,UV座標が数が違う場合があるのでインデックス分作る。なので頂点数=インデックス数分
//	*/
//	int vertexCount					= pMesh->GetControlPointsCount();			//	頂点数
//	KFbxVector4* src				= pMesh->GetControlPoints();				//	頂点座標配列
//	
//	mesh->countData.porygonCount	= pMesh->GetPolygonCount();					//	ポリゴン数
//	mesh->countData.indexCount		= pMesh->GetPolygonVertexCount();			//	インデックス数
//	mesh->countData.vertexCount		= mesh->countData.indexCount;				//	インデックス数分作るので
//	mesh->index						= new int[ mesh->countData.indexCount ];	//	頂点インデックス(こっちには再構築したインデックスが格納される)
//	int* tempIndex					= new int[ mesh->countData.indexCount ];	//	頂点インデックス							
//	// 頂点データの作成
//	mesh->vertex					= new VertexData[ mesh->countData.indexCount ];
//
//	// バーテクスブレンディングデータ
//	mesh->blending					= new VertexBlending[ mesh->countData.indexCount ];
//	math::Vector4*	weight			= new math::Vector4[ mesh->countData.indexCount ];
//	BoneIndex*		boneIndex		= new BoneIndex[ mesh->countData.indexCount ];
//
//	// ブレンディングデータの初期化(ボーンが無い場合もあるため初期化が必要)
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
//	// 仮のデータ
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
//			MessageBox( 0, "3角形以上のポリゴンが存在します。", NULL, MB_OK );
//			return false;
//		}
//		for( int j = 0; j < 3; j++ )
//		{
//			// インデックスの取得
//			tempIndex[ index ] = pMesh->GetPolygonVertex( i, j );
//			index++;
//		}
//	}
//
//	// 頂点座標をインデックス参照で作りなおす
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
//	// 頂点バッファの作成
//	mesh->vertexBuffer[ 0 ].Create( VertexBuffer::FLOAT3, mesh->countData.indexCount );
//	mesh->vertexBuffer[ 0 ].SetBuffer( posIndex, 0, mesh->countData.indexCount );
//	SafeArrayDelete( pos );
//	SafeArrayDelete( posIndex  );
//
//	//	インデックスバッファの作成
//	//	インデックス分作成するので0～インデックス数まで順にいれればいい
//	for( int i = 0; i < mesh->countData.indexCount; i++ )
//	{
//		mesh->index[ i ] = i;
//	}
//	mesh->indexBuffer->Create( IndexBuffer::BIT32,mesh->countData.indexCount );
//	mesh->indexBuffer->SetBuffer( mesh->index, 0, mesh->countData.indexCount );
//
//	// メッシュのデータは複数のレイヤーに格納されている
//	int layerCount = pMesh->GetLayerCount();
//
//	for( int i= 0; i < layerCount; i++ )
//	{
//		KFbxLayer* layer					= pMesh->GetLayer( i );
//		// メッシュレイヤーから各データを格納したレイヤーを取得
//		KFbxLayerElementNormal* normalElem	= layer->GetNormals();
//		KFbxLayerElementUV*		uvElem		= layer->GetUVs();
//
//		// 法線の読み込み
//		if( normalElem != NULL )
//		{
//			KFbxLayerElement::EMappingMode		mappingMode = normalElem->GetMappingMode();
//			KFbxLayerElement::EReferenceMode	refMode		= normalElem->GetReferenceMode();
//			int	normalCount									= normalElem->GetDirectArray().GetCount();
//			int	indexNum									= normalElem->GetIndexArray().GetCount();
//			
//			// 法線データの確保
//			math::Vector3* normal = new math::Vector3[ normalCount ];
//
//			for( int i = 0; i < normalCount; i++ )
//			{
//				normal[ i ].x = -(float)normalElem->GetDirectArray().GetAt( i )[ 0 ];
//				normal[ i ].y = (float)normalElem->GetDirectArray().GetAt( i )[ 1 ];
//				normal[ i ].z = (float)normalElem->GetDirectArray().GetAt( i )[ 2 ];
//			}
//
//			// 法線のインデックス参照で再構築
//			math::Vector3* normalIndex = new math::Vector3[ mesh->countData.indexCount ];
//			//	頂点数と個数が同じ場合、インデックスを共有できる
//			if( normalCount == vertexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					normalIndex[ i ]			= normal[ tempIndex[ i ] ];
//					mesh->vertex[ i ].normal	= normal[ tempIndex[ i ] ];
//				}
//			}
//			// 個数がインデックス分ある場合
//			else if( normalCount == mesh->countData.indexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					normalIndex[ i ]			= normal[ i ];
//					mesh->vertex[ i ].normal	= normal[ i ];
//				}
//			}
//			// 法線インデックスがある場合
//			else if( indexNum == mesh->countData.indexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					normalIndex[ i ]			= normal[ normalElem->GetIndexArray().GetAt( i ) ];
//					mesh->vertex[ i ].normal	= normal[ normalElem->GetIndexArray().GetAt( i ) ];
//				}
//			}
//
//			//	法線のバッファ作成
//			mesh->vertexBuffer[ 1 ].Create( VertexBuffer::FLOAT3, mesh->countData.indexCount );
//			mesh->vertexBuffer[ 1 ].SetBuffer( normalIndex, 0, mesh->countData.indexCount );
//			// 最後にいらなくなったのを解放
//			SafeArrayDelete( normal );
//			SafeArrayDelete( normalIndex );
//
//		}
//
//		// UV座標の読み込み
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
//			// UV座標の確保
//			// FBX内とDirectXでは座標系が違うので変える
//			for( int i = 0; i < uvCount; i++ )
//			{
//				uv[ i ].x =			(float)uvElem->GetDirectArray().GetAt( i )[ 0 ];
//				uv[ i ].y = 1.0f -	(float)uvElem->GetDirectArray().GetAt( i )[ 1 ];
//			}
//			// UVの再構築
//			math::Vector2* uvIndex = new math::Vector2[ mesh->countData.indexCount ];
//			// UVと頂点座標が同じ場合はインデックスを共有できる
//			if( uvCount == vertexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount; i++ )
//				{
//					uvIndex[ i ]			= uv[ tempIndex[ i ] ];
//					mesh->vertex[ i ].uv	= uv[ tempIndex[ i ] ];
//				}
//			}
//			//	UVがインデックスと同じ場合はそのまま代入
//			else if( uvCount == mesh->countData.indexCount )
//			{
//				for( int i = 0; i < mesh->countData.indexCount;i++ )
//				{
//					uvIndex[ i ]			= uv[ i ];
//					mesh->vertex[ i ].uv	= uv[ i ];
//				}
//			}
//			//	UVインデックスとインデックスが同じ場合はUVインデックスから参照する
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
//	//	マテリアルの取得
//	KFbxNode* materialNode = pMesh->GetNode();
//
//	//	マテリアル数の取得
//	mesh->countData.materialCount = materialNode->GetMaterialCount();
//
//	//	マテリアルデータの取得
//	if( mesh->countData.materialCount != 0 )
//	{
//		mesh->material = new MaterialData[ mesh->countData.materialCount ];
//
//		for( int i = 0; i < mesh->countData.materialCount; i++ )
//		{
//			KFbxSurfaceMaterial* material = materialNode->GetMaterial( i );
//
//			// lambertマテリアルの場合
//			if( material->GetClassId().Is( KFbxSurfaceLambert::ClassId ) )
//			{
//				  // Lambertにキャスト
//				   KFbxSurfaceLambert* lambert = (KFbxSurfaceLambert*)material;
//				   
//				   CreateLambert( lambert, &mesh->material[ i ] );
//				    // スペキュラ
//				   mesh->material[ i ].material.specular.r = 0.0f;
//				   mesh->material[ i ].material.specular.g = 0.0f;
//				   mesh->material[ i ].material.specular.b = 0.0f;
//				   mesh->material[ i ].material.specular.a = 1.0f;
//				   // 光沢
//				   mesh->material[ i ].power = 1.0f;
//
//			}
//			//	Phongマテリアルの場合
//			else if( material->GetClassId().Is( KFbxSurfacePhong::ClassId ) )
//			{
//				 // Phongにキャスト
//				 KFbxSurfacePhong* phong = (KFbxSurfacePhong*)material;
//
//				 // PhongはLambertを親に持つので大丈夫
//				 CreateLambert( phong, &mesh->material[ i ] );
//
//				 // スペキュラ
//				 mesh->material[i].material.specular.r = (float)phong->GetSpecularColor().Get()[ 0 ];
//				 mesh->material[i].material.specular.g = (float)phong->GetSpecularColor().Get()[ 1 ];
//				 mesh->material[i].material.specular.b = (float)phong->GetSpecularColor().Get()[ 2 ];
//
//				 // 光沢
//				 mesh->material[i].power = (float)phong->GetShininess().Get();
//			}
//		}
//	}
//
//	// ボーンの読み込み
//	// デフォーマーを得る
//	int defomerCount = pMesh->GetDeformerCount();
//	KFbxDeformer* pDeformer = pMesh->GetDeformer( 0 );								//	デフォーマー
//	KFbxSkin* pSkinInfo = static_cast< KFbxSkin* >( pDeformer );					//	スキン
//	KFbxCluster** m_ppCluster;														//	ボーン格納用クラス( FBX用 )
//
//	// ボーンの個数を得る
//	int boneCount		=	pSkinInfo->GetClusterCount();
//	mesh->bone			=	NULL;
//	mesh->boneCount		=	0;
//	// 0以上ならボーンがあるので読み込みをする
//	if( boneCount > 0 )
//	{
//		// ボーンデータのコピー
//		mesh->boneCount			= boneCount;											//	ボーンの数を格納
//		mesh->bone				= new Bone[ boneCount ];								//	ボーンクラスの確保
//		m_ppCluster				= new KFbxCluster*[ boneCount ];						//	クラスターの確保
//		VertexBlending*	blend	= new VertexBlending[ vertexCount ];					//	仮格納用頂点ブレンディング
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
//		// ボーンの取得
//		for( int i = 0; i < boneCount; i++ )
//		{
//			m_ppCluster[ i ] = pSkinInfo->GetCluster( i );
//			
//			int		iNumIndex	= m_ppCluster[ i ]->GetControlPointIndicesCount();//このボーンに影響を受ける頂点数
//			int*	piIndex		= m_ppCluster[ i ]->GetControlPointIndices();		//このボーンに影響を受ける頂点インデックス
//			double* pdWeight	= m_ppCluster[ i ]->GetControlPointWeights();		//このボーンに対する頂点への影響力
//	
//			//頂点の重みの取得
//			//頂点側からインデックスをたどって、頂点サイドで整理する
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
//		// ボーンデータをインデックス参照で展開
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
//		// ボーンの絶対姿勢の確保
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
//			// 絶対姿勢からオフセット行列を作成する
//			D3DXMatrixInverse( &mesh->bone[ i ].offset, 0, &mesh->bone[ i ].init );
//		}
//
//		// ボーン姿勢行列の確保(60Fps分の確保)
//		math::Matrix	mat;
//		KTime			time;
//		for( int i = 0; i < 61; i++ )
//		{
//			time.SetTime( 0, 0, 0, i, 0, KTime::eFRAMES60, 0 );//60フレーム/秒
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
//				// ボーンのフレーム時姿勢行列を格納
//				mesh->bone[ k ].boneMat.push_back( mat );
//			}
//		}
//
//		//	使い終わってたものを解放
//		SafeDelete( readCount );
//		SafeArrayDelete( m_ppCluster );
//		SafeArrayDelete( blend );
//	}
//	//	ブレンディングバッファの作成
//	mesh->vertexBuffer[ 3 ].Create( VertexBuffer::FLOAT4,mesh->countData.vertexCount );
//	mesh->vertexBuffer[ 4 ].Create( VertexBuffer::UBYTE4,mesh->countData.vertexCount );
//
//	mesh->vertexBuffer[ 3 ].SetBuffer( weight, 0, mesh->countData.vertexCount );
//	mesh->vertexBuffer[ 4 ].SetBuffer( boneIndex, 0, mesh->countData.vertexCount );
//
//	// いらなくなった配列の解放
//	SafeArrayDelete( tempIndex );
//	SafeArrayDelete( weight );
//	SafeArrayDelete( boneIndex );
//
//	// 読みこみ終了
//	return true;
//}
////	渡されたランバートマテリアルからデータを抜き出す。
//bool FbxDecoder::CreateLambert(KFbxSurfaceLambert* Lambert, MaterialData* mat)
//{
//	// アンビエント
//	mat->material.ambient.r		= (float)Lambert->GetAmbientColor().Get()[ 0 ];
//	mat->material.ambient.g		= (float)Lambert->GetAmbientColor().Get()[ 1 ];
//	mat->material.ambient.b		= (float)Lambert->GetAmbientColor().Get()[ 2 ];
//	mat->material.ambient.a		= 1.0f;
//
//	// ディフューズ
//	mat->material.diffuse.r		= (float)Lambert->GetDiffuseColor().Get()[ 0 ];
//	mat->material.diffuse.g		= (float)Lambert->GetDiffuseColor().Get()[ 1 ];
//	mat->material.diffuse.b		= (float)Lambert->GetDiffuseColor().Get()[ 2 ];
//	mat->material.diffuse.a		= 1.0f;
//
//	// エミッシブ
//	mat->material.emissive.r	= (float)Lambert->GetEmissiveColor().Get()[ 0 ];
//	mat->material.emissive.g	= (float)Lambert->GetEmissiveColor().Get()[ 1 ];
//	mat->material.emissive.b	= (float)Lambert->GetEmissiveColor().Get()[ 2 ];
//	mat->material.emissive.a	= 1.0f;
//
//	return true;
//}
//
////	モデルデータの取得
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