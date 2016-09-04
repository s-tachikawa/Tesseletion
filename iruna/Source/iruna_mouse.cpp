//---------------------------------------------------------
// 
//	iruna_mouse.cpp
//	マウス関連
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_mouse.h"
#include <algorithm>

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace io
{

// 静的メンバ変数の実体
DIMOUSESTATE2*	Mouse::nowState	= 0;
DIMOUSESTATE2*	Mouse::oldState	= 0;
POINT			Mouse::position;
HWND			Mouse::hWindow	= 0;

// コンストラクタ
Mouse::Mouse()
	: pDIDevice( 0 )
{
	nowState	= new DIMOUSESTATE2;
	oldState	= new DIMOUSESTATE2;
	
	memset( nowState,  0, sizeof( DIMOUSESTATE2 ) );
	memset( oldState,  0, sizeof( DIMOUSESTATE2 ) );
	memset( &position, 0, sizeof( POINT			) );

	return;
}

// デストラクタ
Mouse::~Mouse()
{
	SafeDelete( oldState );
	SafeDelete( nowState );

	if( pDIDevice )
	{
		pDIDevice->Unacquire();
		SafeRelease( pDIDevice );
	}

	return;
}

// マウスデバイスを作成する
bool Mouse::Create( HWND hWindow, LPDIRECTINPUT8 pDInput )
{
	DIPROPDWORD	dipdw;

	memset( &dipdw, 0 , sizeof( DIPROPDWORD ) );

	dipdw.diph.dwSize		= sizeof( DIPROPDWORD );
	dipdw.diph.dwHeaderSize	= sizeof( DIPROPHEADER );
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= DIPROPAXISMODE_REL; // 相対座標式

	if( FAILED( pDInput->CreateDevice( GUID_SysMouse, &pDIDevice, 0 ) ) )
	{
		// InputDeviceの生成に失敗
		return false;
	}

	if( FAILED( pDIDevice->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		// デバイスにマウスを登録失敗
		return false;
	}

	if( FAILED( pDIDevice->SetProperty( DIPROP_AXISMODE, &dipdw.diph ) ) )
	{
		// マウスの設定を登録に失敗
		return false;
	}

	if( FAILED( pDIDevice->SetCooperativeLevel( hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		// マウスの感度の登録に失敗
		return false;
	}

	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}

	this->hWindow	= hWindow;
	
	return true;
}

// マウスデバイスを更新する
bool Mouse::Update()
{
	// マウスの位置を取得
	GetCursorPos( &position );

	// 情報の更新
	std::swap( oldState, nowState );
	memset( nowState, 0, sizeof( DIMOUSESTATE2 ) );	// 念のため

	// キーの状態を取得、true なら取得成功
	if( SUCCEEDED( pDIDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), nowState ) ) )
	{
		return true;
	}

	// 再度取得を試みる、true なら取得できなかった
	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}

	// もう一度取得してみる、true なら取得成功
	if( SUCCEEDED( pDIDevice->GetDeviceState( sizeof( DIMOUSESTATE2 ), nowState ) ) )
	{
		return true;
	}
		
	// 取得できなかった
	return false;
}

// 指定したキーの状態を返す(静的メンバ関数)
INPUT_STATE Mouse::GetState( MouseButton::Type key )
{
	// 最上位ビット( '0'000 0000 )にフラグが入ってるので右に7つずらす
	return INPUT_STATE_TABLE[ nowState->rgbButtons[ key ] >> 7 ][ oldState->rgbButtons[ key ] >> 7 ];
}

// マウスカーソルの位置を返す(静的メンバ関数)
POINT Mouse::GetPosition()
{
	POINT	temp = position;

	ScreenToClient( hWindow, &temp );
	return temp; 
}

}	//	io		end
}	//	iruna	end