//---------------------------------------------------------
// 
//	iruna_line.cpp
//	当たり判定用線分
//	作成日 11月13日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_line.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace geometry
{
//	コンストラクタ
Line::Line()
{
	memset( this, 0, sizeof( *this ) );
	return;
}

//	コンストラクタ(指定して作成する)
Line::Line( math::Vector3 setOrigin, math::Vector3 setNormal )
	: origin( setOrigin ),
	  normal( setNormal )
{
	return;
}
Line::~Line()
{
	return;
}

}	//	geometry	end
}	//	iruna		end
