// インクルード
#include "../iruna/Include/iruna.h"
#include "SimpleModelRender.h"
#include "NormalDepthRender.h"

// ネームスペース
using namespace iruna;
using namespace graphics;

// バーテクスシェーダーに渡すパラメーター(SimpleModelRender.hlsl用)
struct SShaderParam
{
	math::Matrix m_World;
	math::Matrix m_View;
	math::Matrix m_Proj;

};

// バーテクスシェーダーに渡すパラメーター(NormalDepth.hlsl用)
struct SNormalDepthShaderParam
{
	math::Matrix m_World;
	math::Matrix m_View;
	math::Matrix m_Proj;
	math::Matrix m_WorldInv;
};

// ボード管理クラス
class CSgdModel
{
private:


	ModelData*			modelData;						//	レンダリングモデルデータ
	ModelLoader*		m_pcLoader;						// モデルローダー
		
	Texture*			m_pcModelTexture;				//	テクスチャ

	float				animeFlame;						//	アニメーションフレーム

	Camera				camera;							//	カメラ
	
	float				cameraUp;						//	カメラ拡大率
	float				cameraAngle;					//	カメラの角度

	math::Vector3		modelPos;		//	モデルの座標
	math::Vector3		modelAngle;		//	モデルの角度
	float				modelScale;		//	モデルのスケール

	POINT				oldPos;			//	モデルの過去座標
	POINT				newPos;			//	モデルの現在座標
	math::WoldMatrix	wold;			//	ワールド行列クラス


	math::Vector3 sLight;				// ライト

	CSimpleModelRender*			m_cSimpleShader;
	SShaderParam				m_sSimpleParam;
		
	CNormalDepthRender*			m_cNormalDepthShader;
	SNormalDepthShaderParam		m_sNormalDepthParam;

	DeviceController		m_cRender;

	float	g_TessFactor[2];

public:
	// コンストラクタ
	CSgdModel();
	// デストラクタ
	~CSgdModel();

	void UpDate();

	// 板ポリの描画
	// 第一引数 : カメラ構造体のポインタ
	// 第二引数 : 板ポリの座標
	void Draw(Camera spCamera, math::Vector3 pos);

	void NormalDepthRender(Camera spCamera, math::Vector3 pos);
};
