//---------------------------------------------------------
// 
//	iruna_window.cpp
//	�E�C���h�E�̃R���g���[��
//	�쐬�� 6��22��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Source/iruna_window.h"

namespace iruna
{
namespace core
{
//	Window	Class
//	�ÓI�����o�ϐ��̎���
LPCSTR	Window::CLASS_NAME	= "IrunaLibrary";

// �R���X�g���N�^
Window::Window()
	:	winMode		( false ),
		winWidth	( 0 ),
		winHeight	( 0 ),
		winName		( 0 ),
		winStyle	( 0 ),
		winStyleEx	( 0 ),
		winIcon		( 0 ),
		hWindow		( 0 )
{
	return;
}

// �f�X�g���N�^
Window::~Window()
{
	//	�E�C���h�E�̔j��
	UnregisterClass( CLASS_NAME, static_cast< HINSTANCE >( GetModuleHandle( 0 ) ) );
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK Window::WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParame )
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	case WM_KEYDOWN:
		if( wParam == VK_ESCAPE )
		{
			int hr = MessageBox( NULL ,"�Q�[�����I�����܂����H" , "�A�v���P�[�V�����̏I��" , MB_YESNO );
		
			if( hr == IDYES )
			{
				PostQuitMessage( 0 );
				return 0;
			}
			return 0;
		}
		break;
	}

	return DefWindowProc( hWnd , message , wParam , lParame );
}

// �E�B���h�E�̖��O��ݒ肷��
void Window::SetName( LPCSTR name )
{
	winName		= name;

	return;
}

// �E�B���h�E�̃T�C�Y��ݒ肷��
void Window::SetSize( U_LONG width , U_LONG height )
{
	winWidth	= width;
	winHeight	= height;

	return;
}

// �E�B���h�E�̃��[�h��ݒ肷��(�E�B���h�Eor�t���X�N���[��)
void Window::SetMode( bool mode )
{
	winMode		= mode;

	return;
}

// �E�B���h�E�̃X�^�C����ݒ肷��
void Window::SetStyle( DWORD style , DWORD styleEx )
{
	winStyle	= style;
	winStyleEx	= styleEx;

	return;
}

// �E�B���h�E�̃X�^�C����ݒ肷��
void Window::SetIcon( WORD icon )
{
	winIcon = icon;

	return;
}


// �E�B���h�E�̉�����Ԃ�
U_LONG Window::GetWidth()
{
	return winWidth;
}

// �E�B���h�E�̍�����Ԃ�
U_LONG Window::GetHeight()
{
	return winHeight;
}

// �E�B���h�E�̃��[�h��Ԃ�
bool Window::GetMode()
{
	return winMode;
}

// �E�B���h�E�n���h����Ԃ�
HWND Window::GetHandle()
{
	return hWindow;
}

// �E�B���h�E���쐬
bool Window::Create()
{
	// �E�B���h�E�̃C���X�^���X�̎擾
	HINSTANCE hInstance		= static_cast< HINSTANCE >( GetModuleHandleA( 0 ) );
	
	//	�A�C�R���̓ǂݍ���
	int				tempIcom		= winIcon;
	HICON			iconHandle;

	iconHandle = reinterpret_cast<HICON>( LoadImage(
		hInstance,
		MAKEINTRESOURCE( tempIcom ),
		IMAGE_ICON,
		GetSystemMetrics( SM_CXSMICON ),
		GetSystemMetrics( SM_CYSMICON ),
		( LR_DEFAULTCOLOR | LR_SHARED )
	) );

	// �E�B���h�E�̐ݒ�
	WNDCLASSEXA	winClass;

	winClass.cbSize			= sizeof( WNDCLASSEXA );
	winClass.style			= CS_CLASSDC;
	winClass.lpfnWndProc	= Window::WindowProc;
	winClass.cbClsExtra		= 0;
	winClass.cbWndExtra		= 0;
	winClass.hInstance		= hInstance;
	winClass.hIcon			= iconHandle;
	winClass.hCursor		= LoadCursor( 0, IDC_ARROW );
	winClass.hbrBackground	= static_cast< HBRUSH >( GetStockObject( DKGRAY_BRUSH ) );
	winClass.lpszMenuName	= 0;
	winClass.lpszClassName	= CLASS_NAME;
	winClass.hIconSm		= iconHandle;

	// �E�B���h�E�̓o�^
	if( 0 == RegisterClassEx( &winClass ) )
	{
		//	�E�B���h�E�̓o�^�Ɏ��s
		return false;
	}

	// �E�B���h�E�̕��ƍ����̐ݒ�
	RECT	temp = { 0, 0, winWidth, winHeight };
	AdjustWindowRect( &temp, winStyle, false );

	// ��Őݒ肵���E�B���h�E�N���X�����ɍ쐬
	hWindow	= CreateWindowExA(
				winStyleEx,
				CLASS_NAME,
				winName,
				winStyle,
				0,
				0,
				temp.right - temp.left,
				temp.bottom - temp.top,
				GetDesktopWindow(),
				0,
				hInstance,
				0 );

	
	if( 0 == hWindow )
	{
		// �E�B���h�E�̍쐬�Ɏ��s
		return false;
	}

	// �E�B���h�E�̕\��
	ShowWindow( hWindow, SW_SHOW );
	UpdateWindow( hWindow );

	return true;
}

}	//	core	end
}	//	iruna	end