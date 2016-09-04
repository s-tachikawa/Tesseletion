// インクルード
#include "../iruna/Include/iruna.h"

// ネームスペース
using namespace iruna;
using namespace graphics;


// ボード管理クラス
class CHDAORender
{
private:

	VertexShader*			m_cSimpleVertexShader;			// モデル描画用頂点シェーダー
	PixelShader*			m_cSimplePixcelShader;			// モデル描画用ピクセル頂点シェーダー
	VertexDeclaration*		m_cVertexDec;					// 頂点フォーマット

	int						m_nCBufferSize;					// コンスタントバッファのサイズ

public:
	// コンストラクタ
	CHDAORender();
	// デストラクタ
	~CHDAORender();

	// コンスタントバッファの作成
	void CreateConstantBuffer(int nSize);

	void CreatePixcelConstantBuffer( int nSize );

	// テクスチャの設定
	void SetTexture(int nNum, Texture* tex);
	// コンスタントバッファの設定
	void SetConstantBuffer(void* pcBuffer);

	void SetPixcelConstantBuffer(void* pcBuffer);
	// バッファの更新
	void UpDateConstantBuffer();

	// シェーダーの設定
	void SetShader();
};