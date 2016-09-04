#include "HdaoRender.h"

CHDAORender::CHDAORender()
{

	// 各シェーダーを作成
	m_cSimpleVertexShader = new VertexShader;
	m_cSimplePixcelShader = new PixelShader;
	m_cSimpleVertexShader->CreateShader("../Resource/Effect/HDAO.hlsl", "RenderFullScreenVS", ShaderBase::eShader5_0);
	m_cSimplePixcelShader->CreateShader("../Resource/Effect/HDAO.hlsl", "RenderHDAOPS", ShaderBase::eShader5_0);

	// 頂点レイアウトの作成
	// 入力レイアウトの定義
	// memo: とりあえず描画に必要な情報だけ
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT numElements = sizeof(layoutRGB) / sizeof(layoutRGB[0]);
	// バーテクスシェーダーから頂点レイアウトを作成
	m_cVertexDec = new VertexDeclaration;
	m_cVertexDec->Create(layoutRGB, numElements, m_cSimpleVertexShader);

	return;
}
CHDAORender::~CHDAORender()
{
	SafeDelete(m_cSimpleVertexShader);
	SafeDelete(m_cSimplePixcelShader);
	SafeDelete(m_cVertexDec);

}
// コンスタントバッファの作成
void CHDAORender::CreateConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// コンスタントバッファを作成
	m_cSimpleVertexShader->CreateConstantBuffer(nSize);
	return;
}
// コンスタントバッファの作成
void CHDAORender::CreatePixcelConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// コンスタントバッファを作成
	m_cSimplePixcelShader->CreateConstantBuffer(nSize);
	return;
}
// テクスチャの設定
void CHDAORender::SetTexture(int nNum, Texture* tex)
{
	m_cSimplePixcelShader->SetTexture(tex, nNum);
}

// コンスタントバッファの設定
void CHDAORender::SetConstantBuffer(void* data)
{
	m_cSimpleVertexShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// コンスタントバッファの設定
void CHDAORender::SetPixcelConstantBuffer(void* data)
{
	m_cSimplePixcelShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// モデル更新
void CHDAORender::UpDateConstantBuffer()
{

	return;
}



//	モデルの描画
void CHDAORender::SetShader()
{
	m_cVertexDec->Set();
	// シェーダーのセット
	m_cSimpleVertexShader->SetShader();
	m_cSimplePixcelShader->SetShader();

	return;
}