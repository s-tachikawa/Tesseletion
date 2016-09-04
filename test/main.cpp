
#include "../iruna/Include/iruna.h"
#include "../iruna/Source/iruna_device.h"
#include "box.h"
#include "board.h"
#include "sprite.h"
#include "sgd_model.h"

#include <xnamath.h>

using namespace iruna;
using namespace	graphics;
using namespace core;
using namespace sound;
using namespace physics;
using namespace io;


#define WINDOW_SIZW_X 1280
#define WINDOW_SIZW_Y 920


int WINAPI WinMain( HINSTANCE , HINSTANCE, LPTSTR, int )
{
	//_CrtSetBreakAlloc( 343 );

	// ライブラリ管理クラス
	// ライブラリの起動、一番最初にする
	System*	system	= &System::GetInstance();
	if (!system->Setup(WINDOW_SIZW_X, WINDOW_SIZW_Y, true, "DX11ModelSample"))	// WS_POPUPで枠が消える
		return -1;

	// 通常カメラの設定
	Camera sCamera;
	sCamera.aspect = WINDOW_SIZW_X / WINDOW_SIZW_Y;
	sCamera.eye = math::Vector3( 0, 0, 1000.0f );
	sCamera.fovY = D3DX_PI / 4.0f;
	sCamera.lookAt = math::Vector3( 0, 0, 0 );
	sCamera.upVector = math::Vector3( 0, 1, 0 );
	sCamera.zFar = 10000.0f;
	sCamera.zNear = 0.1f;
	
	CSgdModel* m_cModel = new CSgdModel();
	math::Vector3 m_sPos;
	m_sPos.x = 0.0f;
	m_sPos.y = -100.0f;
	m_sPos.z = 0.0f;
	
	
	// メインループ
	while( system->Run() )
	{
	
		m_cModel->UpDate();
		// ウィンドウがアクティブの時だけ実行
		if( system->IsActive() )
		{
			ClearScreen();
			
			m_cModel->Draw(sCamera, m_sPos);

			// 描画終了
			SwapScreen();
		}

		// ウィンドウがノンアクティブの時の処理
		else
			system->Idle();
	}

	//SafeDelete( pcBox );
	//SafeDelete( pcBoard );
	//SafeDelete( pcTex );
	//SafeDelete( pcShadowMap );
	//SafeDelete(pcDotSprite);
	SafeDelete(m_cModel);
	// ライブラリの終了
	system->Release();

	return 0;
}