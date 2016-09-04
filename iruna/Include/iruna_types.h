//*********************************************************************
/*!
	@file	iruna_types.h
	@brief	�^��`
	@author	���� �Ė�
	@date	2011/06/22	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_TYPES_H
#define IRUNA_TYPES_H

/*----�C���N���[�h-------------------------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>
#include <dxerr.h>

#include <xaudio2.h>

// dinput.h��ǂݍ��ޑO�ɐ錾���Ȃ���΂Ȃ�Ȃ�
#ifndef DIRECTINPUT_VERSION
	#define	DIRECTINPUT_VERSION	0x0800
#endif
#include <dinput.h>

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{

typedef unsigned char				U_CHAR;
typedef unsigned short				U_SHORT;
typedef unsigned int				U_INT;
typedef unsigned long				U_LONG;

} // iruna end


#endif // IRUNA_TYPES_H