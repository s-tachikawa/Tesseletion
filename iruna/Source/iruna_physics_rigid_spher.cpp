//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Source/iruna_physics_core.h"
//#include "../Include/iruna_physics_rigid_spher.h"
//
///*----�f�[�^�^�錾-------------------------------------------------*/
//namespace iruna
//{
//namespace physics
//{
////	�R���X�g���N�^
//RigidSpher::RigidSpher( SpherParameter& parameter )
//{
//	btVector3		localInertia( 0.0f, 0.0f, 0.0f );
//	btTransform		temp;
//
//	temp.setIdentity();
//	temp.setOrigin( btVector3( parameter.pos.x, parameter.pos.y, parameter.pos.z ) );
//	temp.setRotation( btQuaternion( parameter.rotate.x, parameter.rotate.y, parameter.rotate.z ) );
//
//	collisionShape	= new btSphereShape( parameter.radius );
//	motionState		= new btDefaultMotionState( temp );
//
//	collisionShape->calculateLocalInertia( parameter.weight, localInertia );
//
//	rigidBody = new btRigidBody(
//		parameter.weight,
//		motionState,
//		collisionShape,
//		localInertia
//	);
//
//
//
//	PhysicsCore::GetDynamicsWorld()->addRigidBody( rigidBody );
//	return;
//}
//
////	�f�X�g���N�^
//RigidSpher::~RigidSpher()
//{
//	PhysicsCore::GetDynamicsWorld()->removeRigidBody( rigidBody );
//
//	SafeDelete( rigidBody );
//	SafeDelete( collisionShape );
//	SafeDelete( motionState );
//	return;
//}
//
////	���[���h�s��̎擾
//void RigidSpher::GetMatrix( float* dst ) const
//{
//	const btTransform&		matrix		= rigidBody->getWorldTransform();
//
//	matrix.getOpenGLMatrix( dst );
//
//	return;
//}
//
////	�^���x�N�g����ݒ�
//void RigidSpher::SetForce( const math::Vector3& force )
//{
//	rigidBody->applyCentralForce( btVector3( force.x, force.y, force.z ) );
//
//	return;
//}
//
////	�^���x�N�g���ƈʒu��ݒ�
//void RigidSpher::SetForce( const math::Vector3& force, const math::Vector3& pos )
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
//void RigidSpher::SetTorque( const math::Vector3& torque )
//{
//	rigidBody->applyTorque( btVector3( torque.x, torque.y, torque.z ) );
//
//	return;
//}
//
//}	//	physics	end
//}	//	iruna	end