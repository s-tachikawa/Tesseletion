
// インクルード
#include "board.h"
#include "UtiltyVertexDatas.h"

// コンストラクタ
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
// デストラクタ
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

// 板ポリの作成
bool CBoard::Create()
{
	// 各シェーダーを作成
	m_pcVertexShader = new VertexShader;
	m_pcPixcelShader = new PixelShader;
	m_pcVertexShader->CreateShader( "../Resource/Effect/FinalDrawHDAO.hlsl", "VS", ShaderBase::eShader5_0 );
	m_pcPixcelShader->CreateShader( "../Resource/Effect/FinalDrawHDAO.hlsl", "PS", ShaderBase::eShader5_0 );
	
	// 頂点レイアウトの作成
	// 入力レイアウトの定義
	D3D11_INPUT_ELEMENT_DESC layoutRGB[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof( float ) * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof( layoutRGB ) / sizeof( layoutRGB[0] );
	// バーテクスシェーダーから頂点レイアウトを作成
	m_pcVertexDec = new VertexDeclaration;
	m_pcVertexDec->Create( layoutRGB, numElements, m_pcVertexShader );

	// コンスタントバッファを作成
	m_pcVertexShader->CreateConstantBuffer(sizeof(STestParam));
	m_pcPixcelShader->CreateConstantBuffer(sizeof(STestParam));
	//// シャドウマップ用シェーダーを作成
	//m_pcShadowVertex = new VertexShader;
	//m_pcShadowPixcel = new PixelShader;
	//m_pcShadowVertex->CreateShader( "../Resource/Effect/ShadowMap.hlsl", "ShadowVS", ShaderBase::eShader5_0 );
	//m_pcShadowPixcel->CreateShader( "../Resource/Effect/ShadowMap.hlsl", "ShadowPS", ShaderBase::eShader5_0 );
	//// 入力レイアウトの定義
	//D3D11_INPUT_ELEMENT_DESC layoutShadowMap[] = {
	//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof( float ) * 3 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};
	//
	//numElements = sizeof( layoutShadowMap ) / sizeof( layoutShadowMap[0] );
	//// バーテクスシェーダーから頂点レイアウトを作成
	//m_pcShadowDec = new VertexDeclaration;
	//m_pcShadowDec->Create( layoutShadowMap, numElements, m_pcShadowVertex );
	//m_pcShadowVertex->CreateConstantBuffer( sizeof( math::Matrix ) );

	// 頂点バッファの作成
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

	//	SetBufferを呼び出して頂点情報を先に設定をしていないとBufferを作成できない
	int nVertexBufferSize = sizeof( sVertexData[0] );
	m_pcVertexBuffer->Create( nVertexBufferSize, nVertexCount );

	// インデックスバッファの作成
	int nVertexIndex[  6 ];
	//	前
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
	// ピクセルシェーダーで使用するコンスタントバッファを作成
	m_cHdaoRender->CreatePixcelConstantBuffer(sizeof(SHDAOParam));
	// バーテクスバッファ
	m_cHdaoRender->CreateConstantBuffer(sizeof(SHDAOParam));

	return true;
}

// X軸の回転の設定
void CBoard::SetRotation( float fRot )
{
	m_fRot = fRot;
}

// 拡大縮小率の設定
void CBoard::SetScal( float fScal )
{
	m_fScal = fScal;
	return;
}

// テクスチャの設定
void CBoard::SetTexture( Texture* pcTexture )
{
	m_pcTex = pcTexture;
	m_pcTex->CreateSamplerSate();
	return;
}
// シャドウマップの描画
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

	m_pcVertexBuffer->IntoStream(0);	//	頂点座標

	m_cHdaoRender->SetShader();

	m_cHdaoRender->SetPixcelConstantBuffer( &m_cHDAOPram );
	m_cHdaoRender->SetConstantBuffer(&m_cHDAOPram);
	
	m_cHdaoRender->SetTexture(0, pcNormalDepth);

	m_pcIndexBuffer->IntoIndices();
	// ポリゴンの描画
	m_cRender.SetMeshTopology(Primitive::TRIANGLE_LIST);
	// シェーダを設定して描画
	m_cRender.DrawIndexPrimitive(m_nIndexCount, 0, 0);
}

// シャドウマップの描画
void CBoard::DrawShadowMap( Camera spLightCamera, math::Vector3 pos )
{
	//math::WoldMatrix mWorld;
	//mWorld.SetTranslation( pos.x, pos.y, pos.z );
	//mWorld.SetRotation( m_fRot, 0, 0 );
	//mWorld.SetScal( m_fScal, m_fScal, m_fScal );
	//math::Matrix mLightViewProj = mWorld.GetWoldMatrix() * spLightCamera.GetView() * spLightCamera.GetProjection();

	//D3DXMatrixTranspose( &mLightViewProj, &mLightViewProj );

	//m_pcVertexBuffer->IntoStream( 0 );	//	頂点座標

	//m_pcShadowDec->Set();
	//// シェーダーのセット
	//m_pcShadowVertex->SetShader();
	//m_pcShadowPixcel->SetShader();

	//m_pcShadowVertex->SetConstantBuffer( &mLightViewProj, 0, sizeof( math::Matrix ) );

	//m_pcIndexBuffer->IntoIndices();
	//// ポリゴンの描画
	//m_cRender.SetMeshTopology( Primitive::TRIANGLE_LIST );
	//// シェーダを設定して描画
	//m_cRender.DrawIndexPrimitive( m_nIndexCount, 0, 0 );
}

// 板ポリの描画
void CBoard::Draw(Camera spCamera, math::Vector3 pos, Texture* pcHDAO, Texture* pcDecal )
{
	math::WoldMatrix mWorld;
	math::Matrix mWVP;
	mWorld.SetTranslation( pos.x, pos.y, pos.z );
	mWorld.SetRotation( m_fRot, 0, 0 );
	mWorld.SetScal( m_fScal, m_fScal, m_fScal );
	mWVP = mWorld.GetWoldMatrix() * spCamera.GetView() * spCamera.GetProjection();

	D3DXMatrixTranspose( &mWVP, &mWVP );

	m_pcVertexBuffer->IntoStream( 0 );	//	頂点座標

	m_pcVertexDec->Set();
	// シェーダーのセット
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
	// ポリゴンの描画
	m_cRender.SetMeshTopology( Primitive::TRIANGLE_LIST );
	// シェーダを設定して描画
	m_cRender.DrawIndexPrimitive( m_nIndexCount, 0, 0 );

	return;
}