// �C���N���[�h
#include "../iruna/Include/iruna.h"
#include "SimpleModelRender.h"
#include "NormalDepthRender.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace graphics;

// �o�[�e�N�X�V�F�[�_�[�ɓn���p�����[�^�[(SimpleModelRender.hlsl�p)
struct SShaderParam
{
	math::Matrix m_World;
	math::Matrix m_View;
	math::Matrix m_Proj;

};

// �o�[�e�N�X�V�F�[�_�[�ɓn���p�����[�^�[(NormalDepth.hlsl�p)
struct SNormalDepthShaderParam
{
	math::Matrix m_World;
	math::Matrix m_View;
	math::Matrix m_Proj;
	math::Matrix m_WorldInv;
};

// �{�[�h�Ǘ��N���X
class CSgdModel
{
private:


	ModelData*			modelData;						//	�����_�����O���f���f�[�^
	ModelLoader*		m_pcLoader;						// ���f�����[�_�[
		
	Texture*			m_pcModelTexture;				//	�e�N�X�`��

	float				animeFlame;						//	�A�j���[�V�����t���[��

	Camera				camera;							//	�J����
	
	float				cameraUp;						//	�J�����g�嗦
	float				cameraAngle;					//	�J�����̊p�x

	math::Vector3		modelPos;		//	���f���̍��W
	math::Vector3		modelAngle;		//	���f���̊p�x
	float				modelScale;		//	���f���̃X�P�[��

	POINT				oldPos;			//	���f���̉ߋ����W
	POINT				newPos;			//	���f���̌��ݍ��W
	math::WoldMatrix	wold;			//	���[���h�s��N���X


	math::Vector3 sLight;				// ���C�g

	CSimpleModelRender*			m_cSimpleShader;
	SShaderParam				m_sSimpleParam;
		
	CNormalDepthRender*			m_cNormalDepthShader;
	SNormalDepthShaderParam		m_sNormalDepthParam;

	DeviceController		m_cRender;

	float	g_TessFactor[2];

public:
	// �R���X�g���N�^
	CSgdModel();
	// �f�X�g���N�^
	~CSgdModel();

	void UpDate();

	// �|���̕`��
	// ������ : �J�����\���̂̃|�C���^
	// ������ : �|���̍��W
	void Draw(Camera spCamera, math::Vector3 pos);

	void NormalDepthRender(Camera spCamera, math::Vector3 pos);
};
