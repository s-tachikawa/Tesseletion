
// �C���N���[�h
#include "../iruna/Include/iruna.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace graphics;


// �{�[�h�Ǘ��N���X
class CSprite
{
private:

	VertexShader*			m_pcVertexShader;			// �o�[�e�N�X�V�F�[�_�[�@�ʏ�`��p
	PixelShader*			m_pcPixcelShader;			// �s�N�Z���V�F�[�_�[	�ʏ�`��p
	VertexDeclaration*		m_pcVertexDec;				// ���_���C�A�E�g

	Texture*				m_pcTex;					// �e�N�X�`���N���X
	VertexBuffer*			m_pcVertexBuffer;			// �o�[�e�N�X�o�b�t�@

	IndexBuffer*			m_pcIndexBuffer;			// �C���f�b�N�X�o�b�t�@
	int						m_nIndexCount;				// �C���f�b�N�X�J�E���g

	float					m_fScal;					// �g��k����
	DeviceController		m_cRender;

public:
	// �R���X�g���N�^
	CSprite();
	// �f�X�g���N�^
	~CSprite();
	// �|���̍쐬
	bool Create();
	// �T�C�Y�̐ݒ�
	void SetScal( float fScal );
	// �e�N�X�`���̐ݒ�
	void SetTexture( Texture* pcTexture );
	// �|���̕`��
	// ������ : �J�����\���̂̃|�C���^
	// ������ : �|���̍��W
	void Draw( Camera pcCamera, math::Vector2 pos );
};
