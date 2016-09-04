//---------------------------------------------------------
// 
//	iruna_aabb.cpp
//	当たり判定用軸並行境界ボックス( Axis-Aligned Bounding Box )
//	作成日 11月13日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_aabb.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace geometry
{
//	コンストラクタ
Aabb::Aabb()
{
	memset( this, 0, sizeof( *this ) );
	return;
}

//	コンストラクタ(指定して作成する)
Aabb::Aabb( math::Vector3 setOrigin, math::Vector3 setHalfWidths )
{
	min	= setOrigin - setHalfWidths;
	max	= setOrigin + setHalfWidths;
	return;
}

//	デストラクタ
Aabb::~Aabb()
{
	return;
}

//	中心点を設定
void Aabb::SetOrigin( math::Vector3 setOrigin )
{

	math::Vector3	halfWidths = GetHalfWidths();

	min	= setOrigin - halfWidths;
	max	= setOrigin + halfWidths;

	return;
}

//	半径の設定
void Aabb::SetHalfWidths( math::Vector3 setHalfWidths )
{

	math::Vector3	origin = GetOrigin();

	min	= origin - setHalfWidths;
	max	= origin + setHalfWidths;

	return;
}

//	中心点を取得する
math::Vector3 Aabb::GetOrigin() const
{
	math::Vector3	halfWidths = GetHalfWidths();

	return ( min + halfWidths );
}

//	幅を取得する
math::Vector3 Aabb::GetHalfWidths() const
{
	return ( ( max - min ) / 2.f );
}

}	//	geometry	end
}	//	iruna		end