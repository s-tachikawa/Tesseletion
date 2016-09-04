
// �C���N���[�h
#include "../iruna/Include/iruna.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace	graphics;
using namespace core;
using namespace sound;
using namespace physics;
using namespace io;

// �{�b�N�X�N���X�̍쐬�ƊǗ�
class CBox
{
private:

	VertexShader*			m_pcShadowVertex;			// �o�[�e�N�X�V�F�[�_�[�@�[�x�}�b�v�`��p
	PixelShader*			m_pcShadowPixcel;			// �s�N�Z���V�F�[�_�[	�[�x�}�b�v�`��p
	VertexDeclaration*		m_pcShadowDec;				// ���_���C�A�E�g		�[�x�}�b�v�`��p

	VertexDeclaration*	m_pcLayout;				// ���_���C�A�E�g
	VertexBuffer*		m_pcVertexBuffer;		// ���_�o�b�t�@

	IndexBuffer*		m_pcIndexBuffer;		// �C���f�b�N�X�o�b�t�@
	int					m_nIndexCount;			// �C���f�b�N�X�J�E���g

	VertexShader*		m_pcVertexShader;		// �o�[�e�N�X�V�F�[�_�[
	PixelShader*		m_pcPixcelShader;		// �s�N�Z���V�F�[�_�[
	Texture*			m_pcTexture;			// �e�N�X�`��

	DeviceController	m_cRender;				// �f�o�C�X�R���e�L�X�g

	float				m_fRot;

public:
	// �R���X�g���N�^
	CBox();
	// �f�X�g���N�^
	~CBox();
	// �{�b�N�X�̍쐬
	bool Create();
	// �{�b�N�X�̈ʒu���w��
	// ������ vRot :  �{�b�N�X�̉�]
	void SetRotation( math::Vector3 vRot );
	// �V���h�E�}�b�v�̕`��
	void DrawShadowMap( Camera spLightCamera, math::Vector3 vPos );
	// �{�b�N�X�̕`��
	// ������ vPos : �`�悷��ʒu
	// ������ sCamera : �ʂ��J�����\���̂̃|�C���^
	void Draw( Camera psCamera,  math::Vector3 vPos );
};