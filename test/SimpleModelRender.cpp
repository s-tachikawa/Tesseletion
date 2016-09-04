#include "SimpleModelRender.h"

CSimpleModelRender::CSimpleModelRender()
{

	// �e�V�F�[�_�[���쐬
	m_cSimpleVertexShader	= new VertexShader;
	m_cSimplePixcelShader	= new PixelShader;
	m_cSimpleHullShader		= new HullShader;
	m_cSimpleDomainShader	= new DomainShader;
	m_cSimpleVertexShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderVS", ShaderBase::eShader5_0);
	m_cSimplePixcelShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderPS", ShaderBase::eShader5_0);
	m_cSimpleHullShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderTriIntegerHS", ShaderBase::eShader5_0);
	m_cSimpleDomainShader->CreateShader("../Resource/Effect/render_tessellate.hlsl", "RenderTriDS", ShaderBase::eShader5_0);


	// ���_���C�A�E�g�̍쐬
	// ���̓��C�A�E�g�̒�`
	// memo: �Ƃ肠�����`��ɕK�v�ȏ�񂾂�
	
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	/*
	// ���̓��C�A�E�g�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	*/
	UINT numElements = sizeof(layoutRGB) / sizeof(layoutRGB[0]);
	// �o�[�e�N�X�V�F�[�_�[���璸�_���C�A�E�g���쐬
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
// �R���X�^���g�o�b�t�@�̍쐬
void CSimpleModelRender::CreateConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// �R���X�^���g�o�b�t�@���쐬
	m_cSimpleVertexShader->CreateConstantBuffer(nSize);
	return;
}
// �R���X�^���g�o�b�t�@�̍쐬(�n���V�F�[�_�[)
void CSimpleModelRender::CreateHullConstantBuffer(int nSize)
{
	m_nHullCBufferSize = nSize;
	// �R���X�^���g�o�b�t�@���쐬
	m_cSimpleHullShader->CreateConstantBuffer(nSize);
	return;
}
// �R���X�^���g�o�b�t�@�̍쐬(�h���C���V�F�[�_�[)
void CSimpleModelRender::CreateDomainConstantBuffer(int nSize)
{
	m_nDomainCBufferSize = nSize;
	// �R���X�^���g�o�b�t�@���쐬
	m_cSimpleDomainShader->CreateConstantBuffer(nSize);
	return;
}

// �e�N�X�`���̐ݒ�
void CSimpleModelRender::SetTexture( Texture* tex )
{
	m_cSimplePixcelShader->SetTexture(tex);
}

// �R���X�^���g�o�b�t�@�̐ݒ�
void CSimpleModelRender::SetConstantBuffer(void* data)
{
	m_cSimpleVertexShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// �n���V�F�[�_�[�̃R���X�^���g�o�b�t�@�ݒ�
void CSimpleModelRender::SetHullConstantBuffer(void* data)
{
	m_cSimpleHullShader->SetConstantBuffer(data, 1, sizeof(float)*2);
}
// �h���C���V�F�[�_�[�̃R���X�^���g�o�b�t�@�ݒ�
void CSimpleModelRender::SetDomainConstantBuffer(void* data)
{
	m_cSimpleDomainShader->SetConstantBuffer(data, 0, m_nDomainCBufferSize);
}

// ���f���X�V
void CSimpleModelRender::UpDateConstantBuffer()
{

	return;
}



//	���f���̕`��
void CSimpleModelRender::SetShader()
{
	m_cVertexDec->Set();
	// �V�F�[�_�[�̃Z�b�g
	m_cSimpleVertexShader->SetShader();
	m_cSimplePixcelShader->SetShader();
	m_cSimpleHullShader->SetShader();
	m_cSimpleDomainShader->SetShader();

	return;
}