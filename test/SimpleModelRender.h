// インクルード
#include "../iruna/Include/iruna.h"

// ネームスペース
using namespace iruna;
using namespace graphics;


// ボード管理クラス
class CSimpleModelRender
{
private:

	VertexShader*			m_cSimpleVertexShader;			// モデル描画用頂点シェーダー
	PixelShader*			m_cSimplePixcelShader;			// モデル描画用ピクセル頂点シェーダー
	HullShader*				m_cSimpleHullShader;			// モデル描画用ハルシェーダー
	DomainShader*			m_cSimpleDomainShader;			//　モデル描画用ドメインシェーダー
	VertexDeclaration*		m_cVertexDec;					// 頂点フォーマット

	int						m_nCBufferSize;					// コンスタントバッファのサイズ　Vertex
	int						m_nHullCBufferSize;				// コンスタントバッファのサイズ　Hull
	int						m_nDomainCBufferSize;			// コンスタントバッファのサイズ　Domain

public:
	// コンストラクタ
	CSimpleModelRender();
	// デストラクタ
	~CSimpleModelRender();

	// コンスタントバッファの作成(バーテクス)
	void CreateConstantBuffer( int nSize );
	// コンスタントバッファの作成(ハルシェーダー)
	void CreateHullConstantBuffer(int nSize);
	// コンスタントバッファの作成(ドメインシェーダー)
	void CreateDomainConstantBuffer(int nSize);

	// テクスチャの設定
	void SetTexture( Texture* tex );
	// コンスタントバッファの設定
	void SetConstantBuffer( void* pcBuffer );
	// コンスタントバッファの設定(ハルシェーダー)
	void SetHullConstantBuffer(void* pcBuffer);
	// コンスタントバッファの設定(ドメインシェーダー)
	void SetDomainConstantBuffer(void* pcBuffer);
	// バッファの更新
	void UpDateConstantBuffer();

	// シェーダーの設定
	void SetShader();
};