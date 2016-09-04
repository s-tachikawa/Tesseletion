
// インクルード
#include "../iruna/Include/iruna.h"
#include "HdaoRender.h"

// ネームスペース
using namespace iruna;
using namespace graphics;

// バーテクスシェーダーに渡すパラメーター(NormalDepth.hlsl用)
struct SHDAOParam
{
	math::Vector4	g_ScreenParam;		// (width, height, 1.0/width, 1.0/height)
	math::Vector4	g_ProjParam;		// (near, far, tan(fovy), aspect)
	float			g_CheckRadius;
	float			g_RejectDepth;
	float			g_AcceptDepth;
	float			g_Intensity;
	float			g_AcceptAngle;
	int				g_UseNormal;
	float			g_NormalScale;
	float			g_Offset;
};

// バーテクスシェーダーに渡すパラメーター(NormalDepth.hlsl用)
struct STestParam
{
	math::Vector4	g_ScreenParam;		// (width, height, 1.0/width, 1.0/height)
	math::Vector4	g_ProjParam;		// (near, far, tan(fovy), aspect)
	float	g_CheckRadius;
	float			g_RejectDepth;
	float			g_AcceptDepth;
	float			g_Intensity;
	float			g_AcceptAngle;
	float				g_UseNormal;
	float			g_NormalScale;
	float			g_Offset;
};
// ボード管理クラス
class CBoard
{
private:
	
	VertexShader*			m_pcVertexShader;			// バーテクスシェーダー　通常描画用
	PixelShader*			m_pcPixcelShader;			// ピクセルシェーダー	通常描画用
	VertexDeclaration*		m_pcVertexDec;				// 頂点レイアウト

	VertexShader*			m_pcShadowVertex;			// バーテクスシェーダー　深度マップ描画用
	PixelShader*			m_pcShadowPixcel;			// ピクセルシェーダー	深度マップ描画用
	VertexDeclaration*		m_pcShadowDec;				// 頂点レイアウト		深度マップ描画用

	Texture*				m_pcTex;					// テクスチャクラス
	VertexBuffer*			m_pcVertexBuffer;			// バーテクスバッファ
	
	IndexBuffer*			m_pcIndexBuffer;			// インデックスバッファ
	int						m_nIndexCount;				// インデックスカウント

	float					m_fRot;						// 回転
	float					m_fScal;					// 拡大縮小率
	DeviceController		m_cRender;

	CHDAORender*			m_cHdaoRender;				// HDAO描画用レンダラー
	SHDAOParam				m_cHDAOPram;


	// Todo: Test とりあえずテスト s_tachikawa
	STestParam m_cTestShaderPrama;


public:
	// コンストラクタ
	CBoard();
	// デストラクタ
	~CBoard();
	// 板ポリの作成
	bool Create();
	// X軸回転の設定
	void SetRotation( float fRot );
	// 回転の設定
	void SetScal( float fScal );
	// テクスチャの設定
	void SetTexture( Texture* pcTexture );
	// シャドウマップの描画
	// 第一引数 : ライトカメラのポインタ
	void DrawShadowMap( Camera spLightCamera, math::Vector3 pos );
	// 板ポリの描画
	// 第一引数 : カメラ構造体のポインタ
	// 第二引数 : 板ポリの座標
	void Draw(Camera spCamera, math::Vector3 pos, Texture* pcHDAO, Texture* pcDecal);

	// HDAOの描画
	void HDAORender(Camera spCamera, math::Vector3 pos, Texture* pcNormalDepth);

};
