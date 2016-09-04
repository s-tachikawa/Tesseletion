

// �C���N���[�h
#include "../iruna/Include/iruna.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace graphics;


// �����_�����O�̊Ǘ��N���X
class RenderManager
{
public:
	enum ERenderStep
	{
		eShadowMap,			// �V���h�E�}�b�v
		eRGBA,				// �ʏ�`��(RGB)
		eRenderStepMax
	};

private:

public:
	// �R���X�g���N�^
	RenderManager();
	// �f�X�g���N�^
	~RenderManager();
	// ������
	bool Init();
	//�@�`�悷�郁�b�V����o�^����
	void SetDrawMesh();
	//�@�����_�����O�X�e�b�v�̐ݒ�
	void SetRenderStep( ERenderStep eStep );
};