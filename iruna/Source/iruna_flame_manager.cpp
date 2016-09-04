//---------------------------------------------------------
// 
//	iruna_flame_manager.cpp
//	フレームの管理
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_flame_manager.h"

/*----プリプロセッサディレクティブ---------------------------------*/
#pragma comment ( lib, "winmm.lib" )

namespace iruna
{
namespace core
{

// 静的メンバ変数の実体
U_LONG	FrameRateManage::standardOneMS	= 0;
float	FrameRateManage::standardFps	= 0.f;
float	FrameRateManage::secondAverage	= 0.f;

// コンストラクタ
FrameRateManage::FrameRateManage()
{
	timeBeginPeriod( 1 );

	return;
}

// デストラクタ
FrameRateManage::~FrameRateManage()
{
	timeEndPeriod( 1 );

	return;
}

// フレームパーセコンドの設定する(静的メンバ関数)
void FrameRateManage::SetFrameRate( float setFps )
{
	standardFps		= setFps;
	standardOneMS	= static_cast< U_LONG >( 1000 / setFps );
	secondAverage	= setFps;

	return;
}

// 1秒で何フレームだったかを取得する(静的メンバ関数)
float FrameRateManage::GetFrameRate()
{
	return secondAverage;
}

// 設定したフレームパーセコンドを取得する(静的メンバ関数)
float FrameRateManage::GetStandardFrameRate()
{
	return standardFps;
}

// フレームレートを同期させる
bool FrameRateManage::Synchronization()
{
	static	U_LONG	begin		= 0;	// 計測開始時間
	static	U_LONG	end			= 0;	// 計測終了時間
	static	U_LONG	sumMS		= 0;	// 1秒間の㍉秒の合計
	static	U_LONG	frameCount	= 0;	// 何フレームたったか

	if( standardFps <= frameCount )
	{
		secondAverage	= 1000.f / ( sumMS / standardFps );
		sumMS			= 0;
		frameCount		= 0;
	}

	end		= timeGetTime();

	// 何㍉秒止めるか
	int		waitMS	= standardOneMS - ( end - begin );

	// スリープする必要があるかどうか
	bool	sleepFlag = ( 0 < waitMS );

	if( sleepFlag )
		Sleep( waitMS );

	sumMS	+= timeGetTime() - begin;
	begin	= timeGetTime();

	++frameCount;

	return sleepFlag;
}

}	//	core	end
}	//	iruna	end