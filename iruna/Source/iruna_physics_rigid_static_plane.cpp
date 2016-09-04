//
///*----インクルード-------------------------------------------------*/
//#include "../Source/iruna_physics_core.h"
//#include "../Include/iruna_physics_rigid_static_plane.h"
//
///*----データ型宣言-------------------------------------------------*/
//namespace iruna
//{
//namespace physics
//{
//
////	コンストラクタ
//StaticPlane::StaticPlane( PlaneParameter& parameter )
//{
//
//	btVector3		localInertia( 0.0f, 0.0f, 0.0f );
//	btTransform		temp;
//
//	temp.setIdentity();
//	temp.setOrigin( btVector3( 0, 0, 0 ) );
//	temp.setRotation( btQuaternion( parameter.rotate.x, parameter.rotate.y, parameter.rotate.z ) );
//
//	collisionShape	= new btStaticPlaneShape(
//		btVector3( 0.0f, 1.0f, 0.0f ),
//		0
//	);
//
//	
//	
//
//	collisionShape->calculateLocalInertia( 0.0f, localInertia );
//
//	motionState		= new btDefaultMotionState( temp );
//	rigidBody		= new btRigidBody( 0.0f, motionState, collisionShape, localInertia );
//	
//	
//	
//	PhysicsCore::GetDynamicsWorld()->addRigidBody( rigidBody );
//	return;
//}
//
////	デストラクタ
//StaticPlane::~StaticPlane()
//{
//	PhysicsCore::GetDynamicsWorld()->removeRigidBody( rigidBody );
//
//	SafeDelete( rigidBody );
//	SafeDelete( collisionShape );
//	SafeDelete( motionState );
//	return;
//}
//
////	ワールド行列の取得
//void StaticPlane::GetMatrix( float* dst ) const
//{
//	const btTransform&		matrix		= rigidBody->getWorldTransform();
//
//	matrix.getOpenGLMatrix( dst );
//
//	return;
//}
//
////	運動ベクトルを設定
//void StaticPlane::SetForce( const math::Vector3& force )
//{
//	rigidBody->applyCentralForce( btVector3( force.x, force.y, force.z ) );
//
//	return;
//}
//
////	運動ベクトルと位置を設定
//void StaticPlane::SetForce( const math::Vector3& force, const math::Vector3& pos )
//{
//	rigidBody->applyForce(
//		btVector3( force.x, force.y, force.z ),
//		btVector3( pos.x, pos.y, pos.z )
//	);
//
//	return;
//}
//
////	回転ベクトルを設定
//void StaticPlane::SetTorque( const math::Vector3& torque )
//{
//	rigidBody->applyTorque( btVector3( torque.x, torque.y, torque.z ) );
//
//	return;
//}
//
//}	//	physics end
//}	//	iruna end