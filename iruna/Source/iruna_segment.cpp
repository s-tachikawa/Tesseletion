//---------------------------------------------------------
// 
//	iruna_segment.cpp
//	�����蔻��p����
//	�쐬�� 11��13��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_segment.h"
/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace geometry
{

//	�R�X�g���N�^
Segment::Segment()
{
	memset( this, 0, sizeof( *this ) );
	return;
}

//	�R���X�g���N�^(�w�肵�č쐬)
Segment::Segment( math::Vector3 startPos, math::Vector3 endPos )
	:	strat( startPos ),
		end( endPos )
{
	return;
}

//	�f�X�g���N�^
Segment::~Segment()
{
	return;
}

}	//	geometry	end
}	//	iruna		end