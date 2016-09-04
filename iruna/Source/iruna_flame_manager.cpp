//---------------------------------------------------------
// 
//	iruna_flame_manager.cpp
//	�t���[���̊Ǘ�
//	�쐬�� 6��24��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_flame_manager.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#pragma comment ( lib, "winmm.lib" )

namespace iruna
{
namespace core
{

// �ÓI�����o�ϐ��̎���
U_LONG	FrameRateManage::standardOneMS	= 0;
float	FrameRateManage::standardFps	= 0.f;
float	FrameRateManage::secondAverage	= 0.f;

// �R���X�g���N�^
FrameRateManage::FrameRateManage()
{
	timeBeginPeriod( 1 );

	return;
}

// �f�X�g���N�^
FrameRateManage::~FrameRateManage()
{
	timeEndPeriod( 1 );

	return;
}

// �t���[���p�[�Z�R���h�̐ݒ肷��(�ÓI�����o�֐�)
void FrameRateManage::SetFrameRate( float setFps )
{
	standardFps		= setFps;
	standardOneMS	= static_cast< U_LONG >( 1000 / setFps );
	secondAverage	= setFps;

	return;
}

// 1�b�ŉ��t���[�������������擾����(�ÓI�����o�֐�)
float FrameRateManage::GetFrameRate()
{
	return secondAverage;
}

// �ݒ肵���t���[���p�[�Z�R���h���擾����(�ÓI�����o�֐�)
float FrameRateManage::GetStandardFrameRate()
{
	return standardFps;
}

// �t���[�����[�g�𓯊�������
bool FrameRateManage::Synchronization()
{
	static	U_LONG	begin		= 0;	// �v���J�n����
	static	U_LONG	end			= 0;	// �v���I������
	static	U_LONG	sumMS		= 0;	// 1�b�Ԃ̇_�b�̍��v
	static	U_LONG	frameCount	= 0;	// ���t���[����������

	if( standardFps <= frameCount )
	{
		secondAverage	= 1000.f / ( sumMS / standardFps );
		sumMS			= 0;
		frameCount		= 0;
	}

	end		= timeGetTime();

	// ���_�b�~�߂邩
	int		waitMS	= standardOneMS - ( end - begin );

	// �X���[�v����K�v�����邩�ǂ���
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