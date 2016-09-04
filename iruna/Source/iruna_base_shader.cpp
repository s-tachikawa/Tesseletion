//---------------------------------------------------------
// 
//	iruna_base_shader.cpp
//	�V�F�[�_�[�t�@�C���Ǘ��N���X�̃x�[�X
//	�쐬�� 1��14��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_pixel_shader.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
ShaderBase::ShaderBase()
:	m_pcConstantBuffer( NULL )
{
}

// �f�X�g���N�^
ShaderBase::~ShaderBase()
{
	if( m_pcConstantBuffer )
	{
		SafeRelease( m_pcConstantBuffer );
	}
}

// �V�F�[�_�[�^�C�v���擾����
ShaderBase::eCreateShaderType ShaderBase::GetShaderType()
{
	return m_eType;
}

}
}
