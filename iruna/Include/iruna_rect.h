//*********************************************************************
/*!
	@file	iruna_rect.h
	@brief	矩形関連
	@author	立川 翔野
	@date	2011/06/24	- 作成
*/
//*********************************************************************

/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_RECT_H
#define IRUNA_RECT_H

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----データ型 宣言------------------------------------------------*/
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
