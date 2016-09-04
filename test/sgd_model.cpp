#include "sgd_model.h"

using namespace io;

CSgdModel::CSgdModel()
{
	// ���f���̓ǂݍ���
	m_pcLoader = new ModelLoader();
	m_pcLoader->Load("../Resource/model/Dragon.sgd");

	modelData = m_pcLoader->GetModelData();
	// ���f���ɓ\��t����e�N�X�`���̓ǂݍ���
	m_pcModelTexture = new Texture();
	m_pcModelTexture->Load("../Resource/texture/alduin.jpg");


	// �e�l�̏�����
	modelPos = math::Vector3(0.0f, 0, 0);
	modelAngle = math::Vector3(0.0f, 0, 0);
	wold.SetTranslation(modelPos.x, modelPos.y, modelPos.z);

	oldPos.x = 400;
	oldPos.y = 350;
	newPos = oldPos;

	modelScale = 1.0f;
	// ���C�g�̐ݒ�
	sLight.x = 0.0f;
	sLight.y = 30.0f;
	sLight.z = 0.0f;

	// �ʏ�`��p�̃����_���[���쐬
	m_cSimpleShader = new CSimpleModelRender();
	//m_cSimpleShader->CreateConstantBuffer(sizeof(SShaderParam));

	// �@���Ɛ[�x�l��`�悷�郌���_���[���쐬
	//m_cNormalDepthShader = new CNormalDepthRender();
	//m_cNormalDepthShader->CreateConstantBuffer(sizeof( SNormalDepthShaderParam ));

	// �e�b�Z���[�g�W��
	g_TessFactor[0] = 10.0f;
	g_TessFactor[1] = 10.0f;

	//	�R���X�^���g�o�b�t�@�̓o�b�t�@�����Œ�̃o�C�g�������܂��Ă���݂���
	m_cSimpleShader->CreateHullConstantBuffer(sizeof(float) * 4);
	m_cSimpleShader->CreateDomainConstantBuffer(sizeof(math::Matrix));

	//m_cSimpleShader->CreateConstantBuffer(sizeof(math::Matrix));
	return;
}
CSgdModel::~CSgdModel()
{

}

// ���f���X�V
void CSgdModel::UpDate()
{
	wold.SetScal(modelScale * -1, modelScale, modelScale);

	//	�}�E�X�ł̃��f������
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

	// �L�[�̏���(0���G�b�W�̕������A1���|���S���̓���������)
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

//	���f���̕`��
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
		// �o�[�e�N�X�o�b�t�@�̐ݒ�
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

		// �e�N�X�`���̐ݒ�
		if (m_pcModelTexture)
			m_cSimpleShader->SetTexture(m_pcModelTexture);

		modelData->mesh[i]->indexBuffer->IntoIndices();
		// �|���S���̕`��
		m_cRender.SetMeshTopology(Primitive::CONTROL_POINT_3);
		// �V�F�[�_��ݒ肵�ĕ`��
		m_cRender.DrawIndexPrimitive(modelData->mesh[i]->countData.indexCount, 0, 0);
	}

	return;
}