//---------------------------------------------------------
// 
//	iruna_debug_geometry.h
//	デバッグ用ジオメトリーの生成
//	作成日 11月13日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_debug_geometry.h"
#include "../Include/iruna_aabb.h"
#include "../Include/iruna_line.h"
#include "../Include/iruna_sphere.h"
#include "../Include/iruna_segment.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace geometry
{

//	Aabbからジオメトリの作成
void CreateGeonetry( const Aabb& aabb,		DebugGeometry* data, graphics::Color4 color )
{
	data->count = 36;
	if( data->data == NULL )
		data->data = new DebugVertex[ data->count ];

	math::Vector3	vertex[ 8 ] = {
		math::Vector3( aabb.min.x, aabb.max.y, aabb.min.z ),
		math::Vector3( aabb.max.x, aabb.max.y, aabb.min.z ),
		math::Vector3( aabb.min.x, aabb.min.y, aabb.min.z ),
		math::Vector3( aabb.max.x, aabb.min.y, aabb.min.z ),
		math::Vector3( aabb.max.x, aabb.max.y, aabb.max.z ),
		math::Vector3( aabb.min.x, aabb.max.y, aabb.max.z ),
		math::Vector3( aabb.max.x, aabb.min.y, aabb.max.z ),
		math::Vector3( aabb.min.x, aabb.min.y, aabb.max.z ),
	};

	DebugVertex	temp[] = {
		// 前面
		{ vertex[ 0 ], color },	{ vertex[ 1 ], color },	{ vertex[ 2 ], color },
		{ vertex[ 1 ], color },	{ vertex[ 3 ], color },	{ vertex[ 2 ], color },

		// 右面
		{ vertex[ 1 ], color },	{ vertex[ 4 ], color },	{ vertex[ 3 ], color },
		{ vertex[ 4 ], color },	{ vertex[ 6 ], color },	{ vertex[ 3 ], color },

		// 背面
		{ vertex[ 4 ], color },	{ vertex[ 5 ], color },	{ vertex[ 6 ], color },
		{ vertex[ 5 ], color },	{ vertex[ 7 ], color },	{ vertex[ 6 ], color },

		// 左面
		{ vertex[ 5 ], color },	{ vertex[ 0 ], color },	{ vertex[ 7 ], color },
		{ vertex[ 0 ], color },	{ vertex[ 2 ], color },	{ vertex[ 7 ], color },

		// 上面
		{ vertex[ 5 ], color },	{ vertex[ 4 ], color },	{ vertex[ 0 ], color },
		{ vertex[ 4 ], color },	{ vertex[ 1 ], color },	{ vertex[ 0 ], color },

		// 下面
		{ vertex[ 6 ], color },	{ vertex[ 7 ], color },	{ vertex[ 2 ], color },
		{ vertex[ 6 ], color },	{ vertex[ 3 ], color },	{ vertex[ 2 ], color },
	};

	memcpy( data->data, temp, sizeof( DebugVertex ) * data->count );

	return;
}

//	球からジオメトリの作成
void CreateGeonetry( const Sphere& sphere,	DebugGeometry* data, UINT slices, UINT stacks, graphics::Color4 color )
{
	int		num = ( stacks - 1 ) * 6;
	float	add_rot_xy = D3DX_PI / stacks;
	float	add_rot_xz = ( 2.0f * D3DX_PI ) / slices;
	float	rot_xz = 0;

	if( data->count != static_cast< int >( slices * num ) )
	{
		data->count	 = slices * num;
		data->data = new DebugVertex[ data->count ];
	}

	for( UINT i = 0; i < slices; i++ )
	{
		int		count = 0;
		float	rot_xy = 0;

		data->data[ i * num + count ].pos = sphere.origin + math::Vector3( sphere.radius * sinf( rot_xy ) * cosf( rot_xz ),
														  sphere.radius * cosf( rot_xy ),
														  sphere.radius * sinf( rot_xy ) * sinf( rot_xz ) );
		data->data[ i * num + count ].color = color;

		count++;

		while( num > count )
		{
			if( 3 <= count )
			{
				data->data[ i * num + count ] = data->data[ i * num + count - 2 ];
				count++;
				data->data[ i * num + count ] = data->data[ i * num + count - 2 ];
				count++;
			}

			// 奇数なら
			if( 1 == count % 2 )
			{
				rot_xy += add_rot_xy;

				data->data[ i * num + count ].pos = sphere.origin + math::Vector3( sphere.radius * sinf( rot_xy ) * cosf( rot_xz ),
																  sphere.radius * cosf( rot_xy ),
																  sphere.radius * sinf( rot_xy ) * sinf( rot_xz ) );
				data->data[ i * num + count ].color = color;
			}
			else
			{
				data->data[ i * num + count ].pos = sphere.origin + math::Vector3( sphere.radius * sinf( rot_xy ) * cosf( rot_xz + add_rot_xz ),
																  sphere.radius * cosf( rot_xy ),
																  sphere.radius * sinf( rot_xy ) * sinf( rot_xz + add_rot_xz ) );
				data->data[ i * num + count ].color = color;
			}

			count++;
		}

		rot_xz += add_rot_xz;
	}

	return;
}

//	ラインからジオメトリの作成
void CreateGeonetry( const Line& line,		DebugGeometry* data, graphics::Color4 color )
{
	if( NULL == data->data )
		data->data = new DebugVertex[ data->count ];

	data->data[ 0 ].pos		= line.origin;
	data->data[ 0 ].color	= color;

	data->data[ 1 ].pos		= line.origin + ( line.normal * 50 );
	data->data[ 1 ].color	= color;
	return;
}

//	線分からジオメトリの作成
void CreateGeonetry( const Segment& segment,DebugGeometry* data, graphics::Color4 color )
{
	if( NULL == data->data )
		data->data = new DebugVertex[ data->count ];

	data->data[ 0 ].pos		= segment.strat;
	data->data[ 0 ].color	= color;

	data->data[ 1 ].pos		= segment.end;
	data->data[ 1 ].color	= color;
	return;
}
}	//	geometry	end
}	//	iruna		end