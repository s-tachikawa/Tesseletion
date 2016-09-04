// �C���N���[�h
#include "../iruna/Include/iruna.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace graphics;


// �{�[�h�Ǘ��N���X
class CHDAORender
{
private:

	VertexShader*			m_cSimpleVertexShader;			// ���f���`��p���_�V�F�[�_�[
	PixelShader*			m_cSimplePixcelShader;			// ���f���`��p�s�N�Z�����_�V�F�[�_�[
	VertexDeclaration*		m_cVertexDec;					// ���_�t�H�[�}�b�g

	int						m_nCBufferSize;					// �R���X�^���g�o�b�t�@�̃T�C�Y

public:
	// �R���X�g���N�^
	CHDAORender();
	// �f�X�g���N�^
	~CHDAORender();

	// �R���X�^���g�o�b�t�@�̍쐬
	void CreateConstantBuffer(int nSize);

	void CreatePixcelConstantBuffer( int nSize );

	// �e�N�X�`���̐ݒ�
	void SetTexture(int nNum, Texture* tex);
	// �R���X�^���g�o�b�t�@�̐ݒ�
	void SetConstantBuffer(void* pcBuffer);

	void SetPixcelConstantBuffer(void* pcBuffer);
	// �o�b�t�@�̍X�V
	void UpDateConstantBuffer();

	// �V�F�[�_�[�̐ݒ�
	void SetShader();
};