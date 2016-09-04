//*********************************************************************
/*!
	@file	iruna.h
	@brief	iruna���C�u�����ꊇ�C���N���[�h
	@author	���� �Ė�
	@date	2011/06/22	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef _IRUNA_H
#define _IRUNA_H

/*----�C���N���[�h-------------------------------------------------*/

// �R�A�n
#include "../Include/iruna_core.h"

// �O���t�B�b�N�X�n
#include "../Include/iruna_graphics.h"

//	�W�I���g���[�n
#include "../Include/iruna_geometry.h"

// I/O�n
#include "../Include/iruna_io.h"

// ���w�n
#include "../Include/iruna_math.h"

// �T�E���h�n
#include "../Include/iruna_sound.h"

// ���[�e�B���e�B�n
#include "../Include/iruna_utility.h"

// �V�X�e���n
#include "../Include/iruna_system.h"

//	�X�N���v�g�֘A
#include "../Include/iruna_script.h"

//	�����G���W���֘A
#include "../Include/iruna_physics.h"

/*----�v���v���Z�b�T�f�B���N�e�B�u---------------------------------*/
#ifdef _DEBUG
#pragma comment ( lib, "iruna_d.lib" )

#else
#pragma comment ( lib, "iruna.lib"	)



#endif




#endif	//	_IRUNA_H	end