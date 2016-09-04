//*********************************************************************
/*!
	@file	iruna_release.h
	@brief	����֐�
	@author	���� �Ė�
	@date	2011/06/22	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_RELEASE_H
#define IRUNA_RELEASE_H

/*----�֐� ��`----------------------------------------------------*/
namespace iruna
{

//!--------------------------------------------------------------------
//! 
//! @brief	COM��Release���Ăяo���A���S�Ƀ����[�X����
//! @param	[in] instance	- �C���X�^���X
//! 
//!--------------------------------------------------------------------
template< class T >
inline void SafeRelease( T& instance )
{
	if( instance )
		instance->Release();

	instance	= 0;

	return;
}

//!--------------------------------------------------------------------
//! 
//! @brief	�C���X�^���X�����S�ɉ������
//! @param	[in] instance	- �C���X�^���X
//! 
//!--------------------------------------------------------------------
template< class T >
inline void SafeDelete( T& instance )
{
	delete instance;
	instance	= 0;

	return;
}

//!--------------------------------------------------------------------
//! 
//! @brief	�C���X�^���X�����S�ɉ������(�z���)
//! @param	[in] instance	- �C���X�^���X
//! 
//!--------------------------------------------------------------------
template< class T >
inline void SafeArrayDelete( T& instance )
{
	delete[] instance;
	instance	= 0;

	return;
}

}	//	iruna end
#endif	//	IRUNA_RELEASE_H	end