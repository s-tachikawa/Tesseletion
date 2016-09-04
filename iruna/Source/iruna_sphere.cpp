//---------------------------------------------------------
// 
//	iruna_sphere.cpp
//	�����蔻��p��
//	�쐬�� 11��13��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_sphere.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace geometry
{
//	�R���X�g���N�^
Sphere::Sphere()
{
	memset( this, 0, sizeof( *this ) );
	return;
}
//	�R���X�g���N�^
Sphere::Sphere(  math::Vector3 setOrigin, float setRadius )
	: origin( setOrigin ),
	  radius( setRadius )
{
	return;
}

//	�f�X�g���N�^
Sphere::~Sphere()
{
	return;
}

}	//	geometry	end
}	//	iruna		end