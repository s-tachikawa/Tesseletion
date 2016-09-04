//---------------------------------------------------------
// 
//	iruna_aabb.cpp
//	�����蔻��p�����s���E�{�b�N�X( Axis-Aligned Bounding Box )
//	�쐬�� 11��13��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_aabb.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace geometry
{
//	�R���X�g���N�^
Aabb::Aabb()
{
	memset( this, 0, sizeof( *this ) );
	return;
}

//	�R���X�g���N�^(�w�肵�č쐬����)
Aabb::Aabb( math::Vector3 setOrigin, math::Vector3 setHalfWidths )
{
	min	= setOrigin - setHalfWidths;
	max	= setOrigin + setHalfWidths;
	return;
}

//	�f�X�g���N�^
Aabb::~Aabb()
{
	return;
}

//	���S�_��ݒ�
void Aabb::SetOrigin( math::Vector3 setOrigin )
{

	math::Vector3	halfWidths = GetHalfWidths();

	min	= setOrigin - halfWidths;
	max	= setOrigin + halfWidths;

	return;
}

//	���a�̐ݒ�
void Aabb::SetHalfWidths( math::Vector3 setHalfWidths )
{

	math::Vector3	origin = GetOrigin();

	min	= origin - setHalfWidths;
	max	= origin + setHalfWidths;

	return;
}

//	���S�_���擾����
math::Vector3 Aabb::GetOrigin() const
{
	math::Vector3	halfWidths = GetHalfWidths();

	return ( min + halfWidths );
}

//	�����擾����
math::Vector3 Aabb::GetHalfWidths() const
{
	return ( ( max - min ) / 2.f );
}

}	//	geometry	end
}	//	iruna		end