//*********************************************************************
/*!
	@file	iruna_system_datas.h
	@brief	�V�X�e�����\�z����f�[�^�Q
	@author	���� �Ė�
	@date	2012/05/27	- �쐬
*/
//*********************************************************************
/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_SYSTEM_DATAS_H
#define IRUNA_SYSTEM_DATAS_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----�f�[�^�^�錾-------------------------------------------------*/
namespace iruna
{

//!=====================================================================
//!
//! @class	SystemCreateDatas
//! @brief	�V�X�e���̐ݒ�p�\����
//!
//!=====================================================================
struct SystemCreateDatas
{
	U_LONG width;		//!<	�E�B���h�E�̉���
	U_LONG height;		//!<	�E�B���h�E�̍���
	bool mode;			//!<	�E�B���h�E�̃��[�h(�E�B���h�Eor�t���X�N���[��)
	LPCSTR name;		//!<	�E�B���h�E�̃^�C�g��
	U_INT speakers;		//!<	�X�s�[�J�[�̍\��(�f�t�H���g��SPEAKER_STEREO)
	DWORD style;		//!<	�E�B���h�E�̃X�^�C��(�f�t�H���g��WS_OVERLAPPEDWINDOW)
	DWORD styleEx;		//!<	�E�B���h�E�̊g���X�^�C��(�f�t�H���g��0)
	WORD iconID;		//!<	�E�B���h�E�̃A�C�R���̃��\�[�XID

	SystemCreateDatas()
		:	width( 640 ),
			height( 480 ),
			mode( true ),
			name( "NoName" ),
			speakers( SPEAKER_STEREO ),
			style( WS_OVERLAPPEDWINDOW ),
			styleEx( 0 ),
			iconID( 0 )
	{
		return;
	}

};

}	//	iruna	end

#endif	//	IRUNA_SYSTEM_DATAS_H	end