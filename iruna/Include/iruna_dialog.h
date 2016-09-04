//*********************************************************************
/*!
	@file	iruna_dialog.h
	@brief	�V�X�e���_�C�A���O�𐶐�����
	@author	���� �Ė�
	@date	2011/10/21	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_DIALOG_H
#define IRUNA_DIALOG_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----�l�[���X�y�[�X-------------------------------------------------*/
namespace iruna
{
namespace core
{

/*----�O���[�o���ϐ���`---------------------------------*/
extern LPCTSTR			CD_FILTER_LOAD_MODEL;	//!<	�ǂݍ��ރt�@�C��(���f��)
extern LPCTSTR			CD_FILTER_SAVE_MODEL;	//!<	�������ރt�@�C��(���f��)
extern LPCTSTR			CD_FILTER_TEXTURE;		//!<	�ǂݍ��ރt�@�C��(�e�N�X�`��)
extern LPCTSTR			CD_FILTER_SHEDER;		//!<	�ǂݍ��ރt�@�C��(�V�F�[�_�[)

extern const DWORD		CD_FLAGS_SAVE;		//!<	�_�C�A���O�t���O(SAVE)
extern const DWORD		CD_FLAGS_LOAD;		//!<	�_�C�A���O�t���O(LOAD)

/*----�O���[�o���֐���`---------------------------------*/

//!--------------------------------------------------------------------
//! 
//! @brief	���O�����ĕۑ��_�C�A���O�̐���
//! @param	[in] path		- �ۑ��悷��f�B���N�g���p�X
//! @param	[in] filter		- �ǂݍ��ݎ��̊g���q�̃p�X
//! @param	[in] flags		- �_�C�A���O�������ɑ��̃E�B���h�E���A�N�e�B�u�ɂ��邩�ǂ����̃t���O
//! @param	[in] fullPath	- �t���p�X���擾���邩�ǂ���
//! @retval	���ʃt���O
//! 
//!--------------------------------------------------------------------
extern int				SaveDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

//!--------------------------------------------------------------------
//! 
//! @brief	�J���_�C�A���O�̐���
//! @param	[in] path		- �J����̃f�B���N�g���p�X
//! @param	[in] filter		- �ǂݍ��ݎ��̊g���q�̃p�X
//! @param	[in] flags		- �_�C�A���O�������ɑ��̃E�B���h�E���A�N�e�B�u�ɂ��邩�ǂ����̃t���O
//! @param	[in] fullPath	- �t���p�X���擾���邩�ǂ���
//! @retval	���ʃt���O
//! 
//!--------------------------------------------------------------------
extern int				LoadDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath );

}	//	core
}	//	iruna


#endif	//	IRUNA_DIALOG_H	end