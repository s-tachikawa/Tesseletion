
// �C���N���[�h
#include "board.h"
#include "UtiltyVertexDatas.h"

// �R���X�g���N�^
CBoard::CBoard()
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
CBoard::~CBoard()
{
	SafeDelete( m_pcVertexShader );
	SafeDelete( m_pcPixcelShader );
	
	SafeDelete( m_pcVertexBuffer );
	SafeDelete( m_pcVertexDec );
	SafeDelete( m_pcIndexBuffer );

	SafeDelete( m_pcShadowVertex );
	SafeDelete( m_pcShadowPixcel );
	SafeDelete( m_pcShadowDec );
	return;
}

// �|���̍쐬
bool CBoard::Create()
{
	// �e�V�F�[�_�[���쐬
	m_pcVertexShader = new VertexShader;
	m_pcPixcelShader = new PixelShader;
	m_pcVertexShader->CreateShader( "../Resource/Effect/FinalDrawHDAO.hlsl", "VS", ShaderBase::eShader5_0 );
	m_pcPixcelShader->CreateShader( "../Resource/Effect/FinalDrawHDAO.hlsl", "PS", ShaderBase::eShader5_0 );
	
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

	// �R���X�^���g�o�b�t�@���쐬
	m_pcVertexShader->CreateConstantBuffer(sizeof(STestParam));
	m_pcPixcelShader->CreateConstantBuffer(sizeof(STestParam));
	//// �V���h�E�}�b�v�p�V�F�[�_�[���쐬
	//m_pcShadowVertex = new VertexShader;
	//m_pcShadowPixcel = new PixelShader;
	//m_pcShadowVertex->CreateShader( "../Resource/Effect/ShadowMap.hlsl", "ShadowVS", ShaderBase::eShader5_0 );
	//m_pcShadowPixcel->CreateShader( "../Resource/Effect/ShadowMap.hlsl", "ShadowPS", ShaderBase::eShader5_0 );
	//// ���̓��C�A�E�g�̒�`
	//D3D11_INPUT_ELEMENT_DESC layoutShadowMap[] = {
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof( float ) * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};
	//
	//numElements = sizeof( layoutShadowMap ) / sizeof( layoutShadowMap[0] );
	//// �o�[�e�N�X�V�F�[�_�[���璸�_���C�A�E�g���쐬
	//m_pcShadowDec = new VertexDeclaration;
	//m_pcShadowDec->Create( layoutShadowMap, numElements, m_pcShadowVertex );
	//m_pcShadowVertex->CreateConstantBuffer( sizeof( math::Matrix ) );

	// ���_�o�b�t�@�̍쐬
	SBoardVertexBuffer sVertexData[] = 
	{
		{ math::Vector3( -1.0f, 1.0f, 0.0f ), math::Vector2( 0.0f, 0.0f ) },
		{ math::Vector3( 1.0f, 1.0f, 0.0f ), math::Vector2( 1.0f, 0.0f ) },
		{ math::Vector3( -1.0f, -1.0f, 0.0f ), math::Vector2( 0.0f, 1.0f ) },
		{ math::Vector3( 1.0f, -1.0f, 0.0f ), math::Vector2( 1.0f, 1.0f ) },
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

	m_cHdaoRender = new CHDAORender;
	// �s�N�Z���V�F�[�_�[�Ŏg�p����R���X�^���g�o�b�t�@���쐬
	m_cHdaoRender->CreatePixcelConstantBuffer(sizeof(SHDAOParam));
	// �o�[�e�N�X�o�b�t�@
	m_cHdaoRender->CreateConstantBuffer(sizeof(SHDAOParam));

	return true;
}

// X���̉�]�̐ݒ�
void CBoard::SetRotation( float fRot )
{
	m_fRot = fRot;
}

// �g��k�����̐ݒ�
void CBoard::SetScal( float fScal )
{
	m_fScal = fScal;
	return;
}

