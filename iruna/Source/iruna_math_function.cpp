//---------------------------------------------------------
// 
//	iruna_math_function.cpp
//	���w�@�\
//	�쐬�� 11��13��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_math_function.h"

namespace iruna
{
namespace math
{
/*----�O���[�o���֐��錾-------------------------------------------------*/


//	3�����x�N�g���̊O�ς����߂�
Vector3	Cross( Vector3 vec1, Vector3 vec2 )
{
	return Vector3( ( vec1.y * vec2.z ) - ( vec1.z * vec2.y ),
					( vec1.z * vec2.x ) - ( vec1.x * vec2.z ),
					( vec1.x * vec2.y ) - ( vec1.y * vec2.x ) );
}

//	3�����x�N�g���̊O�ς����߂�
float	Cross( Vector2 vec1, Vector2 vec2 )
{
	return ( vec1.x * vec2.x ) + ( vec1.y * vec2.y );
}

//	3�����x�N�g���̓��ς����߂�
float	Dot( Vector3 vec1, Vector3 vec2  )
{
	return ( vec1.x * vec2.x ) + ( vec1.y * vec2.y ) + ( vec1.z * vec2.z );
}

//	3�����x�N�g����2��̒��������߂�
float	LengthSqrt( Vector3 vec )
{
	return Dot( vec, vec );
}

//	3�����x�N�g���̒��������߂�
float	Length( Vector3 vec )
{
	return sqrt( LengthSqrt( vec ) );
}
//	3�����x�N�g���𐳋K������
Vector3 Normalize( Vector3 vec )
{
	float	len	= Length( vec );

	if( 0 == len )
		return  Vector3( 0, 0, 0 );

	return Vector3( ( vec.x / len ),
					( vec.y / len ),
					( vec.z / len ) );
}

//	�w�肵���ʒu�ƃx�N�g��,���ԂŃG���~�l�[�g�X�v���C���Ȑ���Ԃ���
Vector3 HermiteLerp( Vector3 pos1, Vector3 pos2, Vector3 vec1, Vector3 vec2, float time )
{
	Vector3 temp1 = ( ( ( time - 1 ) * ( time - 1 ) ) * ( 2 * time + 1 ) * pos1 );
	Vector3 temp2 = ( ( time * time ) * ( 3 - 2 * time ) * pos2 );
	Vector3 temp3 = ( ( 1 - ( time * time ) ) * time * vec1 );
	Vector3 temp4 = ( ( time - 1 ) * ( time * time ) * vec2 );

	return temp1 + temp2 + temp3 + temp4;
}

//	�w�肵���x�N�g���ƃx�N�g������`��Ԃ���
Vector3 Lerp( Vector3 vec1,Vector3 vec2, float time )
{
	return vec1 + time * ( vec2 - vec1 );

}

//	�w�肵���s��ƍs��̐��`��Ԃ���
Matrix	MatrixInterp( Matrix mat1, Matrix mat2, float time )
{
	return mat1 + time * ( mat2 - mat1 );
}
 
//	�w�肵���x�N�g���ƃx�N�g�������ʐ��`��Ԃ���
Vector3 SphereLinear(  Vector3 vec1,Vector3 vec2, float time )
{
   Vector3 s, e, out;

   s = Normalize( vec1 );
   e = Normalize( vec2 );


   // 2�x�N�g���Ԃ̊p�x�i�s�p���j
   float angle = acos( Dot( s, e ) );

   // sin��
   float SinTh = sin( angle );

   // ��ԌW��
   float Ps = sin( angle * ( 1 - time ) );
   float Pe = sin( angle * time );

   out = ( Ps * s + Pe * e ) / SinTh;

   // �ꉞ���K�����ċ��ʐ��`��Ԃ�
  out =  Normalize( out );

   return out;
}
 
//	�w�肵���s��ƍs������ʐ��`��Ԃŕ�Ԏp�������߂�
Matrix CalcInterPause(  Matrix mat1,Matrix mat2, float time )
{
	Matrix out;
	// �e�p���x�N�g�����o
	Vector3 Sy, Sz;
	Vector3 Ey, Ez;

   memcpy( &Sy, mat1.m[1], sizeof( float ) * 3 );
   memcpy( &Sz, mat1.m[2], sizeof( float ) * 3 );
   memcpy( &Ey, mat2.m[1], sizeof( float ) * 3 );
   memcpy( &Ez, mat2.m[2], sizeof( float ) * 3 );

   // ���ԃx�N�g���Z�o
   Vector3 IY, IZ;
   IY = SphereLinear( Sy, Ey, time );
   IZ = SphereLinear( Sz, Ez, time );

   // ���ԃx�N�g������p���x�N�g�����ĎZ�o
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