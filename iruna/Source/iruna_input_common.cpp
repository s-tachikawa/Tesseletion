//---------------------------------------------------------
// 
//	iruna_io.cpp
//	Iput系共通処理
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_input_common.h"
#include "../Source/iruna_keyboard.h"
#include "../Source/iruna_mouse.h"

namespace iruna
{
namespace io
{

/*----グローバル関数 定義----------------------------------------------------*/

// キーボードの指定したキーの状態を返す
INPUT_STATE CheckKeyState( U_LONG key )
{
	return Keyboard::GetState( key );
}

// マウスの指定したキーの状態を返す
INPUT_STATE CheckMouseState( MouseButton::Type key )
{
	return Mouse::GetState( key );
}

// マウスカーソルの位置を取得する
POINT GetMousePosition()
{
	return Mouse::GetPosition();
}

}	//	io		end
}	//	iruna	end