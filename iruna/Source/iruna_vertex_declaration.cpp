//---------------------------------------------------------
// 
//	iruna_vertex_declaration.h
//	�o�[�e�N�X�f�B�N�����[�V�����̃��b�v
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_vertex_declaration.h"
#include "../Source/iruna_device.h"
#include "../Include/iruna_efect.h"
#include "../Include/iruna_base_shader.h"
#include "../Include/iruna_vertex_shader.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
VertexDeclaration::VertexDeclaration()
	:   element			( NULL ),
		m_pcVertexLayout( NULL )
{
	return;
}

// �R�s�[�R���X�g���N�^
VertexDeclaration::VertexDeclaration( const VertexDeclaration& another )
{
	return;
}

// �f�X�g���N�^
VertexDeclaration::~VertexDeclaration()
{
	Release();

	return;
}

// ���_�錾���쐬����A�����G�������g��˂����񂾏ꍇ�Q�ƃJ�E���g���C���N�������g
bool VertexDeclaration::Create( Element* vertexElement, int nElementCount, ShaderBase* pcShader)
{
	// ���ɍ���Ă��āA�������_�G�������g��������Q�ƃJ�E���g���C���N�������g
	if( m_pcVertexLayout && element == vertexElement )
	{
		m_pcVertexLayout->AddRef();
	}

	// ��������Ȃ��Ă�����Ă�����I��
	if( m_pcVertexLayout )
	{
		return false;
	}

	VertexShader* pcVertexShader = NULL;
	if( pcShader->GetShaderType() != ShaderBase::eVertexShader )
	{
		return false;
	}	
	pcVertexShader = reinterpret_cast< VertexShader* >( pcShader );

	// �G�������g�̃R�s�[
	element	= vertexElement;
	ID3D11Device* pcDevice = Device::GetDevice();

	HRESULT hr = S_OK;
	hr = pcDevice->CreateInputLayout(
			vertexElement,
			nElementCount,
			pcVertexShader->m_pcShaderBlob->GetBufferPointer(),
			pcVertexShader->m_pcShaderBlob->GetBufferSize(),
			&m_pcVertexLayout
		);

	return true;
}

bool VertexDeclaration::Set()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();

	pcDeviceContext->IASetInputLayout( m_pcVertexLayout );
	return true;
}
// ���_�錾���J������A�Q�ƃJ�E���g��0�ɂȂ�����폜����
void VertexDeclaration::Release()
{
	
	if( !m_pcVertexLayout )
	{
		// �f�B�N�����[�V�����f�[�^������ꍇ�͉�����Ȃ�
		return;
	}

	// �Q�ƃJ�E���g��0�Ȃ���
	if( 0 == m_pcVertexLayout->Release() )
	{
		m_pcVertexLayout	= NULL;
		element				= NULL;
	}

	return;
}

}	//	graphics	end
}	//	iruna		end