// �e�N�X�`���̐ݒ�
void CBoard::SetTexture( Texture* pcTexture )
{
	m_pcTex = pcTexture;
	m_pcTex->CreateSamplerSate();
	return;
}
// �V���h�E�}�b�v�̕`��
void CBoard::HDAORender(Camera spLightCamera, math::Vector3 pos, Texture* pcNormalDepth)
{
	math::WoldMatrix mWorld;
	mWorld.SetTranslation(pos.x, pos.y, pos.z);
	mWorld.SetRotation(m_fRot, 0, 0);
	mWorld.SetScal(m_fScal, m_fScal, m_fScal);
	math::Matrix mLightViewProj = mWorld.GetWoldMatrix() * spLightCamera.GetView() * spLightCamera.GetProjection();

	D3DXMatrixTranspose(&mLightViewProj, &mLightViewProj);

	m_cHDAOPram.g_AcceptAngle = 0.0f;
	m_cHDAOPram.g_AcceptDepth = 0.0000f;
	m_cHDAOPram.g_CheckRadius = 10.0f;
	m_cHDAOPram.g_Intensity = 5.0f;
	m_cHDAOPram.g_NormalScale = 1.0f;
	m_cHDAOPram.g_ProjParam = math::Vector4(spLightCamera.zNear, spLightCamera.zFar, tan(spLightCamera.fovY), spLightCamera.aspect);
	m_cHDAOPram.g_RejectDepth = 1.0f;
	m_cHDAOPram.g_ScreenParam = math::Vector4(1280.0f, 920.0f, 1.0f / 1280.0f, 1.0f/920.0f);
	m_cHDAOPram.g_UseNormal = 1.0f;

	//m_cHDAOPram.g_AcceptAngle = 1.0f;
	//m_cHDAOPram.g_AcceptDepth = 1.0000f;
	//m_cHDAOPram.g_CheckRadius = 10.0f;
	//m_cHDAOPram.g_Intensity = 5.0f;
	//m_cHDAOPram.g_NormalScale = 1.0f;
	//m_cHDAOPram.g_ProjParam = math::Vector4(spLightCamera.zNear, spLightCamera.zFar, tan(spLightCamera.fovY), spLightCamera.aspect);
	//m_cHDAOPram.g_RejectDepth = 1.0f;
	//m_cHDAOPram.g_ScreenParam = math::Vector4(1280.0f, 920.0f, 1.0f / 1280.0f, 1.0f/920.0f);
	//m_cHDAOPram.g_ScreenParam.x = 1280.0f;
	//m_cHDAOPram.g_ScreenParam.y = 920.0f;
	//m_cHDAOPram.g_ScreenParam.z = 1.0f / 1280.0f;
	//m_cHDAOPram.g_ScreenParam.w = 1.0f / 920.0f;
	//m_cHDAOPram.g_UseNormal = 1.0f;

	m_pcVertexBuffer->IntoStream(0);	//	���_���W

	m_cHdaoRender->SetShader();

	m_cHdaoRender->SetPixcelConstantBuffer( &m_cHDAOPram );
	m_cHdaoRender->SetConstantBuffer(&m_cHDAOPram);
	
	m_cHdaoRender->SetTexture(0, pcNormalDepth);

	m_pcIndexBuffer->IntoIndices();
	// �|���S���̕`��
	m_cRender.SetMeshTopology(Primitive::TRIANGLE_LIST);
	// �V�F�[�_��ݒ肵�ĕ`��
	m_cRender.DrawIndexPrimitive(m_nIndexCount, 0, 0);
}

// �V���h�E�}�b�v�̕`��
void CBoard::DrawShadowMap( Camera spLightCamera, math::Vector3 pos )
{
	//math::WoldMatrix mWorld;
	//mWorld.SetTranslation( pos.x, pos.y, pos.z );
	//mWorld.SetRotation( m_fRot, 0, 0 );
	//mWorld.SetScal( m_fScal, m_fScal, m_fScal );
	//math::Matrix mLightViewProj = mWorld.GetWoldMatrix() * spLightCamera.GetView() * spLightCamera.GetProjection();

	//D3DXMatrixTranspose( &mLightViewProj, &mLightViewProj );

	//m_pcVertexBuffer->IntoStream( 0 );	//	���_���W

	//m_pcShadowDec->Set();
	//// �V�F�[�_�[�̃Z�b�g
	//m_pcShadowVertex->SetShader();
	//m_pcShadowPixcel->SetShader();

	//m_pcShadowVertex->SetConstantBuffer( &mLightViewProj, 0, sizeof( math::Matrix ) );

	//m_pcIndexBuffer->IntoIndices();
	//// �|���S���̕`��
	//m_cRender.SetMeshTopology( Primitive::TRIANGLE_LIST );
	//// �V�F�[�_��ݒ肵�ĕ`��
	//m_cRender.DrawIndexPrimitive( m_nIndexCount, 0, 0 );
}

// �|���̕`��
void CBoard::Draw(Camera spCamera, math::Vector3 pos, Texture* pcHDAO, Texture* pcDecal )
{
	math::WoldMatrix mWorld;
	math::Matrix mWVP;
	mWorld.SetTranslation( pos.x, pos.y, pos.z );
	mWorld.SetRotation( m_fRot, 0, 0 );
	mWorld.SetScal( m_fScal, m_fScal, m_fScal );
	mWVP = mWorld.GetWoldMatrix() * spCamera.GetView() * spCamera.GetProjection();

	D3DXMatrixTranspose( &mWVP, &mWVP );

	m_pcVertexBuffer->IntoStream( 0 );	//	���_���W

	m_pcVertexDec->Set();
	// �V�F�[�_�[�̃Z�b�g
	m_pcVertexShader->SetShader();
	m_pcPixcelShader->SetShader();

	//m_pcVertexShader->SetConstantBuffer( &mWVP, 0, sizeof( math::Matrix ) );

	m_cTestShaderPrama.g_ScreenParam.x = 2.0f;
	m_pcVertexShader->SetConstantBuffer(&m_cTestShaderPrama, 0, sizeof(STestParam));
	m_pcPixcelShader->SetConstantBuffer(&m_cTestShaderPrama, 0, sizeof(STestParam));

	//if( m_pcTex )
	m_pcPixcelShader->SetTexture(pcDecal, 0);
	m_pcPixcelShader->SetTexture(pcHDAO, 1);

	m_pcIndexBuffer->IntoIndices();
	// �|���S���̕`��
	m_cRender.SetMeshTopology( Primitive::TRIANGLE_LIST );
	// �V�F�[�_��ݒ肵�ĕ`��
	m_cRender.DrawIndexPrimitive( m_nIndexCount, 0, 0 );

	return;
}