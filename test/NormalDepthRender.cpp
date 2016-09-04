#include "NormalDepthRender.h"

CNormalDepthRender::CNormalDepthRender()
{

	// 各シェーダーを作成
	m_cSimpleVertexShader = new VertexShader;
	m_cSimplePixcelShader = new PixelShader;
	bool a = m_cSimpleVertexShader->CreateShader("../Resource/Effect/NormalDepth.hlsl", "RenderVS", ShaderBase::eShader5_0);
	bool b = m_cSimplePixcelShader->CreateShader("../Resource/Effect/NormalDepth.hlsl", "RenderPS", ShaderBase::eShader5_0);

	// 頂点レイアウトの作成
	// 入力レイアウトの定義
	// memo: とりあえず描画に必要な情報だけ
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "DEPTH", 0, DXGI_FORMAT_R32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT numElements = sizeof(layoutRGB) / sizeof(layoutRGB[0]);
	// バーテクスシェーダーから頂点レイアウトを作成
	m_cVertexDec = new VertexDeclaration;
	m_cVertexDec->Create(layoutRGB, numElements, m_cSimpleVertexShader);




	return;
}
CNormalDepthRender::~CNormalDepthRender()
{
	SafeDelete(m_cSimpleVertexShader);
	SafeDelete(m_cSimplePixcelShader);
	SafeDelete(m_cVertexDec);

}
// コンスタントバッファの作成
void CNormalDepthRender::CreateConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// コンスタントバッファを作成
	m_cSimpleVertexShader->CreateConstantBuffer(nSize);
	return;
}
// テクスチャの設定
void CNormalDepthRender::SetTexture(Texture* tex)
{
	m_cSimplePixcelShader->SetTexture(tex);
}

// コンスタントバッファの設定
void CNormalDepthRender::SetConstantBuffer(void* data)
{
	m_cSimpleVertexShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// モデル更新
void CNormalDepthRender::UpDateConstantBuffer()
{

	return;
}



//	モデルの描画
void CNormalDepthRender::SetShader()
{
	m_cVertexDec->Set();
	// シェーダーのセット
	m_cSimpleVertexShader->SetShader();
	m_cSimplePixcelShader->SetShader();

	return;
}