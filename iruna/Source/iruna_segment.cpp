//---------------------------------------------------------
// 
//	iruna_segment.cpp
//	当たり判定用線分
//	作成日 11月13日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_segment.h"
/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace geometry
{

//	コストラクタ
Segment::Segment()
{
	memset( this, 0, sizeof( *this ) );
	return;
}

//	コンストラクタ(指定して作成)
Segment::Segment( math::Vector3 startPos, math::Vector3 endPos )
	:	strat( startPos ),
		end( endPos )
{
	return;
}

//	デストラクタ
Segment::~Segment()
{
	return;
}

}	//	geometry	end
}	//	iruna		end