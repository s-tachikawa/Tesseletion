
#include "box.h"
#include "UtiltyVertexDatas.h"

//	�R���X�g���N�^
CBox::CBox()
:	m_pcLayout( NULL ),
	m_pcVertexBuffer( NULL ),
	m_pcIndexBuffer( NULL ),
	m_pcVertexShader( NULL ),
	m_pcPixcelShader( NULL ),
	m_pcTexture( NULL )
{
	return;
}

// �f�X�g���N�^
CBox::~CBox()
{
	SafeDelete( m_pcTexture );
	SafeDelete( m_pcVertexBuffer );
	SafeDelete( m_pcVertexShader );
	SafeDelete( m_pcLayout );
	SafeDelete( m_pcPixcelShader );
	SafeDelete( m_pcIndexBuffer );

	SafeDelete( m_pcShadowDec );
	SafeDelete( m_pcShadowVertex );
	SafeDelete( m_pcShadowPixcel );
	return;
}

// �{�b�N�X�̍쐬
bool CBox::Create()
{
	// ���_�f�[�^�̐錾
	SBoxVertexData sVertexData[] = 
	{
		// �O
		{ math::Vector3( -1.0f, 1.0f, 1.0f ), math::Vector2( 0.0f, 0.0f ) },	// 0
		{ math::Vector3( 1.0f, 1.0f, 1.0f ), math::Vector2( 1.0f, 0.0f ) },		// 1
		{ math::Vector3( -1.0f, -1.0f, 1.0f ), math::Vector2( 0.0f, 1.0f ) },	// 2
		{ math::Vector3( 1.0f, -1.0f, 1.0f ), math::Vector2( 1.0f, 1.0f ) },	// 3
		// ���
		{ math::Vector3( -1.0f, 1.0f, -1.0f ), math::Vector2( 0.0f, 0.0f ) },	// 4
		{ math::Vector3( 1.0f, 1.0f, -1.0f ), math::Vector2( 1.0f, 0.0f ) },	// 5
		{ math::Vector3( -1.0f, -1.0f, -1.0f ), math::Vector2( 0.0f, 1.0f ) },	// 6
		{ math::Vector3( 1.0f, -1.0f, -1.0f ), math::Vector2( 1.0f, 1.0f ) },	// 7

		// ��
		{ math::Vector3( -1.0f, 1.0f, -1.0f ), math::Vector2( 0.0f, 0.0f ) },	// 8
		{ math::Vector3( 1.0f, 1.0f, -1.0f ), math::Vector2( 1.0f, 0.0f ) },	// 9
		{ math::Vector3( -1.0f, 1.0f, 1.0f ), math::Vector2( 0.0f, 1.0f ) },	// 10
		{ math::Vector3( 1.0f, 1.0f, 1.0f ), math::Vector2( 1.0f, 1.0f ) },		// 11

		// ��
		{ math::Vector3( -1.0f, -1.0f, 1.0f ), math::Vector2( 0.0f, 0.0f ) },	// 12
		{ math::Vector3( 1.0f, -1.0f, 1.0f ), math::Vector2( 1.0f, 0.0f ) },	// 13
		{ math::Vector3( -1.0f, -1.0f, -1.0f ), math::Vector2( 0.0f, 1.0f ) },	// 14
		{ math::Vector3( 1.0f, -1.0f, -1.0f ), math::Vector2( 1.0f, 1.0f ) },	// 15

		// �E
		{ math::Vector3( 1.0f, 1.0f, 1.0f ), math::Vector2( 0.0f, 0.0f ) },		// 16
		{ math::Vector3( 1.0f, 1.0f, -1.0f ), math::Vector2( 1.0f, 0.0f ) },	// 17
		{ math::Vector3( 1.0f, -1.0f, 1.0f ), math::Vector2( 0.0f, 1.0f ) },	// 18
		{ math::Vector3( 1.0f, -1.0f, -1.0f ), math::Vector2( 1.0f, 1.0f ) },	// 19

		// ��
		{ math::Vector3( -1.0f, 1.0f, -1.0f ), math::Vector2( 0.0f, 0.0f ) },	// 20
		{ math::Vector3( -1.0f, 1.0f, 1.0f ), math::Vector2( 1.0f, 0.0f ) },	// 21
		{ math::Vector3( -1.0f, -1.0f, -1.0f ), math::Vector2( 0.0f, 1.0f ) },	// 22
		{ math::Vector3( -1.0f, -1.0f, 1.0f ), math::Vector2( 1.0f, 1.0f ) },	// 23
	};

	// ���_�o�b�t�@�̍쐬
	m_pcVertexBuffer = new VertexBuffer;
	m_pcVertexBuffer->SetBuffer( sVertexData );
	int nVertexCount = sizeof( sVertexData ) / sizeof( sVertexData[ 0 ] );
	int nVertexBufferSize = sizeof( SBoxVertexData );
	m_pcVertexBuffer->Create( nVertexBufferSize, nVertexCount );

	// ���_�V�F�[�_�[�̍쐬
	m_pcVertexShader = new VertexShader;
	m_pcVertexShader->CreateShader( "../Resource/Effect/Simple.hlsl", "VS", ShaderBase::eShader5_0 );
	// �s�N�Z���V�F�[�_�[�̍쐬
	m_pcPixcelShader = new PixelShader;
	m_pcPixcelShader->CreateShader( "../Resource/Effect/Simple.hlsl", "PS", ShaderBase::eShader5_0 );
	// ���_���C�A�E�g�̍쐬

	// ���̓��C�A�E�g�̒�`
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof( float ) * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof( layout ) / sizeof( layout[0] );

	m_pcLayout = new VertexDeclaration;
	m_pcLayout->Create( layout, numElements, m_pcVertexShader );

	// �o�[�e�N�X�V�F�[�_�[
	m_pcVertexShader->CreateConstantBuffer( sizeof( math::Matrix ) );

	// �V���h�E�}�b�v�p�V�F�[�_�[�̍쐬
	
	// ���_�V�F�[�_�[�̍쐬
	m_pcShadowVertex = new VertexShader;
	m_pcShadowPixcel = new PixelShader;
	m_pcShadowVertex->CreateShader( "../Resource/Effect/ShadowMap.hlsl", "ShadowVS", ShaderBase::eShader5_0 );
	m_pcShadowPixcel->CreateShader( "../Resource/Effect/ShadowMap.hlsl", "ShadowPS", ShaderBase::eShader5_0 );
	// ���̓��C�A�E�g�̒�`
	D3D11_INPUT_ELEMENT_DESC layoutShadowMap[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof( float ) * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	numElements = sizeof( layoutShadowMap ) / sizeof( layoutShadowMap[0] );

	m_pcShadowDec = new VertexDeclaration;
	m_pcShadowDec->Create( layoutShadowMap, numElements, m_pcShadowVertex );
	m_pcShadowVertex->CreateConstantBuffer( sizeof( math::Matrix ) );

	// �C���f�b�N�X�o�b�t�@�̍쐬
	int nVertexIndex[ 36 ];
	//	�O
	nVertexIndex[ 0 ] = 0;
	nVertexIndex[ 1 ] = 1;
	nVertexIndex[ 2 ] = 2;
	nVertexIndex[ 3 ] = 3;
	nVertexIndex[ 4 ] = 2;
	nVertexIndex[ 5 ] = 1;
	//	���
	nVertexIndex[ 6 ] = 5;
	nVertexIndex[ 7 ] = 4;
	nVertexIndex[ 8 ] = 7;
	nVertexIndex[ 9 ] = 6;
	nVertexIndex[ 10 ] = 7;
	nVertexIndex[ 11 ] = 4;
	//	�E
	nVertexIndex[ 12 ] = 16;	
	nVertexIndex[ 13 ] = 17;
	nVertexIndex[ 14 ] = 18;
	nVertexIndex[ 15 ] = 19;
	nVertexIndex[ 16 ] = 18;
	nVertexIndex[ 17 ] = 17;
	//	��
	nVertexIndex[ 18 ] = 20;	
	nVertexIndex[ 19 ] = 21;
	nVertexIndex[ 20 ] = 22;
	nVertexIndex[ 21 ] = 23;
	nVertexIndex[ 22 ] = 22;
	nVertexIndex[ 23 ] = 21;
	//	��
	nVertexIndex[ 24 ] = 8;
	nVertexIndex[ 25 ] = 9;
	nVertexIndex[ 26 ] = 10;
	nVertexIndex[ 27 ] = 11;
	nVertexIndex[ 28 ] = 10;
	nVertexIndex[ 29 ] = 9;
	//	��
	nVertexIndex[ 30 ] = 3;
	nVertexIndex[ 31 ] = 2;
	nVertexIndex[ 32 ] = 7;
	nVertexIndex[ 33 ] = 6;
	nVertexIndex[ 34 ] = 7;
	nVertexIndex[ 35 ] = 3;
	

	m_pcIndexBuffer = new IndexBuffer;
	m_pcIndexBuffer->SetBuffer( nVertexIndex );
	m_nIndexCount = sizeof( nVertexIndex ) / sizeof( nVertexIndex[ 0 ] );
	m_pcIndexBuffer->Create( IndexBuffer::BIT32, m_nIndexCount );

	m_pcTexture = new Texture;
	m_pcTexture->Load( "../Resource/Texture/sample.png" );
	m_pcTexture->CreateSamplerSate();


	m_fRot = 0.0f;
	return true;
}

// �{�b�N�X�̉�]
void CBox::SetRotation( math::Vector3 vRot )
{
	return;
}

// �V���h�E�}�b�v�̕`��
void CBox::DrawShadowMap( Camera spLightCamera, math::Vector3 vPos )
{
	math::WoldMatrix mWorld;
	mWorld.SetTranslation( vPos.x, vPos.y, vPos.z );
	mWorld.SetRotation( 0, 0, 0 );
	mWorld.SetScal( 10, 10, 10 );
	
	math::Matrix mLightViewProj = mWorld.GetWoldMatrix() * spLightCamera.GetView() * spLightCamera.GetProjection();

	D3DXMatrixTranspose( &mLightViewProj, &mLightViewProj );

	m_pcVertexBuffer->IntoStream( 0 );	//	���_���W

	m_pcShadowDec->Set();
	m_pcIndexBuffer->IntoIndices();

	m_pcShadowVertex->SetConstantBuffer( &mLightViewProj, 0, sizeof( math::Matrix ) );

	// �V�F�[�_�[�̃Z�b�g
	m_pcShadowVertex->SetShader();
	m_pcShadowPixcel->SetShader();
	
	// �|���S���̕`��
	m_cRender.SetMeshTopology( Primitive::TRIANGLE_LIST );
	// �V�F�[�_��ݒ肵�ĕ`��
	m_cRender.DrawIndexPrimitive( m_nIndexCount, 0, 0 );
}

// �{�b�N�X�̕`��
void CBox::Draw( Camera psCamera, math::Vector3 vPos )
{
	//m_fRot += 0.00001f;
	// �ʒu�̐ݒ�
	math::WoldMatrix mWorld;
	mWorld.SetTranslation( vPos.x, vPos.y, vPos.z );
	mWorld.SetRotation( 0, D3DX_PI / 4.0f, 0 );
	mWorld.SetScal( 10, 10, 10 );

	math::Matrix mWVP = mWorld.GetWoldMatrix() * psCamera.GetView() * psCamera.GetProjection();
	D3DXMatrixTranspose( &mWVP, &mWVP );
	m_pcLayout->Set();
	m_pcIndexBuffer->IntoIndices();
	m_pcVertexBuffer->IntoStream( 0 );

	m_pcVertexShader->SetConstantBuffer( &mWVP, 0, sizeof( math::Matrix ) );
	m_pcPixcelShader->SetTexture( m_pcTexture );

	m_pcVertexShader->SetShader();
	m_pcPixcelShader->SetShader();

	m_cRender.SetMeshTopology( Primitive::TRIANGLE_LIST );
	m_cRender.DrawIndexPrimitive( m_nIndexCount, 0, 0 );

	return;
}