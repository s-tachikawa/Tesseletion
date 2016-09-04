//---------------------------------------------------------
// 
//	iruna_device.cpp
//	�f�o�C�X�̊Ǘ��Ɛ���
//	�쐬�� 6��22��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_device.h"
#include "../Include/iruna_texture.h"
#include "../Include/iruna_viewport.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#ifdef _DEBUG
#pragma comment ( lib, "d3dx9d.lib"	)

#else
#pragma comment ( lib, "d3dx9.lib"	)

#endif

#pragma comment ( lib, "d3d9.lib"	) // DX9�p���C�u����
#pragma comment ( lib, "d3d11.lib"	) // DX9�p���C�u����
#pragma comment ( lib, "d3dx11.lib"	) // DX9�p���C�u����
#pragma comment ( lib,"d3dCompiler.lib")

#pragma comment ( lib, "d3dxof.lib"	)
#pragma comment ( lib, "dxguid.lib"	)
#pragma comment ( lib, "dxerr.lib"  )


/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �ÓI�����o�ϐ��̎���
ID3D11Device*			Device::m_pcDevice				= NULL;
ID3D11DeviceContext*	Device::m_pcDeviceContext		= NULL;
IDXGISwapChain*			Device::m_pcSwapChain			= NULL;
ID3D11RenderTargetView*	Device::m_pcRenderTargetView	= NULL;
ID3D11RasterizerState*	Device::m_pcRasterizestate		= NULL;
ID3D11DepthStencilView*	Device::m_pcDepthStencilView	= NULL;
ID3D11Texture2D*		Device::m_pcDepthStencil		= NULL;
D3D11_VIEWPORT			Device::m_sViewPort;
D3D11_RASTERIZER_DESC	Device::m_sRas;

//	�R���X�g���N�^
Device::Device()
{
	return;
}

//	�f�X�g���N�^
Device::~Device()
{
	m_pcDeviceContext->ClearState();
	SafeRelease( m_pcDeviceContext );
	SafeRelease( m_pcSwapChain		);
	SafeRelease( m_pcRenderTargetView );
	SafeRelease( m_pcDevice );
	SafeRelease( m_pcRasterizestate );
	SafeRelease( m_pcDepthStencilView );
	return;
}

