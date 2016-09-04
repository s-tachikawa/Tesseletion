//---------------------------------------------------------
// 
//	iruna_texture.cpp
//	�e�N�X�`���[�̊Ǘ�
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_texture.h"
#include "../Source/iruna_device.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^
Texture::Texture()
	:	m_pcTexture( NULL ),
		m_pcSampleLinear( NULL ),
		m_pcDynamicTexture( NULL ),
		m_pcRenderTargetView( NULL ),
		m_pcDepthStencilView( NULL ),
		m_pcDepthStencil( NULL )
{
	return;	
}

// �f�X�g���N�^
Texture::~Texture()
{
	SafeRelease( m_pcTexture );
	SafeRelease( m_pcSampleLinear );

	// ���I�e�N�X�`���Ƃ��č쐬����Ă���̂ł���Ή������
	if( m_pcDynamicTexture )
	{
		SafeRelease( m_pcDynamicTexture );
	}
	if( m_pcRenderTargetView )
	{
		SafeRelease( m_pcRenderTargetView );
	}
	if( m_pcDepthStencil )
	{
		SafeRelease( m_pcDepthStencil );
	}
	if( m_pcDepthStencilView )
	{
		SafeRelease( m_pcDepthStencilView );
	}
	

	return;
}

// �摜�t�@�C������e�N�X�`����ǂݍ���
bool Texture::Load( std::string path, Color4 color, U_INT mipLevel, DWORD filter )
{
	// �e�N�X�`���̓ǂݍ��ݐݒ�
	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	LoadInfo.Width = 0;									//	�ǂݍ��ރe�N�X�`���̕�0�ɐݒ肷��Ƃ��̃e�N�X�`���̑傫���ɂȂ�H
	LoadInfo.Height = 0;								//	�ǂݍ��ރe�N�X�`���̍���0�ɐݒ肷��Ƃ��̃e�N�X�`���̑傫���ɂȂ�H
	LoadInfo.Depth = 0;									//	�f�v�X�̐[�x�ݒ�{�����[���e�N�X�`���̂Ƃ��ɂ����K�p�ł��Ȃ�
	LoadInfo.FirstMipLevel = 0;							//	�~�b�v�}�b�v���x���ō��l�̐ݒ�
	LoadInfo.MipLevels = D3DX11_DEFAULT,				//	�e�N�X�`�����̃~�b�v�}�b�v���x�����̐ݒ�
	LoadInfo.Usage = D3D11_USAGE_DEFAULT;				//	�e�N�X�`���̎g�p���@�̐ݒ�
	LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;	//	�f�o�C�X�R���e�L�X�g�̃o�C���h�ݒ�
	LoadInfo.CpuAccessFlags = 0;						//	CPU�A�N�Z�X�̐ݒ�
	LoadInfo.MiscFlags = 0;								//	���\�[�X�v���p�e�B�̐ݒ�
	LoadInfo.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	//	�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	LoadInfo.Filter = D3DX11_FILTER_TRIANGLE;			//	�e�N�X�`���̃t�B���^�[�ݒ�
	LoadInfo.MipFilter = D3DX11_FILTER_TRIANGLE;		//	�ݒ肵���t�B���^�[�Ń~�b�v�}�b�v���t�B���^�����O����t���O
	LoadInfo.pSrcInfo = NULL;							//	�I���W�i���C���[�W�̃��\�[�X


	if( FAILED( D3DX11CreateShaderResourceViewFromFile(
				Device::GetDevice(),
				path.c_str(),
				&LoadInfo,
				NULL,
				&m_pcTexture,
				NULL) ) )
	{
		return false;
	}

	recoveryPath	= path;

	return true;
}

// �e�N�X�`���̃T�v���[�X�e�[�g
bool Texture::CreateSamplerSate()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC sSamDesc;
	ZeroMemory(&sSamDesc,sizeof(D3D11_SAMPLER_DESC));

	sSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sSamDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sSamDesc.MinLOD = 0;
	sSamDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// �T���v���[�X�e�[�g�쐬
	pcDevice->CreateSamplerState( &sSamDesc, &m_pcSampleLinear );

	return false;
}

// �J���̓��I�e�N�X�`�����쐬����
bool Texture::CreateTexture( U_INT width, U_INT height, DWORD usage, U_INT mipLevel, DXGI_FORMAT eFormat )
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// 2�����e�N�X�`���̐ݒ�
	D3D11_TEXTURE2D_DESC sTexDesc;
	memset( &sTexDesc, 0, sizeof( sTexDesc ) );
	sTexDesc.Usage              = D3D11_USAGE_DEFAULT;
	sTexDesc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	sTexDesc.BindFlags          = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	sTexDesc.Width              = width;
	sTexDesc.Height             = height;
	sTexDesc.CPUAccessFlags     = 0;
	sTexDesc.MipLevels          = 1;
	sTexDesc.ArraySize          = 1;
	sTexDesc.SampleDesc.Count   = 1;
	sTexDesc.SampleDesc.Quality = 0;

	hr = pcDevice->CreateTexture2D( &sTexDesc, NULL, &m_pcDynamicTexture );

	// �e�N�X�`���̍쐬�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}

	bool bSuccess = CreateRenderTerget();

	// �����_�[�^�[�Q�b�g�̍쐬�Ɏ��s
	if( !bSuccess )
	{
		return false;
	}

	//	�V�F�[�_�[���\�[�X�̍쐬
	bSuccess = CreateShaderResourceView();
	
	//�@�V�F�[�_�[���\�[�X�̍쐬�Ɏ��s
	if( !bSuccess )
	{
		return false;
	}

	bSuccess = CreateDepthStecil( width, height );
	// �f�v�X�X�e���V���̍쐬�Ɏ��s
	if( !bSuccess )
	{
		return false;
	}

	// ���I�ȃe�N�X�`���̍쐬�ɐ���
	return true;
	
}

