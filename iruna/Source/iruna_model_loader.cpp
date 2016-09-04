//---------------------------------------------------------
// 
//	iruna_model_loader.h
//	指定したモデルデータ読み込み
//	作成日 10月21日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
#include "../Include/iruna_model_loader.h"
#include "../Source/iruna_model_decoder.h"
#include "../Source/iruna_sgd_decoder.h"
#include "../Source/iruna_fbx_decoder.h"
#include "../Source/iruna_pmd_decoder.h"

namespace iruna
{
namespace graphics
{
//	コンストラクタ
ModelLoader::ModelLoader()
	:loader( NULL )
{
	return;
}

//	デストラクタ
ModelLoader::~ModelLoader()
{
	Relese();

	return;
}

// 解放処理
void ModelLoader::Relese()
{

	if( loader != NULL )
	{
		loader->Relese();
		SafeDelete( loader );
	}
	return;
}

// 指定したファイルの読み込み
bool ModelLoader::Load( std::string in_path )
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

	//	SGDとして読み込み
	if( strcmp( temp, ".sgd" ) == 0 )
	{
		loader	= new SgdDecoder;
		type	= Sgd;
	}

	// FBXとして読み込み
	if( strcmp( temp, ".fbx" ) == 0 ||  strcmp( temp, ".FBX" ) == 0)
	{
		//loader	= new FbxDecoder;
		type	= Fbx;
	}
	// PMDとして読み込み
	if( strcmp( temp, ".pmd" ) == 0 ||  strcmp( temp, ".PMD" ) == 0)
	{
		//loader	= new PmdDecoder;
		type	= Pmd;
	}


	loader->Init();

	return loader->Decode( in_path, type );

}

//	モデルデータの取得
ModelData* ModelLoader::GetModelData()
{
	if( loader != NULL )
		return loader->GetModelData();

	return NULL;
}

}	//	graphics	end
}	//	iruna		end