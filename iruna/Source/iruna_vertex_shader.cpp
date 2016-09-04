//---------------------------------------------------------
// 
//	iruna_vertex_sheder.cpp
//	�V�F�[�_�[�t�@�C���Ǘ��N���X
//	�쐬�� 6��25��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_vertex_shader.h"
#include "../Include/iruna_vertex_declaration.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
VertexShader::VertexShader()
	:	m_pcVS( NULL ),
		m_pcShaderBlob( NULL )
{
	// �o�[�e�N�X�V�F�[�_
	m_eType = eVertexShader;
	return;
}

//	�f�X�g���N�^
VertexShader::~VertexShader()
{
	if( m_pcVS )
	{
		SafeRelease( m_pcVS );
	}
	if( m_pcShaderBlob )
	{
		SafeRelease( m_pcShaderBlob );
	}
}

//	���_�V�F�[�_�[�̍쐬
bool VertexShader::CreateShader( std::string strShader,std::string strVertexEntry, eShaderVersion eVersion )
{
	// ���_�V�F�[�_�[�̃o�[�W������
	const char* strVertexShaderVersion[] = 
	{
		"vs_1_0",
		"vs_1_1",
		"vs_2_0",
		"vs_3_0",
		"vs_4_0",
		"vs_5_0",
	};
	
	//	�G���[�o�͗p�{���u
	ID3DBlob* pcErrorBlob;
	
	HRESULT hr = S_OK;
	
	hr = D3DX11CompileFromFile(
		strShader.c_str(),							//	�V�F�[�_�[�t�@�C�����@�V�F�[�_��hlsl,fx�t�@�C����2���
		NULL,										//	�V�F�[�_�[���Ń}�N�����g�p����Ƃ��Ɏg�p
		NULL,										//	�C���N���[�h�t�@�C�����g�p�ł��邽�߂̃t���O
		strVertexEntry.c_str(),						//	���_�V�F�[�_�[�����s����G���g���[�|�C���g�̊֐���
		strVertexShaderVersion[ eVersion ],			//	�V�F�[�_�[���f��
		0,											//	�V�F�[�_�[�̃R���p�C���o�[�W����HLSL�t�@�C��
		0,											//	�V�F�[�_�[�̃R���p�C���o�[�W����FX�t�@�C��
		NULL,
		&m_pcShaderBlob,
		&pcErrorBlob,
		NULL
		);

	// �V�F�[�_�[�ǂݍ��ݎ��s
	if( FAILED( hr ) )
	{
		if( pcErrorBlob != NULL )
		{
			// �G���[���b�Z�[�W�o��
			OutputDebugStringA( (char*)pcErrorBlob->GetBufferPointer() );
		}
	}
	// �G���[�o�͗p�̃{���u���J������
	if( pcErrorBlob )
	{
		SafeRelease(pcErrorBlob);
	}
	//	���_�V�F�[�_�[�̍쐬
	ID3D11Device* pcDevice = Device::GetDevice();
	hr = pcDevice->CreateVertexShader( 
				m_pcShaderBlob->GetBufferPointer(),
				m_pcShaderBlob->GetBufferSize(),
				NULL,
				&m_pcVS
				);

	// ���_�V�F�[�_�[�̍쐬�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}
	return true;
}
//	�o�[�e�N�X�V�F�[�_�[�ɃR���X�^���g�o�b�t�@��ݒ�
bool VertexShader::CreateConstantBuffer( int nBufferSize )
{
	ID3D11Device* pcDevice					= Device::GetDevice();
	ID3D11DeviceContext* pcDeviceContext	= Device::GetDeviceContext();
	
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC			m_cBufferDesc;		//!< ���_�o�b�t�@�ݒ���(cbuffer�ݒ�pbufferDesc)

	//	�R���X�^���g�o�b�t�@�̐ݒ�
	m_cBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;				// �R���X�^���g�o�b�t�@�𓮓I�ɏ����������\�ɂ���t���O
	m_cBufferDesc.ByteWidth			= nBufferSize;						// �R���X�^���g�o�b�t�@�̃T�C�Y
	m_cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;		// �R���X�^���g�o�b�t�@�p�Ƀo�b�t�@���o�C���h�����邽�߂̃t���O
	m_cBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;			// �R���X�^���g�o�b�t�@��CPU����A�N�Z�X�ł���悤�ɂ��邩�ǂ���
	m_cBufferDesc.MiscFlags			= 0;

	//	�R���X�^���g�o�b�t�@�̍쐬
	hr = pcDevice->CreateBuffer( &m_cBufferDesc,NULL, &m_pcConstantBuffer );

	// �R���X�^���g�o�b�t�@�쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}

	return false;
}

//	���_�V�F�[�_�[�ɃR���X�^���g�o�b�t�@���Z�b�g
bool VertexShader::SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	HRESULT hr = S_OK;
	
	// �R���X�^���g�o�b�t�@���쐬����Ă��Ȃ�
	if( !m_pcConstantBuffer )
	{
		return true;
	}

	D3D11_MAPPED_SUBRESOURCE	m_cMappedResource;	//!< ���_�V�F�[�_�[
	// �R���X�^���g�o�b�t�@�ɏ������߂�悤�ɐݒ�
	hr = pcDeviceContext->Map( 
		m_pcConstantBuffer,			//	�f�[�^���������ݗp�o�b�t�@
		NULL,						
		D3D11_MAP_WRITE_DISCARD,	//�@�������߂�悤�Ƀt���O��ݒ�
		NULL,
		&m_cMappedResource			//�@�f�[�^���}�b�v�����邽�߂̃o�b�t�@
		);

	//	 �R���X�^���g�o�b�t�@�̃}�b�v�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}

	CopyMemory( m_cMappedResource.pData, pData, nBufferSize );
	
	pcDeviceContext->UpdateSubresource(m_pcConstantBuffer, 0, 0, pData, 0, 0);

	// �������݋֎~�ɐݒ�
	pcDeviceContext->Unmap( m_pcConstantBuffer, NULL );
	
	pcDeviceContext->VSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return false;
}

//	���_�V�F�[�_�[�Ƀe�N�X�`�����Z�b�g
bool VertexShader::SetTexture( Texture* pcTex, int nNum )
{
	// �e�N�X�`�����Ȃ�
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->VSSetSamplers(nNum, 1, &pcSamplerState);
	pcDeviceContext->VSSetShaderResources(nNum, 1, &pcShederResource);

	return true;
}

//	�쐬�ł����V�F�[�_�[���f�o�C�X�R���e�L�X�g�ɐݒ�
bool VertexShader::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();

	// ���_�V�F�[�_�[
	if( m_pcVS )
	{
		pcDeviceContext->VSSetShader( m_pcVS, NULL, 0 );
	}	
	return true;
}

}	//	graphics	end
}	//	iruna		end