//---------------------------------------------------------
// 
//	iruna_sphere.cpp
//	当たり判定用球
//	作成日 11月13日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_sphere.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace geometry
{
//	コンストラクタ
Sphere::Sphere()
{
	memset( this, 0, sizeof( *this ) );
	return;
}
//	コンストラクタ
Sphere::Sphere(  math::Vector3 setOrigin, float setRadius )
	: origin( setOrigin ),
	  radius( setRadius )
{
	return;
}

//	デストラクタ
Sphere::~Sphere()
{
	return;
}

}	//	geometry	end
}	//	iruna		end