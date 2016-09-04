//---------------------------------------------------------
// 
//	iruna_keyboard.cpp
//	キーボード関連
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Source/iruna_keyboard.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace io
{

// 静的メンバ変数の実体
BYTE*	Keyboard::nowState	= 0;
BYTE*	Keyboard::oldState	= 0;

// コンストラクタ
Keyboard::Keyboard()
	: pDIDevice( 0 )
{
	nowState	= new BYTE[ 256 ];
	oldState	= new BYTE[ 256 ];

	memset( nowState, 0, sizeof( BYTE ) * 256 );
	memset( oldState, 0, sizeof( BYTE ) * 256 );

	return;
}

// デストラクタ
Keyboard::~Keyboard()
{
	SafeArrayDelete( oldState );
	SafeArrayDelete( nowState );

	if( pDIDevice )
	{
		pDIDevice->Unacquire();
		SafeRelease( pDIDevice );
	}

	return;
}

// キーボードデバイスを作成する
bool Keyboard::Create( HWND hWindow, LPDIRECTINPUT8 pDInput )
{
	if( FAILED( pDInput->CreateDevice( GUID_SysKeyboard, &pDIDevice, 0 ) ) )
	{
		//	キーボードデバイスの生成に失敗
		return false;
	}

	if( FAILED( pDIDevice->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		// デバイスにキーボードを登録失敗
		return false;
	}

	if( FAILED( pDIDevice->SetCooperativeLevel( hWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		// キーボードの感度の設定を失敗
		return false;
	}

	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}

	return true;
}

// キーボードデバイスを更新する
bool Keyboard::Update()
{
	std::swap( oldState, nowState );
	memset( nowState, 0, sizeof( BYTE ) * 256 );	// 念のため

	// キーの状態を取得、true なら取得成功
	if( SUCCEEDED( pDIDevice->GetDeviceState( 256, nowState ) ) )
	{
		return true;
	}
	// 再度取得を試みる、true なら取得できなかった
	if( FAILED( pDIDevice->Acquire() ) )
	{
		return false;
	}
	// もう一度取得してみる、true なら取得成功
	if( SUCCEEDED( pDIDevice->GetDeviceState( 256, nowState ) ) )
	{	
		return true;
	}	
	// 取得できなかった
	return false;
}

// 指定したキーの状態を返す(静的メンバ関数)
INPUT_STATE Keyboard::GetState( U_LONG key )
{
	// 最上位ビット( '0'000 0000 )にフラグが入ってるので右に7つずらす
	return INPUT_STATE_TABLE[ nowState[ key ] >> 7 ][ oldState[ key ] >> 7 ];
}

}	//	io		end
}	//	iruna	end