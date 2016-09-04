//*********************************************************************
/*!
	@file	iruna_input_device.h
	@brief	�C���v�b�g�f�o�C�X�̊Ǘ�
	@author	���� �Ė�
	@date	2011/06/24	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_INPUT_DEVICE_H
#define IRUNA_INPUT_DEVICE_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace io
{

// �O���錾
class Keyboard;
class Mouse;

//!=====================================================================
//!
//! @class	InputDevice
//! @brief	�C���v�b�g�f�o�C�X�Ǘ��N���X
//!
//!=====================================================================
class InputDevice
{
// �v���C�x�[�g	�����o�ϐ�
private:
	LPDIRECTINPUT8	pDInput;	//!< �_�C���N�g�C���v�b�g
	Keyboard*		keyboard;	//!< �L�[�{�[�h�f�o�C�X
	Mouse*			mouse;		//!< �}�E�X�f�o�C�X

// �p�u���b�N	�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	InputDevice();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~InputDevice();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�C���v�b�g�f�o�C�X���쐬����
	//! @param	[in] hWindow	- �E�B���h�E�n���h��
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Create( HWND hWindow );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�C���v�b�g�f�o�C�X���X�V����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Update();
};

}	//	io		end
}	//	iruna	end

#endif	//	IRUNA_INPUT_DEVICE_H	end