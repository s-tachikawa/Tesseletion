//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Source/iruna_physics_core.h"
//#include "../Include/iruna_physics_rigid_box.h"
//
///*----�f�[�^�^�錾-------------------------------------------------*/
//namespace iruna
//{
//namespace physics
//{
////	�R���X�g���N�^
//RigidBox::RigidBox( BoxParameter& parameter )
//{
//	btVector3		localInertia( 0.0f, 0.0f, 0.0f );
//	btTransform		temp;
//
//	//	�w�肵���ʒu�̍s����쐬
//	temp.setIdentity();
//	temp.setOrigin( btVector3( parameter.pos.x, parameter.pos.y, parameter.pos.z ) );
//
//	//	�w�肵�����a�̃p�����[�^�[����{�b�N�X���쐬
//	collisionShape = new btBoxShape(
//		btVector3(	parameter.halfSize.x,
//					parameter.halfSize.y,
//					parameter.halfSize.z )
//	);
//
//	//	���̈ʒu���쐬
//	motionState = new btDefaultMotionState( temp );
//
//	//	�d����ݒ�H
//	collisionShape->calculateLocalInertia( parameter.weight, localInertia );
//
//	//	�ݒ肵���p�����[�^���獄�̍쐬
//	rigidBody = new btRigidBody(
//		parameter.weight,
//		motionState,
//		collisionShape,
//		localInertia
//	);
//
//	//	�����G���W���K�p�G���A�ɓo�^
//	PhysicsCore::GetDynamicsWorld()->addRigidBody( rigidBody );
//	return;
//}
//
////	�f�X�g���N�^
//RigidBox::~RigidBox()
//{
//	PhysicsCore::GetDynamicsWorld()->removeRigidBody( rigidBody );
//
//	SafeDelete( rigidBody );
//	SafeDelete( collisionShape );
//	SafeDelete( motionState );
//
//	return;
//}
//
////	���[���h�s��̎擾
//void RigidBox::GetMatrix( float* dst ) const
//{
//	const btTransform&		matrix		= rigidBody->getWorldTransform();
//
//	matrix.getOpenGLMatrix( dst );
//
//	return;
//}
//
////	�^���x�N�g����ݒ�
//void RigidBox::SetForce( const math::Vector3& force )
//{
//	rigidBody->applyCentralForce( btVector3( force.x, force.y, force.z ) );
//
//	return;
//}
//
////	�^���x�N�g���ƈʒu��ݒ�
//void RigidBox::SetForce( const math::Vector3& force, const math::Vector3& pos )
//{
//	rigidBody->applyForce(
//		btVector3( force.x, force.y, force.z ),
//		btVector3( pos.x, pos.y, pos.z )
//	);
//
//	return;
//}
//
////	��]�x�N�g����ݒ�
//void RigidBox::SetTorque( const math::Vector3& torque )
//{
//	rigidBody->applyTorque( btVector3( torque.x, torque.y, torque.z ) );
//
//	return;
//}
//
//}	//	physics end
//}	//	iruna end
