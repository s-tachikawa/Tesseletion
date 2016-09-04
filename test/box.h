
// インクルード
#include "../iruna/Include/iruna.h"

// ネームスペース
using namespace iruna;
using namespace	graphics;
using namespace core;
using namespace sound;
using namespace physics;
using namespace io;

// ボックスクラスの作成と管理
class CBox
{
private:

	VertexShader*			m_pcShadowVertex;			// バーテクスシェーダー　深度マップ描画用
	PixelShader*			m_pcShadowPixcel;			// ピクセルシェーダー	深度マップ描画用
	VertexDeclaration*		m_pcShadowDec;				// 頂点レイアウト		深度マップ描画用

	VertexDeclaration*	m_pcLayout;				// 頂点レイアウト
	VertexBuffer*		m_pcVertexBuffer;		// 頂点バッファ

	IndexBuffer*		m_pcIndexBuffer;		// インデックスバッファ
	int					m_nIndexCount;			// インデックスカウント

	VertexShader*		m_pcVertexShader;		// バーテクスシェーダー
	PixelShader*		m_pcPixcelShader;		// ピクセルシェーダー
	Texture*			m_pcTexture;			// テクスチャ

	DeviceController	m_cRender;				// デバイスコンテキスト

	float				m_fRot;

public:
	// コンストラクタ
	CBox();
	// デストラクタ
	~CBox();
	// ボックスの作成
	bool Create();
	// ボックスの位置を指定
	// 第一引数 vRot :  ボックスの回転
	void SetRotation( math::Vector3 vRot );
	// シャドウマップの描画
	void DrawShadowMap( Camera spLightCamera, math::Vector3 vPos );
	// ボックスの描画
	// 第一引数 vPos : 描画する位置
	// 第二引数 sCamera : 写すカメラ構造体のポインタ
	void Draw( Camera psCamera,  math::Vector3 vPos );
};