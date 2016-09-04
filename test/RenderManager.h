

// インクルード
#include "../iruna/Include/iruna.h"

// ネームスペース
using namespace iruna;
using namespace graphics;


// レンダリングの管理クラス
class RenderManager
{
public:
	enum ERenderStep
	{
		eShadowMap,			// シャドウマップ
		eRGBA,				// 通常描画(RGB)
		eRenderStepMax
	};

private:

public:
	// コンストラクタ
	RenderManager();
	// デストラクタ
	~RenderManager();
	// 初期化
	bool Init();
	//　描画するメッシュを登録する
	void SetDrawMesh();
	//　レンダリングステップの設定
	void SetRenderStep( ERenderStep eStep );
};