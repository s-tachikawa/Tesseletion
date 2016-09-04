//---------------------------------------------------------
// 
//	iruna_efect.cpp
//	�V�F�[�_�[�t�@�C���Ǘ��N���X
//	�쐬�� 6��25��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_efect.h"
#include "../Source/iruna_device.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_vertex_declaration.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
Effect::Effect()
	:	m_pcVS( NULL ),
		m_pcVertexBlob( NULL ),
		m_pcConstantBuffer( NULL ),
		m_pcGS( NULL ),
		m_pcPS( NULL ),
		m_pcHull( NULL ),
		m_pcDomain( NULL ),
		m_pcDomainBlob( NULL ),
		m_pcDomainConstantBuffer( NULL )
{
	return;
}

//	�f�X�g���N�^
Effect::~Effect()
{
	if( m_pcVS )
	{
		SafeRelease( m_pcVS );
	}
	if( m_pcGS )
	{
		SafeRelease( m_pcGS );
	}
	if( m_pcPS )
	{
		SafeRelease( m_pcPS );
	}
	if( m_pcConstantBuffer )
	{
		SafeRelease( m_pcConstantBuffer );
	}
	if( m_pcDomain )
	{
		SafeRelease( m_pcDomain );
	}
	if( m_pcHull )
	{
		SafeRelease( m_pcHull );
	}
	if( m_pcDomainBlob )
	{
		SafeRelease( m_pcDomainBlob );
	}
	if( m_pcDomainConstantBuffer )
	{
		SafeRelease( m_pcDomainConstantBuffer );
	}
}

