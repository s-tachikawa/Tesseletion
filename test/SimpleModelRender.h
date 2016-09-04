// �C���N���[�h
#include "../iruna/Include/iruna.h"

// �l�[���X�y�[�X
using namespace iruna;
using namespace graphics;


// �{�[�h�Ǘ��N���X
class CSimpleModelRender
{
private:

	VertexShader*			m_cSimpleVertexShader;			// ���f���`��p���_�V�F�[�_�[
	PixelShader*			m_cSimplePixcelShader;			// ���f���`��p�s�N�Z�����_�V�F�[�_�[
	HullShader*				m_cSimpleHullShader;			// ���f���`��p�n���V�F�[�_�[
	DomainShader*			m_cSimpleDomainShader;			//�@���f���`��p�h���C���V�F�[�_�[
	VertexDeclaration*		m_cVertexDec;					// ���_�t�H�[�}�b�g

	int						m_nCBufferSize;					// �R���X�^���g�o�b�t�@�̃T�C�Y�@Vertex
	int						m_nHullCBufferSize;				// �R���X�^���g�o�b�t�@�̃T�C�Y�@Hull
	int						m_nDomainCBufferSize;			// �R���X�^���g�o�b�t�@�̃T�C�Y�@Domain

public:
	// �R���X�g���N�^
	CSimpleModelRender();
	// �f�X�g���N�^
	~CSimpleModelRender();

	// �R���X�^���g�o�b�t�@�̍쐬(�o�[�e�N�X)
	void CreateConstantBuffer( int nSize );
	// �R���X�^���g�o�b�t�@�̍쐬(�n���V�F�[�_�[)
	void CreateHullConstantBuffer(int nSize);
	// �R���X�^���g�o�b�t�@�̍쐬(�h���C���V�F�[�_�[)
	void CreateDomainConstantBuffer(int nSize);

	// �e�N�X�`���̐ݒ�
	void SetTexture( Texture* tex );
	// �R���X�^���g�o�b�t�@�̐ݒ�
	void SetConstantBuffer( void* pcBuffer );
	// �R���X�^���g�o�b�t�@�̐ݒ�(�n���V�F�[�_�[)
	void SetHullConstantBuffer(void* pcBuffer);
	// �R���X�^���g�o�b�t�@�̐ݒ�(�h���C���V�F�[�_�[)
	void SetDomainConstantBuffer(void* pcBuffer);
	// �o�b�t�@�̍X�V
	void UpDateConstantBuffer();

	// �V�F�[�_�[�̐ݒ�
	void SetShader();
};