//	�����_�[�^�[�Q�b�g�̍쐬
bool Texture::CreateRenderTerget()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// ���I�ȃe�N�X�`�����쐬����Ă��Ȃ�
	if( !m_pcDynamicTexture )
	{
		return false;
	}

	// �����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC sRenderTergetDesc;
	memset( &sRenderTergetDesc, 0, sizeof( sRenderTergetDesc ) );
	sRenderTergetDesc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
	sRenderTergetDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;

	// �����_�[�^�[�Q�b�g�̍쐬
	hr = pcDevice->CreateRenderTargetView( m_pcDynamicTexture, &sRenderTergetDesc, &m_pcRenderTargetView );

	if( FAILED( hr ) )
	{
		return false;
	}

	return true;

}

// �f�v�X�X�e���V���̍쐬
bool Texture::CreateDepthStecil( U_INT width, U_INT height )
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	//	�f�v�X�X�e���V���r���[�̍쐬
	D3D11_TEXTURE2D_DESC sDepthDesc;
	sDepthDesc.Width					= width;
	sDepthDesc.Height					= height;
	sDepthDesc.MipLevels				= 1;
	sDepthDesc.ArraySize				= 1;
	sDepthDesc.Format					= DXGI_FORMAT_D24_UNORM_S8_UINT;
	sDepthDesc.SampleDesc.Count			= 1;
	sDepthDesc.SampleDesc.Quality		= 0;
	sDepthDesc.Usage					= D3D11_USAGE_DEFAULT;
	sDepthDesc.BindFlags				= D3D11_BIND_DEPTH_STENCIL;
	sDepthDesc.CPUAccessFlags			= 0;
	sDepthDesc.MiscFlags				= 0;

	hr = pcDevice->CreateTexture2D( &sDepthDesc, NULL, &m_pcDepthStencil );

	// �f�v�X�X�e���V���p�e�N�X�`���̍쐬�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC sDepthStencilViewDesc;
	sDepthStencilViewDesc.Format		= sDepthDesc.Format;
	sDepthStencilViewDesc.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2DMS;
	sDepthStencilViewDesc.Flags			= 0;

	hr = pcDevice->CreateDepthStencilView( m_pcDepthStencil, &sDepthStencilViewDesc, &m_pcDepthStencilView );

	// �f�v�X�X�e���V���r���[�̍쐬�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}

// �V�F�[�_�[���\�[�X�r���[�̍쐬
bool Texture::CreateShaderResourceView()
{
	ID3D11Device* pcDevice = Device::GetDevice();
	HRESULT hr = S_OK;

	// ���I�ȃe�N�X�`�����쐬����Ă��Ȃ�
	if( !m_pcDynamicTexture )
	{
		return false;
	}

	// �V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC sShaderResourceDesc;
	memset( &sShaderResourceDesc, 0, sizeof( sShaderResourceDesc ) );
	sShaderResourceDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	sShaderResourceDesc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
	sShaderResourceDesc.Texture2D.MipLevels = 1;

	hr = pcDevice->CreateShaderResourceView( m_pcDynamicTexture, &sShaderResourceDesc, &m_pcTexture );

	if( FAILED( hr ) )
	{
		return false;
	}

	return true;
}
// �e�N�X�`�����������
void Texture::Release()
{
	
	SafeRelease( m_pcSampleLinear );
	recoveryPath.clear();
	SafeRelease( m_pcTexture );
	
	// ���I�ȃe�N�X�`�����쐬����Ă���Ή��
	if( m_pcDynamicTexture )
	{
		SafeRelease( m_pcDynamicTexture );
	}
	if( m_pcRenderTargetView )
	{
		SafeRelease( m_pcRenderTargetView );
	}

	return;
}

// �e�N�X�`�������b�N���A�A�N�Z�X���邽�߂�LockedRect��Ԃ�(���I�e�N�X�`���̂�)
bool Texture::Lock( LockedRect &rect, DWORD flag )
{
	//return SUCCEEDED( texture->LockRect( 0, &rect, 0, flag ) );
	return true;
}

// �e�N�X�`�����A�����b�N���A�A�N�Z�X�ł��Ȃ��悤�ɂ���(���I�e�N�X�`���̂�)
bool Texture::Unlock()
{
	//return SUCCEEDED( texture->UnlockRect( 0 ) );
	return true;
}

// �e�N�X�`�����擾
ID3D11ShaderResourceView* const Texture::GetTexture()
{
	return m_pcTexture;
}

// �e�N�X�`���T���v���[�X�e�[�g���擾
ID3D11SamplerState* const Texture::GetSamplerState()
{
	return m_pcSampleLinear;
}
// �����_�[�^�[�Q�b�g�̎擾
ID3D11RenderTargetView*	const Texture::GetRenderTerget()
{
	return m_pcRenderTargetView;
}

// �f�v�X�X�e���V���r���[�̎擾
ID3D11DepthStencilView*	const Texture::GetDepthStencil()
{
	return m_pcDepthStencilView;
}

// �e�N�X�`���̃T�C�Y���擾
POINT Texture::GetSize()
{
	POINT				temp;
	ZeroMemory( &temp, sizeof( temp ) );
	//D3DSURFACE_DESC		desc;
	//texture->GetLevelDesc( 0, &desc );

	//temp.x	= desc.Width;
	//temp.y	= desc.Height;

	//return temp;
	return temp;
}

}	//	graphics	end
}	//	iruna		end