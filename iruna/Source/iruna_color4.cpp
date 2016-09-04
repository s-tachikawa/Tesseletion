//---------------------------------------------------------
// 
//	iruna_color4.cpp
//	RGBA�̐F�֌W������
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_color4.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// Color4 Union
// �R���X�g���N�^(U_LONG�ŏ���������^�C�v)
Color4::Color4( U_LONG setColor )
	: color( setColor )
{
	return;
}

// �R���X�g���N�^(U_CHAR�~4�ŏ���������^�C�v)
Color4::Color4( U_CHAR r, U_CHAR g, U_CHAR b, U_CHAR a )
{
	channel[ ColorChannel::RED	 ]	= r;
	channel[ ColorChannel::GREEN ]	= g;
	channel[ ColorChannel::BLUE	 ]	= b;
	channel[ ColorChannel::ALPHA ]	= a;

	return;
}

// Color4F Struct
// �R���X�g���N�^(�S��0�ŏ���������^�C�v)
Color4F::Color4F()
	: r( 0.f ),
	  g( 0.f ),
	  b( 0.f ),
	  a( 0.f )
{
	return;
}

// �R���X�g���N�^(D3DCOLORVALUE�ŏ���������^�C�v)
Color4F::Color4F( D3DCOLORVALUE colorValue )
	: r( colorValue.r ),
	  g( colorValue.g ),
	  b( colorValue.b ),
	  a( colorValue.a )
{
	return;
}

// �R���X�g���N�^(����w�肵�ď���������^�C�v)
Color4F::Color4F( float setR, float setG, float setB, float setA )
	: r( setR ),
	  g( setG ),
	  b( setB ),
	  a( setA )
{
	return;
}

}	//	graphics	end
}	//	iruna		end