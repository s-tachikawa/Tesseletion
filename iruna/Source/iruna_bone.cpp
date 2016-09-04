//---------------------------------------------------------
// 
//	iruna_bone.cpp
//	���f���{�[���Ǘ��N���X
//	�쐬�� 11��01��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
/*----�C���N���[�h---------------------------------*/
#include "../Include/iruna_bone.h"

/*----�l�[���X�y�[�X---------------------------------*/
namespace iruna
{
namespace graphics
{
// �R���X�g���N�^
Bone::Bone()
{
	// �s��̏�����
	D3DXMatrixIdentity( &init );
	D3DXMatrixIdentity( &offset );
	D3DXMatrixIdentity( &tran );
	D3DXMatrixIdentity( &comb );
	D3DXMatrixIdentity( &test );
	D3DXMatrixIdentity( &skin );

	id			= -1;
	parentId	= -1;
}

// �{�[���̑��΍��W��e�̑��΍��W�ɕς���
void Bone::BoneRun(iruna::math::Matrix* parentOffset)
{
	//�q�{�[��������Ȃ玩���̃I�t�Z�b�g�s���n����
	//�e�Ƃ̑��Ύp���ɒ����܂�
	for( int i = 0; i< (int)child.size();i++ )
		child[ i ]->BoneRun( &offset );

	//���[�g�{�[���͌v�Z���Ȃ�
	if( parentOffset )
		init *= *parentOffset;

	return;
}

// �{�[���̎p���X�V
void Bone::BoneUpDate( iruna::math::Matrix parent )
{
	D3DXMatrixIdentity( &skin );
	D3DXMatrixIdentity( &comb );
	//�ϊ��s��Ɛe�s�񂩂獇���s��̍쐬
	comb = (tran) * parent;
	
	//�q�{�[��������Ȃ�̎q�{�[���̍X�V	
	for( int i = 0; i <  (int)child.size(); i++)
		child[ i ]->BoneUpDate( comb );
		
	//�X�L�j���O�s��̍쐬
	skin = offset * comb;
		
	return;
}

// �{�[���̏����p���̐ݒ�(Matrix ver)
void Bone::SetInitMatrix( math::Matrix initMat )
{
	init = initMat;
	return;
}

//	�{�[���̏����p���̐ݒ�(Vector ver)
void Bone::SetInitMatrix( math::Vector3 bonePos )
{

	D3DXMatrixTranslation(	&init,
							bonePos.x,
							bonePos.y,
							bonePos.z
							);

	//	�����p������I�t�Z�b�g�s��𐶐�
	D3DXMatrixInverse( &offset, 0, &init );
	return;
}

}	//	graphics	end
}	//	iruna		end