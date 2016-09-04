#include "HdaoRender.h"

CHDAORender::CHDAORender()
{

	// �e�V�F�[�_�[���쐬
	m_cSimpleVertexShader = new VertexShader;
	m_cSimplePixcelShader = new PixelShader;
	m_cSimpleVertexShader->CreateShader("../Resource/Effect/HDAO.hlsl", "RenderFullScreenVS", ShaderBase::eShader5_0);
	m_cSimplePixcelShader->CreateShader("../Resource/Effect/HDAO.hlsl", "RenderHDAOPS", ShaderBase::eShader5_0);

	// ���_���C�A�E�g�̍쐬
	// ���̓��C�A�E�g�̒�`
	// memo: �Ƃ肠�����`��ɕK�v�ȏ�񂾂�
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};
	UINT numElements = sizeof(layoutRGB) / sizeof(layoutRGB[0]);
	// �o�[�e�N�X�V�F�[�_�[���璸�_���C�A�E�g���쐬
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
// �R���X�^���g�o�b�t�@�̍쐬
void CHDAORender::CreateConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// �R���X�^���g�o�b�t�@���쐬
	m_cSimpleVertexShader->CreateConstantBuffer(nSize);
	return;
}
// �R���X�^���g�o�b�t�@�̍쐬
void CHDAORender::CreatePixcelConstantBuffer(int nSize)
{
	m_nCBufferSize = nSize;
	// �R���X�^���g�o�b�t�@���쐬
	m_cSimplePixcelShader->CreateConstantBuffer(nSize);
	return;
}
// �e�N�X�`���̐ݒ�
void CHDAORender::SetTexture(int nNum, Texture* tex)
{
	m_cSimplePixcelShader->SetTexture(tex, nNum);
}

// �R���X�^���g�o�b�t�@�̐ݒ�
void CHDAORender::SetConstantBuffer(void* data)
{
	m_cSimpleVertexShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// �R���X�^���g�o�b�t�@�̐ݒ�
void CHDAORender::SetPixcelConstantBuffer(void* data)
{
	m_cSimplePixcelShader->SetConstantBuffer(data, 0, m_nCBufferSize);
}

// ���f���X�V
void CHDAORender::UpDateConstantBuffer()
{

	return;
}



//	���f���̕`��
void CHDAORender::SetShader()
{
	m_cVertexDec->Set();
	// �V�F�[�_�[�̃Z�b�g
	m_cSimpleVertexShader->SetShader();
	m_cSimplePixcelShader->SetShader();

	return;
}