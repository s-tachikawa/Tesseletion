//---------------------------------------------------------
// 
//	iruna_hull_sheder.cpp
//	�V�F�[�_�[�t�@�C���Ǘ��N���X
//	�쐬�� 1��14��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_hull_shader.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
HullShader::HullShader()
	:	m_pcHULL( NULL )
{
	m_eType = eHULLShader;
	return;
}

//	�f�X�g���N�^
HullShader::~HullShader()
{
	if( m_pcHULL )
	{
		SafeRelease( m_pcHULL );
	}
}

//	�s�N�Z���V�F�[�_�[�̍쐬
bool HullShader::CreateShader( std::string strShader,std::string strHullEntry, eShaderVersion eVersion )
{
	// �s�N�Z���V�F�[�_�[�̃o�[�W������
	const char* strHullShaderVersion[] = 
	{
		"hs_1_0",
		"hs_1_1",
		"hs_2_0",
		"hs_3_0",
		"hs_4_0",
		"hs_5_0",
	};

	//	�G���[�o�͗p�{���u
	ID3DBlob* pcErrorBlob;
	ID3DBlob* pcShaderBlob;
	HRESULT hr = S_OK;

	//	�V�F�[�_�[�t�@�C����ǂݍ���ŃR���p�C��
	hr = D3DX11CompileFromFile(
		strShader.c_str(),						//	�V�F�[�_�[�t�@�C�����@�V�F�[�_��hlsl,fx�t�@�C����2���
		NULL,									//	�V�F�[�_�[���Ń}�N�����g�p����Ƃ��Ɏg�p
		NULL,									//	�C���N���[�h�t�@�C�����g�p�ł��邽�߂̃t���O
		strHullEntry.c_str(),					//	�V�F�[�_�[�����s����G���g���[�|�C���g�̊֐���
		strHullShaderVersion[ eVersion ],		//	�V�F�[�_�[���f��
		0,										//	�V�F�[�_�[�̃R���p�C���o�[�W����HLSL�t�@�C��
		0,										//	�V�F�[�_�[�̃R���p�C���o�[�W����FX�t�@�C��
		NULL,
		&pcShaderBlob,
		&pcErrorBlob,
		NULL
		);

	// �V�F�[�_�[�쐬���s
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

	//	�n���V�F�[�_�[���쐬
	ID3D11Device* pcDevice = Device::GetDevice();
	hr = pcDevice->CreateHullShader(
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcHULL
		);
	// �n���V�F�[�_�[�쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}
//	�s�N�Z���V�F�[�_�[�ɃR���X�^���g�o�b�t�@��ݒ�
bool HullShader::CreateConstantBuffer( int nBufferSize )
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
bool HullShader::SetConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
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

	// �������݋֎~�ɐݒ�
	pcDeviceContext->Unmap( m_pcConstantBuffer, NULL );

	pcDeviceContext->HSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return false;
}

//	���_�V�F�[�_�[�Ƀe�N�X�`�����Z�b�g
bool HullShader::SetTexture( Texture* pcTex, int nNum )
{
	// �e�N�X�`�����Ȃ�
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->HSSetSamplers( 0, 1, &pcSamplerState );
	pcDeviceContext->HSSetShaderResources( 0, 1, &pcShederResource );

	return true;
}

//	�쐬�ł����V�F�[�_�[���f�o�C�X�R���e�L�X�g�ɐݒ�
bool HullShader::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	if( m_pcHULL )
	{
		pcDeviceContext->HSSetShader( m_pcHULL, NULL, 0 );
	}	
	return true;
}

}	//	graphics	end
}	//	iruna		end