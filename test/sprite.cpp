
// インクルード
#include "sprite.h"
#include "UtiltyVertexDatas.h"

// コンストラクタ
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
// デストラクタ
CSprite::~CSprite()
{
	SafeDelete( m_pcVertexShader );
	SafeDelete( m_pcPixcelShader );

	SafeDelete( m_pcVertexBuffer );
	SafeDelete( m_pcVertexDec );
	SafeDelete( m_pcIndexBuffer );

	return;
}

// 板ポリの作成
bool CSprite::Create()
{
	// 各シェーダーを作成
	m_pcVertexShader = new VertexShader;
	m_pcPixcelShader = new PixelShader;
	bool a = m_pcVertexShader->CreateShader( "../Resource/Effect/Sprite.hlsl", "VS", ShaderBase::eShader5_0 );
	bool b = m_pcPixcelShader->CreateShader( "../Resource/Effect/Sprite.hlsl", "PS", ShaderBase::eShader5_0 );

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

	//m_pcVertexShader->CreateConstantBuffer( sizeof( math::Matrix ) );
	// 頂点バッファの作成
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

	return true;
}

// 拡大縮小率の設定
void CSprite::SetScal( float fScal )
{
	m_fScal = fScal;
	return;
}

// テクスチャの設定
void CSprite::SetTexture( Texture* pcTexture )
{
	m_pcTex = pcTexture;
	m_pcTex->CreateSamplerSate();
	return;
}

// 板ポリの描画
void CSprite::Draw( Camera pcCamera, math::Vector2 pos )
{	
	
	m_pcVertexBuffer->IntoStream(0);	//	頂点座標

	m_pcVertexDec->Set();
	// シェーダーのセット
	m_pcVertexShader->SetShader();
	m_pcPixcelShader->SetShader();

	if (m_pcTex)
		m_pcPixcelShader->SetTexture(m_pcTex);

	m_pcIndexBuffer->IntoIndices();
	// ポリゴンの描画
	m_cRender.SetMeshTopology(Primitive::TRIANGLE_LIST);
	// シェーダを設定して描画
	m_cRender.DrawIndexPrimitive(m_nIndexCount, 0, 0);

	return;
}