//	���_�V�F�[�_�[�̍쐬
bool Effect::CreateVertexShader( std::string strShader,std::string strVertexEntry, eShaderVersion eVersion )
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
		&m_pcVertexBlob,
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
				m_pcVertexBlob->GetBufferPointer(),
				m_pcVertexBlob->GetBufferSize(),
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
bool Effect::CreateVertexConstantBuffer( int nBufferSize )
{
	ID3D11Device* pcDevice					= Device::GetDevice();
	ID3D11DeviceContext* pcDeviceContext	= Device::GetDeviceContext();
	
	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC			m_cBufferDesc;		//!< ���_�o�b�t�@�ݒ���(cbuffer�ݒ�pbufferDesc)

	//	�R���X�^���g�o�b�t�@�̐ݒ�
	m_cBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;						// �R���X�^���g�o�b�t�@�𓮓I�ɏ����������\�ɂ���t���O
	m_cBufferDesc.ByteWidth			= nBufferSize;							// �R���X�^���g�o�b�t�@�̃T�C�Y
	m_cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;			// �R���X�^���g�o�b�t�@�p�Ƀo�b�t�@���o�C���h�����邽�߂̃t���O
	m_cBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;			// �R���X�^���g�o�b�t�@��CPU����A�N�Z�X�ł���悤�ɂ��邩�ǂ���
	m_cBufferDesc.MiscFlags			= 0;

	//	�R���X�^���g�o�b�t�@�̍쐬
	hr = pcDevice->CreateBuffer( &m_cBufferDesc,NULL, &m_pcConstantBuffer );

	// �R���X�^���g�o�b�t�@�쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}

//	���_�V�F�[�_�[�ɃR���X�^���g�o�b�t�@���Z�b�g
bool Effect::SetVertexConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
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

	pcDeviceContext->VSSetConstantBuffers( nRegisterNum, 1, &m_pcConstantBuffer );

	return true;
}
//	�s�N�Z���V�F�[�_�[�̍쐬
bool Effect::CreatePixelShader( std::string strShader,std::string strPixelEntry, eShaderVersion eVersion )
{
	// ���_�V�F�[�_�[�̃o�[�W������
	const char* strVertexShaderVersion[] = 
	{
		"ps_1_0",
		"ps_1_1",
		"ps_2_0",
		"ps_3_0",
		"ps_4_0",
		"ps_5_0",
	};

	//	�G���[�o�͗p�{���u
	ID3DBlob* pcErrorBlob;

	HRESULT hr = S_OK;

	ID3DBlob* pcShaderBlob = NULL;

	//	�V�F�[�_�[�t�@�C����ǂݍ���ŃR���p�C��
	hr = D3DX11CompileFromFile(
		strShader.c_str(),							//	�V�F�[�_�[�t�@�C�����@�V�F�[�_��hlsl,fx�t�@�C����2���
		NULL,									//	�V�F�[�_�[���Ń}�N�����g�p����Ƃ��Ɏg�p
		NULL,									//	�C���N���[�h�t�@�C�����g�p�ł��邽�߂̃t���O
		strPixelEntry.c_str(),							//	�s�N�Z���V�F�[�_�[�����s����G���g���[�|�C���g�̊֐���
		strVertexShaderVersion[ eVersion ],		//	�V�F�[�_�[���f��
		0,			//	�V�F�[�_�[�̃R���p�C���o�[�W����HLSL�t�@�C��
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

	// �s�N�Z���V�F�[�_�[���쐬
	ID3D11Device* pcDevice = Device::GetDevice();
	hr = pcDevice->CreatePixelShader(
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcPS
		);
	// �s�N�Z���V�F�[�_�[�쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}
	//	�s�N�Z���V�F�[�_�[�쐬����
	pcShaderBlob->Release();
	pcShaderBlob = NULL;

	return true;
}
//	�s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����Z�b�g
bool Effect::SetTexture( Texture* pcTex )
{
	// �e�N�X�`�����Ȃ�
	if( !pcTex )
	{
		return false;
	}
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	ID3D11SamplerState* pcSamplerState = pcTex->GetSamplerState();
	ID3D11ShaderResourceView* pcShederResource = pcTex->GetTexture();
	pcDeviceContext->PSSetSamplers( 0, 1, &pcSamplerState );
	pcDeviceContext->PSSetShaderResources( 0, 1, &pcShederResource );

	return true;
}
//	�W�I���g���[�V�F�[�_�[�쐬
bool Effect::CreateGeometryShader( std::string strShader,std::string strGeometryEntry, eShaderVersion eVersion )
{
	// ���_�V�F�[�_�[�̃o�[�W������
	const char* strVertexShaderVersion[] = 
	{
		"gs_1_0",
		"gs_1_1",
		"gs_2_0",
		"gs_3_0",
		"gs_4_0",
		"gs_5_0",
	};

	//	�G���[�o�͗p�{���u
	ID3DBlob* pcErrorBlob;

	HRESULT hr = S_OK;

	ID3DBlob* pcShaderBlob = NULL;

	hr = D3DX11CompileFromFile(
		strShader.c_str(),							//	�V�F�[�_�[�t�@�C�����@�V�F�[�_��hlsl,fx�t�@�C����2���
		NULL,									//	�V�F�[�_�[���Ń}�N�����g�p����Ƃ��Ɏg�p
		NULL,									//	�C���N���[�h�t�@�C�����g�p�ł��邽�߂̃t���O
		strGeometryEntry.c_str(),							//	�W�I���g���V�F�[�_�[�����s����G���g���[�|�C���g�̊֐���
		strVertexShaderVersion[ eVersion ],		//	�V�F�[�_�[���f��
		D3DCOMPILE_ENABLE_STRICTNESS,			//	�V�F�[�_�[�̃R���p�C���o�[�W����HLSL�t�@�C��
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

	//	�W�I���g���[�V�F�[�_�[�쐬
	ID3D11Device* pcDevice = Device::GetDevice();

	pcDevice->CreateGeometryShader( 
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcGS
		);

	//	�W�I���g���V�F�[�_�[�쐬����
	pcShaderBlob->Release();
	pcShaderBlob = NULL;

	return true;
}

//	�n���V�F�[�_�[�̍쐬
bool Effect::CreateHullShader( std::string path, std::string strHullEntry, eShaderVersion eVersion )
{
	// �n���V�F�[�_�[�̃o�[�W������
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

	HRESULT hr = S_OK;

	ID3DBlob* pcShaderBlob = NULL;

	hr = D3DX11CompileFromFile(
		path.c_str(),							//	�V�F�[�_�[�t�@�C�����@�V�F�[�_��hlsl,fx�t�@�C����2���
		NULL,									//	�V�F�[�_�[���Ń}�N�����g�p����Ƃ��Ɏg�p
		NULL,									//	�C���N���[�h�t�@�C�����g�p�ł��邽�߂̃t���O
		strHullEntry.c_str(),					//	�W�I���g���V�F�[�_�[�����s����G���g���[�|�C���g�̊֐���
		strHullShaderVersion[ eVersion ],		//	�V�F�[�_�[���f��
		D3DCOMPILE_ENABLE_STRICTNESS,			//	�V�F�[�_�[�̃R���p�C���o�[�W����HLSL�t�@�C��
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

	//	�W�I���g���[�V�F�[�_�[�쐬
	ID3D11Device* pcDevice = Device::GetDevice();

	pcDevice->CreateHullShader( 
		pcShaderBlob->GetBufferPointer(),
		pcShaderBlob->GetBufferSize(),
		NULL,
		&m_pcHull
		);

	//	�W�I���g���V�F�[�_�[�쐬����
	pcShaderBlob->Release();
	pcShaderBlob = NULL;
	return true;
}

//	�h���C���V�F�[�_�[�̍쐬
bool Effect::CreateDomainShader( std::string path, std::string strDomainEntry, eShaderVersion eVersion )
{
	// �n���V�F�[�_�[�̃o�[�W������
	const char* strDomainShaderVersion[] = 
	{
		"ds_1_0",
		"ds_1_1",
		"ds_2_0",
		"ds_3_0",
		"ds_4_0",
		"ds_5_0",
	};

	//	�G���[�o�͗p�{���u
	ID3DBlob* pcErrorBlob;

	HRESULT hr = S_OK;

	hr = D3DX11CompileFromFile(
		path.c_str(),							//	�V�F�[�_�[�t�@�C�����@�V�F�[�_��hlsl,fx�t�@�C����2���
		NULL,									//	�V�F�[�_�[���Ń}�N�����g�p����Ƃ��Ɏg�p
		NULL,									//	�C���N���[�h�t�@�C�����g�p�ł��邽�߂̃t���O
		strDomainEntry.c_str(),					//	�V�F�[�_�[�����s����G���g���[�|�C���g�̊֐���
		strDomainShaderVersion[ eVersion ],		//	�V�F�[�_�[���f��
		D3DCOMPILE_ENABLE_STRICTNESS,			//	�V�F�[�_�[�̃R���p�C���o�[�W����HLSL�t�@�C��
		0,										//	�V�F�[�_�[�̃R���p�C���o�[�W����FX�t�@�C��
		NULL,
		&m_pcDomainBlob,
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

	//	�W�I���g���[�V�F�[�_�[�쐬
	ID3D11Device* pcDevice = Device::GetDevice();

	pcDevice->CreateDomainShader( 
		m_pcDomainBlob->GetBufferPointer(),
		m_pcDomainBlob->GetBufferSize(),
		NULL,
		&m_pcDomain
		);

	return true;
}

//	�h���C���V�F�[�_�[�p�R���X�^���g�o�b�t�@���쐬
bool Effect::CreateDomainConstantBuffer( int nBufferSize )
{
	ID3D11Device* pcDevice					= Device::GetDevice();
	ID3D11DeviceContext* pcDeviceContext	= Device::GetDeviceContext();

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC			m_cBufferDesc;		//!< ���_�o�b�t�@�ݒ���(cbuffer�ݒ�pbufferDesc)

	//	�R���X�^���g�o�b�t�@�̐ݒ�
	m_cBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;					// �R���X�^���g�o�b�t�@�𓮓I�ɏ����������\�ɂ���t���O
	m_cBufferDesc.ByteWidth			= nBufferSize;							// �R���X�^���g�o�b�t�@�̃T�C�Y
	m_cBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;			// �R���X�^���g�o�b�t�@�p�Ƀo�b�t�@���o�C���h�����邽�߂̃t���O
	m_cBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;				// �R���X�^���g�o�b�t�@��CPU����A�N�Z�X�ł���悤�ɂ��邩�ǂ���
	m_cBufferDesc.MiscFlags			= 0;

	//	�R���X�^���g�o�b�t�@�̍쐬
	hr = pcDevice->CreateBuffer( &m_cBufferDesc,NULL, &m_pcDomainConstantBuffer );

	// �R���X�^���g�o�b�t�@�쐬���s
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}

//	�h���C���V�F�[�_�[�p�R���X�^���g�o�b�t�@�ɕϐ���ݒ�
bool Effect::SetDomainConstantBuffer( void* pData, int nRegisterNum, int nBufferSize )
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	HRESULT hr = S_OK;

	// �R���X�^���g�o�b�t�@���쐬����Ă��Ȃ�
	if( !m_pcDomainConstantBuffer )
	{
		return true;
	}

	D3D11_MAPPED_SUBRESOURCE	m_cMappedResource;	//!< ���_�V�F�[�_�[
	// �R���X�^���g�o�b�t�@�ɏ������߂�悤�ɐݒ�
	hr = pcDeviceContext->Map( 
		m_pcDomainConstantBuffer,	//	�f�[�^���������ݗp�o�b�t�@
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
	pcDeviceContext->Unmap( m_pcDomainConstantBuffer, NULL );

	pcDeviceContext->DSSetConstantBuffers( nRegisterNum, 1, &m_pcDomainConstantBuffer );

	return true;
}

//	�쐬�ł����V�F�[�_�[���f�o�C�X�R���e�L�X�g�ɐݒ�
bool Effect::SetShader()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();
	
	// �e�V�F�[�_�[���쐬����Ă���ΐݒ肷��
	
	// ���_�V�F�[�_�[
	if( m_pcVS )
	{
		pcDeviceContext->VSSetShader( m_pcVS, NULL, 0 );
	}
	// �s�N�Z���V�F�[�_�[
	if( m_pcPS )
	{
		pcDeviceContext->PSSetShader( m_pcPS, NULL, 0 );
	}
	// �W�I���g���[�V�F�[�_�[�̃Z�b�g
	if( m_pcGS )
	{
		pcDeviceContext->GSSetShader( m_pcGS, NULL, 0);
	}
	// �n���V�F�[�_�[�̐ݒ�
	if( m_pcHull )
	{
		pcDeviceContext->HSSetShader( m_pcHull, NULL, 0 );
	}
	// �h���C���V�F�[�_�[�̐ݒ�
	if( m_pcDomain )
	{
		pcDeviceContext->DSSetShader( m_pcDomain, NULL, 0 );
	}
	
	return true;
}

}	//	graphics	end
}	//	iruna		end