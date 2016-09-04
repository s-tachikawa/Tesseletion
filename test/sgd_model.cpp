#include "sgd_model.h"

using namespace io;

CSgdModel::CSgdModel()
{
	// モデルの読み込み
	m_pcLoader = new ModelLoader();
	m_pcLoader->Load("../Resource/model/Dragon.sgd");

	modelData = m_pcLoader->GetModelData();
	// モデルに貼り付けるテクスチャの読み込み
	m_pcModelTexture = new Texture();
	m_pcModelTexture->Load("../Resource/texture/alduin.jpg");


	// 各値の初期化
	modelPos = math::Vector3(0.0f, 0, 0);
	modelAngle = math::Vector3(0.0f, 0, 0);
	wold.SetTranslation(modelPos.x, modelPos.y, modelPos.z);

	oldPos.x = 400;
	oldPos.y = 350;
	newPos = oldPos;

	modelScale = 1.0f;
	// ライトの設定
	sLight.x = 0.0f;
	sLight.y = 30.0f;
	sLight.z = 0.0f;

	// 通常描画用のレンダラーを作成
	m_cSimpleShader = new CSimpleModelRender();
	//m_cSimpleShader->CreateConstantBuffer(sizeof(SShaderParam));

	// 法線と深度値を描画するレンダラーを作成
	//m_cNormalDepthShader = new CNormalDepthRender();
	//m_cNormalDepthShader->CreateConstantBuffer(sizeof( SNormalDepthShaderParam ));

	// テッセレート係数
	g_TessFactor[0] = 10.0f;
	g_TessFactor[1] = 10.0f;

	//	コンスタントバッファはバッファを取る最低のバイト数が決まっているみたい
	m_cSimpleShader->CreateHullConstantBuffer(sizeof(float) * 4);
	m_cSimpleShader->CreateDomainConstantBuffer(sizeof(math::Matrix));

	//m_cSimpleShader->CreateConstantBuffer(sizeof(math::Matrix));
	return;
}
CSgdModel::~CSgdModel()
{

}

// モデル更新
void CSgdModel::UpDate()
{
	wold.SetScal(modelScale * -1, modelScale, modelScale);

	//	マウスでのモデル操作
	POINT temp = io::GetMousePosition();
	if (temp.x < 600)
	{
		if (io::CheckMouseState(io::MouseButton::LEFT) == io::INPUT_PUSH ||
			io::CheckMouseState(io::MouseButton::RIGHT) == io::INPUT_PUSH)
			newPos = io::GetMousePosition();

		if (io::CheckMouseState(io::MouseButton::LEFT) == io::INPUT_PUSHED)
		{
			oldPos = io::GetMousePosition();
			modelPos.x = -(oldPos.x - newPos.x) * 0.1f;
			modelPos.y = -(oldPos.y - newPos.y) * 0.1f;
			wold.SetTranslation(modelPos.x, modelPos.y, 0.0f);
		}
		if (io::CheckMouseState(io::MouseButton::RIGHT) == io::INPUT_PUSHED)
		{
			oldPos = io::GetMousePosition();
			modelAngle.y = (oldPos.x - newPos.x) * 0.01f;
			modelAngle.x = (oldPos.y - newPos.y) * 0.01f;
			wold.SetRotation(modelAngle.x, modelAngle.y, 0.0f);
		}
	}

	// キーの処理(0→エッジの分割数、1→ポリゴンの内部分割数)
	if (CheckKeyState(DIK_UP) == INPUT_PUSH)
	{
		g_TessFactor[0] += 1.0f;
	}
	if (CheckKeyState(DIK_DOWN) == INPUT_PUSH)
	{
		g_TessFactor[0] -= 1.0f;
	}
	if (CheckKeyState(DIK_LEFT) == INPUT_PUSH)
	{
		g_TessFactor[1] += 1.0f;
	}
	if (CheckKeyState(DIK_RIGHT) == INPUT_PUSH)
	{
		g_TessFactor[1] -= 1.0f;
	}
	return;
}

//	モデルの描画
void CSgdModel::Draw(Camera spCamera, math::Vector3 pos)
{

	math::WoldMatrix mWorld;
	math::Matrix mWVP;
	mWorld.SetTranslation(pos.x, pos.y, pos.z);
	//mWorld.SetRotation(m_fRot, 0, 0);
	//mWorld.SetScal(10.0f, 10.0f, 10.0f);
	mWVP = mWorld.GetWoldMatrix() * wold.GetWoldMatrix() * spCamera.GetView() * spCamera.GetProjection();
	m_sSimpleParam.m_World = mWorld.GetWoldMatrix() * wold.GetWoldMatrix();
	m_sSimpleParam.m_View = spCamera.GetView();
	m_sSimpleParam.m_Proj = spCamera.GetProjection();

	D3DXMatrixTranspose(&mWVP, &mWVP);

	D3DXMatrixTranspose(&m_sSimpleParam.m_World, &m_sSimpleParam.m_World);
	D3DXMatrixTranspose(&m_sSimpleParam.m_View, &m_sSimpleParam.m_View);
	D3DXMatrixTranspose(&m_sSimpleParam.m_Proj, &m_sSimpleParam.m_Proj);
	
	for (int i = 0; i < (int)modelData->mesh.size(); i++)
	{
		// バーテクスバッファの設定
		modelData->mesh[i]->vertexBuffer[0].IntoStream(0);
		modelData->mesh[i]->vertexBuffer[1].IntoStream(1);
		modelData->mesh[i]->vertexBuffer[2].IntoStream(2);
		//modelData->mesh[i]->vertexBuffer[3].IntoStream(3);
		//modelData->mesh[i]->vertexBuffer[4].IntoStream(4);
		modelData->mesh[i]->indexBuffer->IntoIndices();

		//m_cSimpleShader->SetConstantBuffer(&mWVP);
		m_cSimpleShader->SetDomainConstantBuffer(&mWVP);
		m_cSimpleShader->SetHullConstantBuffer(&g_TessFactor);

		m_cSimpleShader->SetShader();

		// テクスチャの設定
		if (m_pcModelTexture)
			m_cSimpleShader->SetTexture(m_pcModelTexture);

		modelData->mesh[i]->indexBuffer->IntoIndices();
		// ポリゴンの描画
		m_cRender.SetMeshTopology(Primitive::CONTROL_POINT_3);
		// シェーダを設定して描画
		m_cRender.DrawIndexPrimitive(modelData->mesh[i]->countData.indexCount, 0, 0);
	}

	return;
}