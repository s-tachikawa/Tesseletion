
// �C���N���[�h
#include "sprite.h"
#include "UtiltyVertexDatas.h"

// �R���X�g���N�^
CSprite::CSprite()
:	m_pcVertexShader( NULL ),
m_pcPixcelShader( NULL ),
m_pcTex( NULL ),
m_pcVertexBuffer( NULL ),
m_pcVertexDec( NULL ),
m_pcIndexBuffer( NULL )
{
	return;
}
// �f�X�g���N�^
CSprite::~CSprite()
{
	SafeDelete( m_pcVertexShader );
	SafeDelete( m_pcPixcelShader );

	SafeDelete( m_pcVertexBuffer );
	SafeDelete( m_pcVertexDec );
	SafeDelete( m_pcIndexBuffer );

	return;
}

// �|���̍쐬
bool CSprite::Create()
{
	// �e�V�F�[�_�[���쐬
	m_pcVertexShader = new VertexShader;
	m_pcPixcelShader = new PixelShader;
	bool a = m_pcVertexShader->CreateShader( "../Resource/Effect/Sprite.hlsl", "VS", ShaderBase::eShader5_0 );
	bool b = m_pcPixcelShader->CreateShader( "../Resource/Effect/Sprite.hlsl", "PS", ShaderBase::eShader5_0 );

	// ���_���C�A�E�g�̍쐬
	// ���̓��C�A�E�g�̒�`
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof( float ) * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof( layoutRGB ) / sizeof( layoutRGB[0] );
	// �o�[�e�N�X�V�F�[�_�[���璸�_���C�A�E�g���쐬
	m_pcVertexDec = new VertexDeclaration;
	m_pcVertexDec->Create( layoutRGB, numElements, m_pcVertexShader );

	//m_pcVertexShader->CreateConstantBuffer( sizeof( math::Matrix ) );
	// ���_�o�b�t�@�̍쐬
	SBoardVertexBuffer sVertexData[] = 
	{
		{ math::Vector3( -1.0f, 1.0f, 0.0f ), math::Vector2( 0.0f, 0.0f ) },
		{ math::Vector3(1.0f*0.001f, 1.0f, 0.0f), math::Vector2(1.0f, 0.0f) },
		{ math::Vector3(-1.0f, -1.0f*0.001f, 0.0f), math::Vector2(0.0f, 1.0f) },
		{ math::Vector3(1.0f*0.001f, -1.0f*0.001f, 0.0f), math::Vector2(1.0f, 1.0f) },
	};

	int nVertexCount = sizeof( sVertexData ) / sizeof( sVertexData[ 0 ] );

	m_pcVertexBuffer = new VertexBuffer;
	m_pcVertexBuffer->SetBuffer( sVertexData );

	//	SetBuffer���Ăяo���Ē��_�����ɐݒ�����Ă��Ȃ���Buffer���쐬�ł��Ȃ�
	int nVertexBufferSize = sizeof( sVertexData[0] );
	m_pcVertexBuffer->Create( nVertexBufferSize, nVertexCount );

	// �C���f�b�N�X�o�b�t�@�̍쐬
	int nVertexIndex[  6 ];
	//	�O
	nVertexIndex[ 0 ] = 0;	
	nVertexIndex[ 1 ] = 1;
	nVertexIndex[ 2 ] = 2;

	nVertexIndex[ 3 ] = 3;
	nVertexIndex[ 4 ] = 2;
	nVertexIndex[ 5 ] = 1;

	m_nIndexCount = sizeof( nVertexIndex ) / sizeof( nVertexIndex[ 0 ] );
	m_pcIndexBuffer = new IndexBuffer;
	m_pcIndexBuffer->SetBuffer( nVertexIndex );
	m_pcIndexBuffer->Create( IndexBuffer::BIT32, m_nIndexCount );

	return true;
}

// �g��k�����̐ݒ�
void CSprite::SetScal( float fScal )
{
	m_fScal = fScal;
	return;
}

// �e�N�X�`���̐ݒ�
void CSprite::SetTexture( Texture* pcTexture )
{
	m_pcTex = pcTexture;
	m_pcTex->CreateSamplerSate();
	return;
}

// �|���̕`��
void CSprite::Draw( Camera pcCamera, math::Vector2 pos )
{	
	
	m_pcVertexBuffer->IntoStream(0);	//	���_���W

	m_pcVertexDec->Set();
	// �V�F�[�_�[�̃Z�b�g
	m_pcVertexShader->SetShader();
	m_pcPixcelShader->SetShader();

	if (m_pcTex)
		m_pcPixcelShader->SetTexture(m_pcTex);

	m_pcIndexBuffer->IntoIndices();
	// �|���S���̕`��
	m_cRender.SetMeshTopology(Primitive::TRIANGLE_LIST);
	// �V�F�[�_��ݒ肵�ĕ`��
	m_cRender.DrawIndexPrimitive(m_nIndexCount, 0, 0);

	return;
}