//---------------------------------------------------------
// 
//	iruna_math_function.cpp
//	数学機能
//	作成日 11月13日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_math_function.h"

namespace iruna
{
namespace math
{
/*----グローバル関数宣言-------------------------------------------------*/


//	3次元ベクトルの外積を求める
Vector3	Cross( Vector3 vec1, Vector3 vec2 )
{
	return Vector3( ( vec1.y * vec2.z ) - ( vec1.z * vec2.y ),
					( vec1.z * vec2.x ) - ( vec1.x * vec2.z ),
					( vec1.x * vec2.y ) - ( vec1.y * vec2.x ) );
}

//	3次元ベクトルの外積を求める
float	Cross( Vector2 vec1, Vector2 vec2 )
{
	return ( vec1.x * vec2.x ) + ( vec1.y * vec2.y );
}

//	3次元ベクトルの内積を求める
float	Dot( Vector3 vec1, Vector3 vec2  )
{
	return ( vec1.x * vec2.x ) + ( vec1.y * vec2.y ) + ( vec1.z * vec2.z );
}

//	3次元ベクトルの2乗の長さを求める
float	LengthSqrt( Vector3 vec )
{
	return Dot( vec, vec );
}

//	3次元ベクトルの長さを求める
float	Length( Vector3 vec )
{
	return sqrt( LengthSqrt( vec ) );
}
//	3次元ベクトルを正規化する
Vector3 Normalize( Vector3 vec )
{
	float	len	= Length( vec );

	if( 0 == len )
		return  Vector3( 0, 0, 0 );

	return Vector3( ( vec.x / len ),
					( vec.y / len ),
					( vec.z / len ) );
}

//	指定した位置とベクトル,時間でエルミネートスプライン曲線補間する
Vector3 HermiteLerp( Vector3 pos1, Vector3 pos2, Vector3 vec1, Vector3 vec2, float time )
{
	Vector3 temp1 = ( ( ( time - 1 ) * ( time - 1 ) ) * ( 2 * time + 1 ) * pos1 );
	Vector3 temp2 = ( ( time * time ) * ( 3 - 2 * time ) * pos2 );
	Vector3 temp3 = ( ( 1 - ( time * time ) ) * time * vec1 );
	Vector3 temp4 = ( ( time - 1 ) * ( time * time ) * vec2 );

	return temp1 + temp2 + temp3 + temp4;
}

//	指定したベクトルとベクトルを線形補間する
Vector3 Lerp( Vector3 vec1,Vector3 vec2, float time )
{
	return vec1 + time * ( vec2 - vec1 );

}

//	指定した行列と行列の線形補間する
Matrix	MatrixInterp( Matrix mat1, Matrix mat2, float time )
{
	return mat1 + time * ( mat2 - mat1 );
}
 
//	指定したベクトルとベクトルを球面線形補間する
Vector3 SphereLinear(  Vector3 vec1,Vector3 vec2, float time )
{
   Vector3 s, e, out;

   s = Normalize( vec1 );
   e = Normalize( vec2 );


   // 2ベクトル間の角度（鋭角側）
   float angle = acos( Dot( s, e ) );

   // sinθ
   float SinTh = sin( angle );

   // 補間係数
   float Ps = sin( angle * ( 1 - time ) );
   float Pe = sin( angle * time );

   out = ( Ps * s + Pe * e ) / SinTh;

   // 一応正規化して球面線形補間に
  out =  Normalize( out );

   return out;
}
 
//	指定した行列と行列を球面線形補間で補間姿勢を求める
Matrix CalcInterPause(  Matrix mat1,Matrix mat2, float time )
{
	Matrix out;
	// 各姿勢ベクトル抽出
	Vector3 Sy, Sz;
	Vector3 Ey, Ez;

   memcpy( &Sy, mat1.m[1], sizeof( float ) * 3 );
   memcpy( &Sz, mat1.m[2], sizeof( float ) * 3 );
   memcpy( &Ey, mat2.m[1], sizeof( float ) * 3 );
   memcpy( &Ez, mat2.m[2], sizeof( float ) * 3 );

   // 中間ベクトル算出
   Vector3 IY, IZ;
   IY = SphereLinear( Sy, Ey, time );
   IZ = SphereLinear( Sz, Ez, time );

   // 中間ベクトルから姿勢ベクトルを再算出
   Vector3 IX;
   IX = Cross( IY, IZ );
   IY = Cross( IZ, IX );
   IX = Normalize( IX );
   IY = Normalize( IY );
   IZ = Normalize( IZ );

   memset( out, 0, sizeof( Matrix ) );
   memcpy( out.m[0], &IX, sizeof( float ) * 3 );
   memcpy( out.m[1], &IY, sizeof( float ) * 3 );
   memcpy( out.m[2], &IZ, sizeof( float ) * 3 );
   out._44 = 1.0f;

   return out;
}

}	//	math	end
}	//	iruna	end