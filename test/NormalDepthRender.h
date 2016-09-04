// インクルード
#include "../iruna/Include/iruna.h"

// ネームスペース
using namespace iruna;
using namespace graphics;


// ボード管理クラス
class CNormalDepthRender
{
private:

	VertexShader*			m_cSimpleVertexShader;			// モデル描画用頂点シェーダー
	PixelShader*			m_cSimplePixcelShader;			// モデル描画用ピクセル頂点シェーダー
	VertexDeclaration*		m_cVertexDec;					// 頂点フォーマット

	int						m_nCBufferSize;					// コンスタントバッファのサイズ

public:
	// コンストラクタ
	CNormalDepthRender();
	// デストラクタ
	~CNormalDepthRender();

	// コンスタントバッファの作成
	void CreateConstantBuffer(int nSize);

	// テクスチャの設定
	void SetTexture(Texture* tex);
	// コンスタントバッファの設定
	void SetConstantBuffer(void* pcBuffer);
	// バッファの更新
	void UpDateConstantBuffer();

	// シェーダーの設定
	void SetShader();
};