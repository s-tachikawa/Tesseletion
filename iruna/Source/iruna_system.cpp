//---------------------------------------------------------
// 
//	iruna_system.cpp
//	irunaライブラリ管理クラス
//	作成日 6月24日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_system.h"
#include "../Include/iruna_flame_manager.h"
#include "../Source/iruna_window.h"
#include "../Source/iruna_device.h"
#include "../Source/iruna_input_device.h"
//#include "../Source/iruna_physics_core.h"
#include "../Include/iruna_text.h"
#include "../Source/iruna_sound_device.h"

/*----プリプロセッサディレクティブ---------------------------------*/
#pragma warning( disable : 4127 )	// while文の条件式が定数だとダメなのを無視する

namespace iruna
{

// 静的メンバ変数の実体
System*	System::instance	= 0;

// コンストラクタ(外部からの呼出し禁止)
System::System()
	: frame	( 0 ),
	  window( 0 ),
	  device( 0 ),
	  input ( 0 ),
	  text	( 0 ),
	  sound	( 0 )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	return;
}

// デストラクタ
System::~System()
{
	return;
}

// システムクラスの唯一のインスタンス生成する関数
System& System::GetInstance()
{
	if( !instance )
		instance	= new System;
		
	return *instance; 
}

// ウィンドウやデバイスのセットアップをする
bool System::Setup( U_LONG width, U_LONG height, bool mode, LPCSTR name, U_INT speakers, DWORD style, DWORD styleEx, WORD iconID )
{
	if( window && device )
		return false;

	// フレームレートマネージャを生成
	//frame	= new core::FrameRateManage;
	//core::FrameRateManage::SetFrameRate( 60.f );

	// ウィンドウを作成
	window	= new core::Window;
	window->SetSize( width, height );
	window->SetMode( mode );
	window->SetName( name );
	window->SetStyle( style, styleEx );
	window->SetIcon( iconID );

	if( !window->Create() )
		return false;

	// デバイスを作成
	device	= new graphics::Device;
	
	if( !device->Create( window->GetHandle(), width, height ) )
	{
		return false;
	}

	// インプットデバイスを作成
	input	= new io::InputDevice;

	if( !input->Create( window->GetHandle() ) )
	{
		return false;
	}

	// サウンドデバイスの作成
	//sound	= new sound::SoundDevice;

	//if(sound->CreateSoundDevice( speakers ) != 0)
	//{
	//	return false;
	//}

	//	物理エンジンの初期化
	//physics = new physics::PhysicsCore;
	//physics->PhysicsCoreInit( NULL, NULL );


	// テキスト管理クラスを作成
	//text	= graphics::Text::GetInstance();
	//text->SetStyle( 16, "HG創英角ﾎﾟｯﾌﾟ体" );

	return true;
}

// ウィンドウやデバイスを削除・開放をする
void System::Release()
{
	//SafeDelete( text   );
	SafeDelete( input  );
	SafeDelete( device );
	SafeDelete( window );
	//SafeDelete( frame  );
	//SafeDelete( sound  );
	//SafeDelete( physics );
	SafeDelete( instance );

	return;
}

// システムの更新、メッセージ処理など
bool System::Run()
{
	//frame->Synchronization();

	while( true )
	{
		MSG		msg;
		memset( &msg, 0, sizeof( MSG ) );

		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if( WM_QUIT == msg.message )
		{
	
			return false;
		}
		break;
	}

	//	インプットデバイスの更新
	input->Update();
	//	物理エンジンの更新
	//physics::PhysicsCore::GetDynamicsWorld()->stepSimulation( 1.0f / 60.0f );
	//physics::PhysicsCore::GetDynamicsWorld()->debugDrawWorld();

	return true;
}

// ノンアクティブ時のシステム更新
bool System::Idle()
{
	Sleep( 1 );

	return true;
}

// ウィンドウがアクティブかノンアクティブかを取得する
bool System::IsActive()
{
	return ( window->GetHandle() == GetActiveWindow() );
}

// 起動中にウィンドウモードを切り替える
bool System::ChangeWindowMode( bool mode )
{
	if( window->GetMode() == mode )
		return true;

	//device->SetPresentParameters( window->GetWidth(), window->GetHeight(), mode );

	while( true )
	{
		MSG		msg;
		memset( &msg, 0, sizeof( MSG ) );

		if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if( WM_QUIT == msg.message )
			return false;

		break;
	}

	window->SetMode( mode );

	return true;
}

}	//	iruna	end