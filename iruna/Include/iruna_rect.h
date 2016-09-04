//*********************************************************************
/*!
	@file	iruna_rect.h
	@brief	��`�֘A
	@author	���� �Ė�
	@date	2011/06/24	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_RECT_H
#define IRUNA_RECT_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace math
{

//!=====================================================================
//!
//! @struct	Rect
//! @brief	
//!
//!=====================================================================
struct Rect
{
	int		left;
	int		top;
	int		right;
	int		bottom;

	Rect( int setLeft = 0, int setTop = 0, int setRight = 0, int setBottom = 0 )
		: left( setLeft ), top( setTop ), right( setRight ), bottom( setBottom ) {}
};

//!=====================================================================
//!
//! @struct	RectF
//! @brief	
//!
//!=====================================================================
struct RectF
{
	float	left;
	float	top;
	float	right;
	float	bottom;

		RectF( float setLeft = 0, float setTop = 0, float setRight = 0, float setBottom = 0 )
		: left( setLeft ), top( setTop ), right( setRight ), bottom( setBottom ) {}
};

}	//	math	end
}	//	iruna	end

#endif	//	IRUNA_RECT_H	end
