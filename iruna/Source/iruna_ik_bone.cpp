
/*----�C���N���[�h---------------------------------*/
#include "../Include/iruna_ik_bone.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//	�R���X�g���N�^
IkBone::IkBone()
:	index( 0 ),
	targetIndex( 0 ),
	length( 0 ),
	iterations( 0 ),
	weight( 0.0f )

{
	return;
}

//	IK�{�[���̍X�V
void IkBone::IkUpdate( Bone* bone )
{
	math::Vector3 localEffectPos;
	math::Vector3 localTargetPos;
	for( int i = 0; i < iterations; ++i )
	{
		for( int k = 0; k < ( int )child.size(); ++k )
		{
			//	�e��������{�[���̔ԍ����擾
			int attentionIdx = child[ k ];
			//	IK�{�[����IK�{�[���̐ڑ���̃{�[�����W���擾
			math::Vector3 effectPos = math::Vector3( 0 ,0 ,0 );
			math::Vector3 targetPos = math::Vector3( 0 ,0 ,0 );

			if( bone[ targetIndex ].parentId != 0xFFFF )
				D3DXVec3TransformCoord( &effectPos, &effectPos, &bone[ targetIndex ].comb );
			else
				D3DXVec3TransformCoord( &effectPos, &effectPos, &bone[ targetIndex ].tran );
			
			if( bone[ index ].parentId != 0xFFFF)
				D3DXVec3TransformCoord( &targetPos, &targetPos, &bone[ index ].comb );
			else
				D3DXVec3TransformCoord( &targetPos, &targetPos, &bone[ index ].tran );

			//	�e��������
			math::Matrix invCoord;

			D3DXMatrixIdentity( &invCoord );
			D3DXMatrixInverse( &invCoord, 0, &bone[ attentionIdx ].comb );

			//	IK�Ɛڑ�����e����̃{�[���̑��΍��W�ɂ���
			D3DXVec3TransformCoord( &localEffectPos, &effectPos, &invCoord );
			D3DXVec3TransformCoord( &localTargetPos, &targetPos, &invCoord );

			//	�ڑ����IK�{�[���̊p�x�����߂�
			math::Vector3 effectDir;
			math::Vector3 targetDir;
			D3DXVec3Normalize( &effectDir, &localEffectPos );
			D3DXVec3Normalize( &targetDir, &localTargetPos );

			//	�{�[�����Ђ��������ꍇ�p�x����������(PMD�̏ꍇ)
			if( bone[ attentionIdx ].boneName.find( "�Ђ�" ) != std::string::npos )
			{
				effectDir = math::Vector3( 0, effectDir.y, effectDir.z );
				targetDir = math::Vector3( 0, targetDir.y, targetDir.z );
				D3DXVec3Normalize( &effectDir, &effectDir );
				D3DXVec3Normalize( &targetDir, &targetDir );
			}
			//	�p�x�����߂�
			float p = D3DXVec3Dot( &effectDir, &targetDir );
			
			// �v�Z�덷�ɂ��1���z�����acos()�����U����̂Œ���!
			if (p > 1 - 1.0e-5f) continue;

			float angle = acos( p );
			//	�e���x*4�ȏ�͋Ȃ���Ȃ�
			if( angle > 4 * weight ) angle = 4.0f * weight;
			
			math::Vector3 axis;
			D3DXVec3Cross(&axis, &effectDir, &targetDir);

			math::Matrix rot;

			D3DXMatrixRotationAxis( &rot, &axis, angle );
			if( bone[ attentionIdx ].boneName.find( "�Ђ�" ) != std::string::npos )
			{
				math::Matrix inv;
				D3DXMatrixInverse( &inv, 0, &bone[ attentionIdx ].init );

				math::Matrix def = rot * bone[ attentionIdx ].tran * inv;

				math::Vector3 t = math::Vector3( 0, 0, 1 );

				D3DXVec3TransformCoord( &t, &t, &def );

				if( t.y < 0 )
				{
					D3DXMatrixRotationAxis( &rot, &axis, -2.0f * angle );
				}

			}

			bone[ attentionIdx ].tran = rot * bone[ attentionIdx ].tran;

			//	���{�[�����X�V����
			math::WoldMatrix world;
			for( int i = 0; i < boneCount; i++ )
			{
				if( bone[ i ].parentId == 0xffff )
					bone[ i ].BoneUpDate( world.GetWoldMatrix() );
			}

			const float errToleranceSq = 0.000001f;

			if( D3DXVec3LengthSq( &( localEffectPos - localTargetPos ) ) < errToleranceSq )
			{
				return;
			}

		}
		
	}
	
	return;
}

}	//	graphics	end
}	//	iruna		end