//*********************************************************************
/*!
	@file	white_debug_drawing.h
	@brief	3D当たり判定のデバック用モデル生成構造体群
	@author	立川 翔野
	@date	2011/11/13	- 作成
*/
//*********************************************************************
/*----多重インクルード防止-------------------------------------------------*/
#ifndef IRUNA_DEBUG_GEOMETRY_H
#define IRUNA_DEBUG_GEOMETRY_H


/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_vector3.h"
#include "../Include/iruna_color4.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{

// 前方宣言
namespace graphics
{

class VertexBuffer;

}	// graphics	end


namespace geometry
{
struct Aabb;
struct Sphere;
struct Line;
struct Segment;

//!=====================================================================
//!
//! @struct	DebugVertex
//! @brief	当たり判定デバッグ表示用の頂点バッファ用データ構造体
//!
//!=====================================================================
struct DebugVertex
{
	
	math::Vector3		pos;	//!<	頂点座標
	graphics::Color4	color;	//!<	頂点色
};


//!=====================================================================
//!
//! @struct	DebugGeometry
//! @brief	当たり判定デバッグ表示用の頂点データ構造体
//!
//!=====================================================================
struct DebugGeometry
{
//	パブリックメンバ変数
public:
	UINT			count;	//!<	頂点数
	DebugVertex*	data;	//!<	頂点データ

//	パブリックメンバ関数
public:
	DebugGeometry()
	{
		data = NULL;
		count = 0;
	}

};

/*----グローバル関数宣言------------------------------------------------*/

//!--------------------------------------------------------------------
//! 
//! @brief	指定したジオメトリのVertexDataを作成する
//! @param	[in]	aabb		- 表示したいAabb
//! @param	[inout] data		- 作成したジオメトリーデータ
//! @param	[in]	color		- 表示するジオメトリーの色(デフォルトは白色)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Aabb& aabb,		DebugGeometry* data, graphics::Color4 color = 0xffffffff );

//!--------------------------------------------------------------------
//! 
//! @brief	コンストラクタ(Sphereで頂点データを作成)
//! @param	[in]	sphere		- 表示したいSphere
//! @param	[inout] data		- 作成したジオメトリーデータ
//! @param	[in]	color		- 表示するSPHEREの色(デフォルトは白色)
//! @param	[in]	slices		- SPHEREの縦の分割数(デフォルトは16)
//! @param	[in]	stacks		- SPHEREの横の分割数(デフォルトは10)
//! @param	[in]	color		- 表示するジオメトリーの色(デフォルトは白色)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Sphere& sphere,	DebugGeometry* data, UINT slices = 16, UINT stacks = 10, graphics::Color4 color = 0xffffffff );

//!--------------------------------------------------------------------
//! 
//! @brief	指定したジオメトリのVertexDataを作成する
//! @param	[in]	line		- 表示したいLine
//! @param	[inout] data		- 作成したジオメトリーデータ
//! @param	[in]	color		- 表示するジオメトリーの色(デフォルトは白色)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Line& line,		DebugGeometry* data, graphics::Color4 color = 0xffffffff );

//!--------------------------------------------------------------------
//! 
//! @brief	指定したジオメトリのVertexDataを作成する
//! @param	[in]	segment		- 表示したいSegment
//! @param	[inout] data		- 作成したジオメトリーデータ
//! @param	[in]	color		- 表示するジオメトリーの色(デフォルトは白色)
//! 
//!--------------------------------------------------------------------
void CreateGeonetry( const Segment& segment,DebugGeometry* data, graphics::Color4 color = 0xffffffff );



}	//	geometry	end
}	//	iruna		end


#endif	//	IRUNA_DEBUG_GEOMETRY_H	end