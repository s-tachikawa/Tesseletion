//*********************************************************************
/*!
	@file	iruna_input_common.h
	@brief	�C���v�b�g ���ʃw�b�_�[
	@author	���� �Ė�
	@date	2011/06/24	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_INPUT_COMMON_H
#define IRUNA_INPUT_COMMON_H


/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"

namespace iruna
{
namespace io
{
//	�C���v�b�g�f�o�C�X�̏�Ԉꗗ
enum INPUT_STATE{
	INPUT_RELEASE	= 0,	//!< �����Ă���
	INPUT_PUSH		= 1,	//!< �������u��
	INPUT_PUSHED	= 2,	//!< �����Ă���
	INPUT_RELEASED	= 3,	//!< �������u��
};

// �C���v�b�g�f�o�C�X�̏�ԃe�[�u��
const INPUT_STATE	INPUT_STATE_TABLE[ 2 ][ 2 ] = {
	{ INPUT_RELEASE,	INPUT_RELEASED	},
	{ INPUT_PUSH,		INPUT_PUSHED	},
};

//!=====================================================================
//!
//! @struct	MouseButton
//! @brief	�}�E�X�̃{�^���̈ꗗ
//!
//!=====================================================================
struct MouseButton
{
	enum Type{
		LEFT,
		RIGHT,
		CENTER,
		KEY3,
		KEY4,
		KEY5,
		KEY6,
		KEY7
	};
};

}	// io		end
}	// iruna	end

/*----�֐� �錾----------------------------------------------------*/
namespace iruna
{
namespace io
{

//!--------------------------------------------------------------------
//! 
//! @brief	�L�[�{�[�h�̎w�肵���L�[�̏�Ԃ�Ԃ�
//! @param	[in] key	- ���ׂ����L�[
//! @retval	�����ꂽ�L�[�̏��
//! 
//!--------------------------------------------------------------------
INPUT_STATE		CheckKeyState( U_LONG key );

//!--------------------------------------------------------------------
//! 
//! @brief	�}�E�X�̎w�肵���L�[�̏�Ԃ�Ԃ�
//! @param	[in] key	- ���ׂ����L�[
//! @retval	�����ꂽ�L�[�̏��
//! 
//!--------------------------------------------------------------------
INPUT_STATE		CheckMouseState( MouseButton::Type key );

//!--------------------------------------------------------------------
//! 
//! @brief	�}�E�X�J�[�\���̈ʒu���擾����
//! @retval	�}�E�X�J�[�\���̈ʒu
//! 
//!--------------------------------------------------------------------
POINT			GetMousePosition();

}	//	io		end
}	//	iruna	end
#endif //	IRUNA_INPUT_COMMON_H	end