// �f�o�C�X��SwapChain���쐬����
bool Device::Create( HWND hWindow, U_LONG width, U_LONG height, bool mode )
{
	HRESULT hr = S_OK;

	// �h���C�o�[�^�C�v�錾
	D3D_DRIVER_TYPE eDriverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,		// �n�[�h�E�F�A�����A��ʓI�Ȏ����͂���
		D3D_DRIVER_TYPE_WARP,			// ���p�t�H�[�}���X�̃\�t�g�E�F�A ���X�^���C�U�[,9_1 ���� 10.1 �܂ł̋@�\���x�������ł��Ȃ��B
		D3D_DRIVER_TYPE_REFERENCE,		// �����x�ŋ@�\�������ł����A�ᑬ�ȃh���C�o�[��ʓI�ł͂Ȃ�
	};
	// �h���C�o�[�̐�
	UINT numDriverTypes = sizeof( eDriverTypes ) / sizeof( eDriverTypes[0] );

	// �@�\���x���^�C�v�̐錾
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,			// DirectX11�̋@�\���^�[�Q�b�g�ɂ��܂��B�V�F�[�_�[���f��5.0
		D3D_FEATURE_LEVEL_10_1,			// DirectX10.1�̋@�\���^�[�Q�b�g�ɂ��܂��B�V�F�[�_�[���f��4.0
		D3D_FEATURE_LEVEL_10_0,			// DirectX10�̋@�\���^�[�Q�b�g�ɂ��܂��B�V�F�[�_�[���f��4.0
	};
	UINT numFeatureLevels = sizeof( featureLevels ) / sizeof( featureLevels[0] );

	//�@�X���b�v�`�F�C���̐ݒ�
	// �X���b�v�`�F�C���̐ݒ�
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );

	sd.BufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = width;							// �E�B���h�E�̉���
	sd.BufferDesc.Height = height;							// �E�B���h�E�̏c��
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// �\���s�N�Z���̃t�H�[�}�b�g32Bit�F��RGBA
	sd.BufferDesc.RefreshRate.Numerator = 60;				// ���������̃t���[�����[�g(���q�j
	sd.BufferDesc.RefreshRate.Denominator = 1;				// ���������̃t���[�����[�g(����)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// �����_�����O�^�[�Q�b�g�Ƃ��Ă��̃o�b�t�@���g�p����t���O
	sd.OutputWindow = hWindow;								// �E�B���h�E�n���h���̎w��
	sd.SampleDesc.Count = 1;								// �}���`�T���v�����O�A�A���`�G�C���A�X�Ɏg�p���鉽�����Ȃ��̂�1�s�N�Z���̐F�����߂�T���v�����O��
	sd.SampleDesc.Quality = 0;								// �}���`�T���v�����O�A�A���`�G�C���A�X�̐��x���x��
	sd.Windowed = mode;										// �E�B���h�E���[�h
	//sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// �X���b�v�`�F�C���̋@�\�ǉ��t���O�A�t���X�N���[���A�E�B���h�E���[�h�̐؂肩�����X���[�Y�ɍs���Ă����B


	// �f�o�C�X�ƃX���b�v�`�F�C�����쐬����B
	for( int i = 0; i < ( int )numDriverTypes; i++ )
	{
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,							// �r�f�I�A�_�v�^�[�̃|�C���^����̃A�_�v�^�[���g�p����ł����NULL���w��
			eDriverTypes[ i ],				// �h���C�o�[�^�C�v�̎w��
			NULL,							// �\�t�g�E�F�A���X�^���C�U�[��DLL�n���h���h���C�o�[�̃^�C�v���\�t�g�E�F�A�ȊO�Ȃ�NULL���w��
			0,								// ���C���[�̃^�C�v���w��f�o�b�O���C���[�ɐݒ肷��Ƒ啝�ɑ��x���ቺ����炵���̂Őݒ肵�Ȃ�
			featureLevels,					//	DirectX�̋@�\���x��
			numFeatureLevels,				// �@�\���x���̌�
			D3D11_SDK_VERSION,				// �g�p����SDK�̃o�[�W����
			&sd,
			&m_pcSwapChain,
			&m_pcDevice,
			NULL,
			&m_pcDeviceContext				// �f�o�C�X�R���e�L�X�g�̐ݒ�
			);

		if ( SUCCEEDED( hr ) )
		{
			// ���������烋�[�v�E�o
			break;
		}
	}
	// �f�o�C�X�̍쐬���s
	if ( FAILED( hr ) )
	{
		return false;
	}
	
	// �o�b�N�o�b�t�@�p�̃e�N�X�`�����쐬
	ID3D11Texture2D* pcBackBuffer;
	hr = m_pcSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pcBackBuffer );
	// �o�b�N�o�b�t�@�̎擾�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}
	// �����_�����O�^�[�Q�b�g�r���[���쐬
	hr = m_pcDevice->CreateRenderTargetView( pcBackBuffer, NULL, &m_pcRenderTargetView );
	pcBackBuffer->Release();
	pcBackBuffer = NULL;
	
	// �����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s
	if( FAILED( hr ) )
	{
		return false;
	}
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
	
	m_pcDevice->CreateTexture2D( &sDepthDesc, NULL, &m_pcDepthStencil );

	D3D11_DEPTH_STENCIL_VIEW_DESC sDepthStencilViewDesc;
	sDepthStencilViewDesc.Format		= sDepthDesc.Format;
	sDepthStencilViewDesc.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2DMS;
	sDepthStencilViewDesc.Flags			= 0;

	m_pcDevice->CreateDepthStencilView( m_pcDepthStencil, &sDepthStencilViewDesc, &m_pcDepthStencilView );
	
	// �����_�[�^�[�Q�b�g���f�o�C�X�R���e�L�X�g�Ƀo�C���h
	m_pcDeviceContext->OMSetRenderTargets( 1, &m_pcRenderTargetView, m_pcDepthStencilView );
	// �r���[�|�[�g�̐ݒ�
	m_sViewPort.Width = (FLOAT)width;
	m_sViewPort.Height = (FLOAT)height;
	m_sViewPort.MinDepth = 0.0f;
	m_sViewPort.MaxDepth = 1.0f;
	m_sViewPort.TopLeftX = 0;
	m_sViewPort.TopLeftY = 0;
	// �r���[�|�[�g���R���e�L�X�g�ɐݒ�
	m_pcDeviceContext->RSSetViewports( 1, &m_sViewPort );

	//	���X�^���C�Y�̐ݒ�
	ZeroMemory( &m_sRas, sizeof( m_sRas ) );
	m_sRas.CullMode = D3D11_CULL_FRONT;
	//m_sRas.FillMode = D3D11_FILL_SOLID;
	m_sRas.FillMode = D3D11_FILL_WIREFRAME;
	m_sRas.FrontCounterClockwise = TRUE;
	m_sRas.DepthClipEnable = TRUE;
	m_sRas.ScissorEnable = FALSE;
	hr = m_pcDevice->CreateRasterizerState( &m_sRas, &m_pcRasterizestate );
	m_pcDeviceContext->RSSetState( m_pcRasterizestate );

	// �u�����h�X�e�[�g�̍쐬
	D3D11_BLEND_DESC BlendStateDesc;
	BlendStateDesc.AlphaToCoverageEnable = FALSE;
	BlendStateDesc.IndependentBlendEnable = FALSE;

	for( int i = 0; i < 8; i++ )
	{
		BlendStateDesc.RenderTarget[ i ].BlendEnable				= TRUE;
		BlendStateDesc.RenderTarget[ i ].SrcBlend					= D3D11_BLEND_SRC_ALPHA;
		BlendStateDesc.RenderTarget[ i ].DestBlend					= D3D11_BLEND_INV_SRC_ALPHA;
		BlendStateDesc.RenderTarget[ i ].BlendOp					= D3D11_BLEND_OP_ADD;
		BlendStateDesc.RenderTarget[ i ].SrcBlendAlpha				= D3D11_BLEND_ONE;
		BlendStateDesc.RenderTarget[ i ].DestBlendAlpha				= D3D11_BLEND_ZERO;
		BlendStateDesc.RenderTarget[ i ].BlendOpAlpha				= D3D11_BLEND_OP_ADD;
		BlendStateDesc.RenderTarget[ i ].RenderTargetWriteMask		= D3D11_COLOR_WRITE_ENABLE_ALL;
	}

	//	�u�����h�X�e�[�g�̍쐬
	m_pcDevice->CreateBlendState(&BlendStateDesc, &m_pcBlendState);
	
	//	�e�F�̐����̍������@
	float blendFactor[4] = {D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO};
	//���̃u�����f�B���O���R���e�L�X�g�ɐݒ�
	m_pcDeviceContext->OMSetBlendState( m_pcBlendState, blendFactor, 0xffffffff );
	return true;
}

