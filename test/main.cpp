
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

	// ���C�u�����Ǘ��N���X
	// ���C�u�����̋N���A��ԍŏ��ɂ���
	System*	system	= &System::GetInstance();
	if (!system->Setup(WINDOW_SIZW_X, WINDOW_SIZW_Y, true, "DX11ModelSample"))	// WS_POPUP�Řg��������
		return -1;

	// �ʏ�J�����̐ݒ�
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
	
	
	// ���C�����[�v
	while( system->Run() )
	{
	
		m_cModel->UpDate();
		// �E�B���h�E���A�N�e�B�u�̎��������s
		if( system->IsActive() )
		{
			ClearScreen();
			
			m_cModel->Draw(sCamera, m_sPos);

			// �`��I��
			SwapScreen();
		}

		// �E�B���h�E���m���A�N�e�B�u�̎��̏���
		else
			system->Idle();
	}

	//SafeDelete( pcBox );
	//SafeDelete( pcBoard );
	//SafeDelete( pcTex );
	//SafeDelete( pcShadowMap );
	//SafeDelete(pcDotSprite);
	SafeDelete(m_cModel);
	// ���C�u�����̏I��
	system->Release();

	return 0;
}