
// インクルード
#include "../iruna/Include/iruna.h"

// ネームスペース
using namespace iruna;
using namespace graphics;


// ボード管理クラス
class CSprite
{
private:

	VertexShader*			m_pcVertexShader;			// バーテクスシェーダー　通常描画用
	PixelShader*			m_pcPixcelShader;			// ピクセルシェーダー	通常描画用
	VertexDeclaration*		m_pcVertexDec;				// 頂点レイアウト

	Texture*				m_pcTex;					// テクスチャクラス
	VertexBuffer*			m_pcVertexBuffer;			// バーテクスバッファ

	IndexBuffer*			m_pcIndexBuffer;			// インデックスバッファ
	int						m_nIndexCount;				// インデックスカウント

	float					m_fScal;					// 拡大縮小率
	DeviceController		m_cRender;

public:
	// コンストラクタ
	CSprite();
	// デストラクタ
	~CSprite();
	// 板ポリの作成
	bool Create();
	// サイズの設定
	void SetScal( float fScal );
	// テクスチャの設定
	void SetTexture( Texture* pcTexture );
	// 板ポリの描画
	// 第一引数 : カメラ構造体のポインタ
	// 第二引数 : 板ポリの座標
	void Draw( Camera pcCamera, math::Vector2 pos );
};
