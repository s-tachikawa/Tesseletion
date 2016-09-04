//---------------------------------------------------------
// 
//	iruna_input_device.cpp
//	InputDeviceの管理と生成
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_input_device.h"
#include "../Source/iruna_keyboard.h"
#include "../Source/iruna_mouse.h"

/*----プリプロセッサディレクティブ---------------------------------*/
#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dxguid.lib"  )

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace io
{

// コンストラクタ
InputDevice::InputDevice()
	: pDInput ( 0 ),
	  keyboard( 0 ),
	  mouse	  ( 0 )
{
	return;
}

// デストラクタ
InputDevice::~InputDevice()
{
	SafeDelete(  mouse	  );
	SafeDelete(  keyboard );
	SafeRelease( pDInput  );

	return;
}

// 各インプットデバイスを作成する
bool InputDevice::Create( HWND hWindow )
{
	if( pDInput )
	{
		return false;
	}

	// デバイスの生成
	if( FAILED( DirectInput8Create(
					static_cast< HINSTANCE >( GetModuleHandle( 0 ) ),
					DIRECTINPUT_VERSION,
					IID_IDirectInput8,
					reinterpret_cast< LPVOID* >( &pDInput ),
					0 ) ) )
	{
		return false;
	}
	// キーボードの生成
	keyboard	= new Keyboard;
	if( !keyboard->Create( hWindow, pDInput ) )
	{
		return false;
	}
	// マウスの生成
	mouse		= new Mouse;
	if( !mouse->Create( hWindow, pDInput ) )
	{
		return false;
	}

	return true;
}

// 各インプットデバイスを更新する
bool InputDevice::Update()
{
	if( !keyboard->Update() )
	{
		return false;
	}

	if( !mouse->Update() )
	{
		return false;
	}

	return true;
}

}	//	io		end
}	//	iruna	end