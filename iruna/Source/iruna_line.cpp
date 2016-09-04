//---------------------------------------------------------
// 
//	iruna_line.cpp
//	�����蔻��p����
//	�쐬�� 11��13��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_line.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace geometry
{
//	�R���X�g���N�^
Line::Line()
{
	memset( this, 0, sizeof( *this ) );
	return;
}

//	�R���X�g���N�^(�w�肵�č쐬����)
Line::Line( math::Vector3 setOrigin, math::Vector3 setNormal )
	: origin( setOrigin ),
	  normal( setNormal )
{
	return;
}
Line::~Line()
{
	return;
}

}	//	geometry	end
}	//	iruna		end
