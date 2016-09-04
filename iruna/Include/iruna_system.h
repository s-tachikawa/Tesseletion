//*********************************************************************
/*!
	@file	iruna_system.h
	@brief	���C�u�����̃R���g���[��
	@author	���� �Ė�
	@date	2011/06/22	- �쐬
	@date	2011/07/10	- �T�E���h�̒ǉ�
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_SYSTEM_H
#define IRUNA_SYSTEM_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_system_datas.h"


namespace iruna
{
	// �O���錾
namespace core
{

class	Window;
class	FrameRateManage;

}	// core		end

namespace graphics
{

class	Device;
class	Text;

}	// graphics	end

namespace sound
{

	class SoundDevice;

}	//	sound	end	

namespace io
{

class	InputDevice;

}	// io		end

namespace physics
{
class PhysicsCore;

}	//	physics end

//!=====================================================================
//!
//! @class	System
//! @brief	���C�u�����̋N���E�Ǘ��E�I��������N���X(�V���O���g��)
//!
//!=====================================================================
class System
{
// �v���C�x�[�g	�����o�ϐ�
private:
	core::FrameRateManage*	frame;		//!< �t���[�����[�g�Ǘ��N���X
	core::Window*			window;		//!< �E�B���h�E�Ǘ��N���X
	graphics::Device*		device;		//!< �f�o�C�X
	sound::SoundDevice*		sound;		//!< �T�E���h�f�o�C�X
	io::InputDevice*		input;		//!< �C���v�b�g�f�o�C�X
	physics::PhysicsCore*	physics;	//!< �����G���W���Ǘ��N���X
	graphics::Text*			text;		//!< �e�L�X�g�Ǘ��N���X
	static System*			instance;	//!< �C���X�^���X(�ÓI�����o�ϐ�)

// �v���C�x�[�g	�����o�֐�
private:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(�O������̌ďo���֎~)
	//! 
	//!--------------------------------------------------------------------
	System();

// ���p�u���b�N		�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~System();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�X�e���N���X�̗B��̃C���X�^���X��������֐�(�ÓI�����o�֐�)
	//! @retval	System�N���X�̃C���X�^���X
	//! 
	//!--------------------------------------------------------------------
	static System&	GetInstance();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�E�B���h�E��f�o�C�X�̃Z�b�g�A�b�v������
	//! @param	[in] width	- �E�B���h�E�̉���
	//! @param	[in] height	- �E�B���h�E�̍���
	//! @param	[in] mode	- �E�B���h�E�̃��[�h(�E�B���h�Eor�t���X�N���[��)
	//! @param	[in] name	- �E�B���h�E�̃^�C�g��
	//! @param	[in] iconID	- �E�B���h�E�̃A�C�R���̃��\�[�XID
	//! @param	[in] style	- �E�B���h�E�̃X�^�C��(�f�t�H���g��WS_OVERLAPPEDWINDOW)
	//! @param	[in] speakers	- �X�s�[�J�[�̍\��(�f�t�H���g��SPEAKER_STEREO)
	//! @param	[in] styleEx- �E�B���h�E�̊g���X�^�C��(�f�t�H���g��0)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Setup( U_LONG width, U_LONG height, bool mode, LPCSTR name,  U_INT speakers = SPEAKER_STEREO, DWORD style = WS_OVERLAPPEDWINDOW, DWORD styleEx = 0, WORD iconID = 0);

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�E�B���h�E��f�o�C�X���폜�E���������
	//! 
	//!--------------------------------------------------------------------
	void	Release();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�X�e���̍X�V�A���b�Z�[�W�����Ȃ�
	//! @retval	�G���[�t���O	true�F���Ȃ��@false�F�G���[
	//! 
	//!--------------------------------------------------------------------
	bool	Run();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�m���A�N�e�B�u���̃V�X�e���X�V
	//! @retval	�G���[�t���O	true�F���Ȃ��@false�F�G���[
	//! 
	//!--------------------------------------------------------------------
	bool	Idle();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�E�B���h�E���A�N�e�B�u���m���A�N�e�B�u�����擾����
	//! @retval	�A�N�e�B�u�t���O	true�F�A�N�e�B�u�@false�F�m���A�N�e�B�u
	//! 
	//!--------------------------------------------------------------------
	bool	IsActive();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�N�����ɃE�B���h�E���[�h��؂�ւ���
	//! @param	[in] mode	- �E�B���h�E�̃��[�h(�E�B���h�Eor�t���X�N���[��)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	ChangeWindowMode( bool mode );
};

}	//	iruna	end

#endif	//	IRUNA_SYSTEM_H