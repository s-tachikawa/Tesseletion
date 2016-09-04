//*********************************************************************
/*!
	@file	iruna_debug.h
	@brief	�f�o�b�O�p�Ȃ�
	@author	���� �Ė�
	@date	2011/06/22	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_DEBUG_H
#define IRUNA_DEBUG_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_types.h"

/*----�֐� ��`----------------------------------------------------*/
namespace iruna
{

//!--------------------------------------------------------------------
//! 
//! @brief	�f�o�b�O�E�B���h�E�ɕ����Ɛ��l���o�͂���(�f�o�b�O���̂ݗL��)
//! @param	[in] str	- �o�͂��镶����
//! @param	[in] ...	- �Ԃ����݂������l
//! 
//!--------------------------------------------------------------------
inline void DrawDebugFormatString( LPCSTR str, ... )
{
	va_list		list;
	char		temp[ 256 ];

	va_start( list, str );
	vsprintf_s( temp, 256, str, list );
	va_end( list );
	
	OutputDebugString( temp );

	return;
}

}	// iruna	end
#endif	// IRUNA_DEBUG_H	end