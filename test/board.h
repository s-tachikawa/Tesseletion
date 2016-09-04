
// �C���N���[�h
#include "../iruna/Include/iruna.h"
#include "HdaoRender.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace graphics;

// �o�[�e�N�X�V�F�[�_�[�ɓn���p�����[�^�[(NormalDepth.hlsl�p)
struct SHDAOParam
{
	math::Vector4	g_ScreenParam;		// (width, height, 1.0/width, 1.0/height)
	math::Vector4	g_ProjParam;		// (near, far, tan(fovy), aspect)
	float			g_CheckRadius;
	float			g_RejectDepth;
	float			g_AcceptDepth;
	float			g_Intensity;
	float			g_AcceptAngle;
	int				g_UseNormal;
	float			g_NormalScale;
	float			g_Offset;
};

// �o�[�e�N�X�V�F�[�_�[�ɓn���p�����[�^�[(NormalDepth.hlsl�p)
struct STestParam
{
	math::Vector4	g_ScreenParam;		// (width, height, 1.0/width, 1.0/height)
	math::Vector4	g_ProjParam;		// (near, far, tan(fovy), aspect)
	float	g_CheckRadius;
	float			g_RejectDepth;
	float			g_AcceptDepth;
	float			g_Intensity;
	float			g_AcceptAngle;
	float				g_UseNormal;
	float			g_NormalScale;
	float			g_Offset;
};
// �{�[�h�Ǘ��N���X
class CBoard
{
private:
	
	VertexShader*			m_pcVertexShader;			// �o�[�e�N�X�V�F�[�_�[�@�ʏ�`��p
	PixelShader*			m_pcPixcelShader;			// �s�N�Z���V�F�[�_�[	�ʏ�`��p
	VertexDeclaration*		m_pcVertexDec;				// ���_���C�A�E�g

	VertexShader*			m_pcShadowVertex;			// �o�[�e�N�X�V�F�[�_�[�@�[�x�}�b�v�`��p
	PixelShader*			m_pcShadowPixcel;			// �s�N�Z���V�F�[�_�[	�[�x�}�b�v�`��p
	VertexDeclaration*		m_pcShadowDec;				// ���_���C�A�E�g		�[�x�}�b�v�`��p

	Texture*				m_pcTex;					// �e�N�X�`���N���X
	VertexBuffer*			m_pcVertexBuffer;			// �o�[�e�N�X�o�b�t�@
	
	IndexBuffer*			m_pcIndexBuffer;			// �C���f�b�N�X�o�b�t�@
	int						m_nIndexCount;				// �C���f�b�N�X�J�E���g

	float					m_fRot;						// ��]
	float					m_fScal;					// �g��k����
	DeviceController		m_cRender;

	CHDAORender*			m_cHdaoRender;				// HDAO�`��p�����_���[
	SHDAOParam				m_cHDAOPram;


	// Todo: Test �Ƃ肠�����e�X�g s_tachikawa
	STestParam m_cTestShaderPrama;


public:
	// �R���X�g���N�^
	CBoard();
	// �f�X�g���N�^
	~CBoard();
	// �|���̍쐬
	bool Create();
	// X����]�̐ݒ�
	void SetRotation( float fRot );
	// ��]�̐ݒ�
	void SetScal( float fScal );
	// �e�N�X�`���̐ݒ�
	void SetTexture( Texture* pcTexture );
	// �V���h�E�}�b�v�̕`��
	// ������ : ���C�g�J�����̃|�C���^
	void DrawShadowMap( Camera spLightCamera, math::Vector3 pos );
	// �|���̕`��
	// ������ : �J�����\���̂̃|�C���^
	// ������ : �|���̍��W
	void Draw(Camera spCamera, math::Vector3 pos, Texture* pcHDAO, Texture* pcDecal);

	// HDAO�̕`��
	void HDAORender(Camera spCamera, math::Vector3 pos, Texture* pcNormalDepth);

};
