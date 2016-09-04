#include "NormalDepthRender.h"

CNormalDepthRender::CNormalDepthRender()
{

	// �e�V�F�[�_�[���쐬
	m_cSimpleVertexShader = new VertexShader;
	m_cSimplePixcelShader = new PixelShader;
	bool a = m_cSimpleVertexShader->CreateShader("../Resource/Effect/NormalDepth.hlsl", "RenderVS", ShaderBase::eShader5_0);
	bool b = m_cSimplePixcelShader->CreateShader("../Resource/Effect/NormalDepth.hlsl", "RenderPS", ShaderBase::eShader5_0);

	// ���_���C�A�E�g�̍쐬
	// ���̓��C�A�E�g�̒�`
	// memo: �Ƃ肠�����`��ɕK�v�ȏ�񂾂�
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "DEPTH", 0, DXGI_FORMAT_R32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT numElements = sizeof(layoutRGB) / sizeof(layoutRGB[0]);
	// �o�[�e�N�X�V�F�[�_�[���璸�_���C�A�E�g���쐬
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
// �R���X�^���g�o�b�t�@�̍쐬
void CNormalDepthRender::CreateConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// �R���X�^���g�o�b�t�@���쐬
	m_cSimpleVertexShader->CreateConstantBuffer(nSize);
	return;
}
// �e�N�X�`���̐ݒ�
void CNormalDepthRender::SetTexture(Texture* tex)
{
	m_cSimplePixcelShader->SetTexture(tex);
}

// �R���X�^���g�o�b�t�@�̐ݒ�
void CNormalDepthRender::SetConstantBuffer(void* data)
{
	m_cSimpleVertexShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// ���f���X�V
void CNormalDepthRender::UpDateConstantBuffer()
{

	return;
}



//	���f���̕`��
void CNormalDepthRender::SetShader()
{
	m_cVertexDec->Set();
	// �V�F�[�_�[�̃Z�b�g
	m_cSimpleVertexShader->SetShader();
	m_cSimplePixcelShader->SetShader();

	return;
}