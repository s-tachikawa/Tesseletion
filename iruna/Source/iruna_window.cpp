//---------------------------------------------------------
// 
//	iruna_window.cpp
//	ウインドウのコントロール
//	作成日 6月22日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_window.h"

namespace iruna
{
namespace core
{
//	Window	Class
//	静的メンバ変数の実体
LPCSTR	Window::CLASS_NAME	= "IrunaLibrary";

// コンストラクタ
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

// デストラクタ
Window::~Window()
{
	//	ウインドウの破棄
	UnregisterClass( CLASS_NAME, static_cast< HINSTANCE >( GetModuleHandle( 0 ) ) );
}

// ウィンドウプロシージャ
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
			int hr = MessageBox( NULL ,"ゲームを終了しますか？" , "アプリケーションの終了" , MB_YESNO );
		
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

// ウィンドウの名前を設定する
void Window::SetName( LPCSTR name )
{
	winName		= name;

	return;
}

// ウィンドウのサイズを設定する
void Window::SetSize( U_LONG width , U_LONG height )
{
	winWidth	= width;
	winHeight	= height;

	return;
}

// ウィンドウのモードを設定する(ウィンドウorフルスクリーン)
void Window::SetMode( bool mode )
{
	winMode		= mode;

	return;
}

// ウィンドウのスタイルを設定する
void Window::SetStyle( DWORD style , DWORD styleEx )
{
	winStyle	= style;
	winStyleEx	= styleEx;

	return;
}

// ウィンドウのスタイルを設定する
void Window::SetIcon( WORD icon )
{
	winIcon = icon;

	return;
}


// ウィンドウの横幅を返す
U_LONG Window::GetWidth()
{
	return winWidth;
}

// ウィンドウの高さを返す
U_LONG Window::GetHeight()
{
	return winHeight;
}

// ウィンドウのモードを返す
bool Window::GetMode()
{
	return winMode;
}

// ウィンドウハンドルを返す
HWND Window::GetHandle()
{
	return hWindow;
}

// ウィンドウを作成
bool Window::Create()
{
	// ウィンドウのインスタンスの取得
	HINSTANCE hInstance		= static_cast< HINSTANCE >( GetModuleHandleA( 0 ) );
	
	//	アイコンの読み込み
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

	// ウィンドウの設定
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

	// ウィンドウの登録
	if( 0 == RegisterClassEx( &winClass ) )
	{
		//	ウィンドウの登録に失敗
		return false;
	}

	// ウィンドウの幅と高さの設定
	RECT	temp = { 0, 0, winWidth, winHeight };
	AdjustWindowRect( &temp, winStyle, false );

	// 上で設定したウィンドウクラスを元に作成
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
		// ウィンドウの作成に失敗
		return false;
	}

	// ウィンドウの表示
	ShowWindow( hWindow, SW_SHOW );
	UpdateWindow( hWindow );

	return true;
}

}	//	core	end
}	//	iruna	end