// ����ʂ��N���A���A�`����J�n����(�ÓI�����o�֐�)
bool Device::ClearScreen( float r, float g, float b, float a )
{
	// �o�b�N�o�b�t�@�����F�ɐ��߂邩
	float clearColor[ 4 ];
	clearColor[ 0 ] = r;
	clearColor[ 1 ] = g;
	clearColor[ 2 ] = b;
	clearColor[ 3 ] = a;
	m_pcDeviceContext->ClearRenderTargetView( m_pcRenderTargetView, clearColor );
	m_pcDeviceContext->ClearDepthStencilView( m_pcDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
	return false;
}

// �w�肵�������_�[�^�[�Q�b�g���N���A
bool Device::ClearBackBuffer(math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil)
{
	float clearColor[ 4 ];
	clearColor[ 0 ] = vColor.x;
	clearColor[ 1 ] = vColor.y;
	clearColor[ 2 ] = vColor.z;
	clearColor[ 3 ] = vColor.w;
	m_pcDeviceContext->ClearRenderTargetView( pcRenderTerget, clearColor );
	m_pcDeviceContext->ClearDepthStencilView( pcDepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0 );
	return true;
}

// �`����I�����A����ʂɕ`�������̂�\��ʂ֓]��(�ÓI�����o�֐�)
bool Device::SwapScreen()
{
	m_pcSwapChain->Present( 0, 0 );
	return false;
}

// �f�t�H���g�̃����_�����O�^�[�Q�b�g�̎擾(�o�b�N�o�b�t�@�̎擾)
ID3D11RenderTargetView* Device::GetRenderTargetView()
{
	return m_pcRenderTargetView;
}

// �f�t�H���g�̃f�v�X�X�e���V���r���[���擾
ID3D11DepthStencilView* Device::GetDepthStencilView()
{
	return m_pcDepthStencilView;
}

// �f�t�H���g�̃r���[�|�[�g���擾
D3D11_VIEWPORT* Device::GetViewPort()
{
	return &m_sViewPort;
}

// �f�t�H���g�̃��X�^���C�Y�̐ݒ���擾
D3D11_RASTERIZER_DESC* Device::GetRasterizerState()
{
	return &m_sRas;
}

// �f�o�C�X���擾����(�ÓI�����o�֐�)
ID3D11Device* Device::GetDevice()
{
	return m_pcDevice;
}

// �f�o�C�X�R���e�L�X�g���擾����(�ÓI�����o�֐�)
ID3D11DeviceContext* Device::GetDeviceContext()
{
	return m_pcDeviceContext;
}

}//	graphics	end
}//	iruna		end
