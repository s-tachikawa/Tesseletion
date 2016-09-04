#include "SimpleModelRender.h"

CSimpleModelRender::CSimpleModelRender()
{

	// 各シェーダーを作成
	m_cSimpleVertexShader	= new VertexShader;
	m_cSimplePixcelShader	= new PixelShader;
	m_cSimpleHullShader		= new HullShader;
	m_cSimpleDomainShader	= new DomainShader;
	m_cSimpleVertexShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderVS", ShaderBase::eShader5_0);
	m_cSimplePixcelShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderPS", ShaderBase::eShader5_0);
	m_cSimpleHullShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderTriIntegerHS", ShaderBase::eShader5_0);
	m_cSimpleDomainShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderTriDS", ShaderBase::eShader5_0);


	// 頂点レイアウトの作成
	// 入力レイアウトの定義
	// memo: とりあえず描画に必要な情報だけ
	
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	/*
	// 入力レイアウトの定義
	D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	*/
	UINT numElements = sizeof(layoutRGB) / sizeof(layoutRGB[0]);
	// バーテクスシェーダーから頂点レイアウトを作成
	m_cVertexDec = new VertexDeclaration;
	m_cVertexDec->Create(layoutRGB, numElements, m_cSimpleVertexShader);

	return;
}
CSimpleModelRender::~CSimpleModelRender()
{
	SafeDelete(m_cSimpleVertexShader);
	SafeDelete(m_cSimplePixcelShader);
	SafeDelete(m_cVertexDec);

}
// コンスタントバッファの作成
void CSimpleModelRender::CreateConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// コンスタントバッファを作成
	m_cSimpleVertexShader->CreateConstantBuffer(nSize);
	return;
}
// コンスタントバッファの作成(ハルシェーダー)
void CSimpleModelRender::CreateHullConstantBuffer(int nSize)
{
	m_nHullCBufferSize = nSize;
	// コンスタントバッファを作成
	m_cSimpleHullShader->CreateConstantBuffer(nSize);
	return;
}
// コンスタントバッファの作成(ドメインシェーダー)
void CSimpleModelRender::CreateDomainConstantBuffer(int nSize)
{
	m_nDomainCBufferSize = nSize;
	// コンスタントバッファを作成
	m_cSimpleDomainShader->CreateConstantBuffer(nSize);
	return;
}

// テクスチャの設定
void CSimpleModelRender::SetTexture( Texture* tex )
{
	m_cSimplePixcelShader->SetTexture(tex);
}

// コンスタントバッファの設定
void CSimpleModelRender::SetConstantBuffer(void* data)
{
	m_cSimpleVertexShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// ハルシェーダーのコンスタントバッファ設定
void CSimpleModelRender::SetHullConstantBuffer(void* data)
{
	m_cSimpleHullShader->SetConstantBuffer(data, 1, sizeof(float)*2);
}
// ドメインシェーダーのコンスタントバッファ設定
void CSimpleModelRender::SetDomainConstantBuffer(void* data)
{
	m_cSimpleDomainShader->SetConstantBuffer(data, 0, m_nDomainCBufferSize);
}

// モデル更新
void CSimpleModelRender::UpDateConstantBuffer()
{

	return;
}



//	モデルの描画
void CSimpleModelRender::SetShader()
{
	m_cVertexDec->Set();
	// シェーダーのセット
	m_cSimpleVertexShader->SetShader();
	m_cSimplePixcelShader->SetShader();
	m_cSimpleHullShader->SetShader();
	m_cSimpleDomainShader->SetShader();

	return;
}