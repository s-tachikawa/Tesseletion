//
///*----インクルード-------------------------------------------------*/
//#include "../Source/iruna_physics_core.h"
//#include "../Include/iruna_physics_rigid_box.h"
//
///*----データ型宣言-------------------------------------------------*/
//namespace iruna
//{
//namespace physics
//{
////	コンストラクタ
//RigidBox::RigidBox( BoxParameter& parameter )
//{
//	btVector3		localInertia( 0.0f, 0.0f, 0.0f );
//	btTransform		temp;
//
//	//	指定した位置の行列を作成
//	temp.setIdentity();
//	temp.setOrigin( btVector3( parameter.pos.x, parameter.pos.y, parameter.pos.z ) );
//
//	//	指定した半径のパラメーターからボックスを作成
//	collisionShape = new btBoxShape(
//		btVector3(	parameter.halfSize.x,
//					parameter.halfSize.y,
//					parameter.halfSize.z )
//	);
//
//	//	剛体位置を作成
//	motionState = new btDefaultMotionState( temp );
//
//	//	重さを設定？
//	collisionShape->calculateLocalInertia( parameter.weight, localInertia );
//
//	//	設定したパラメータから剛体作成
//	rigidBody = new btRigidBody(
//		parameter.weight,
//		motionState,
//		collisionShape,
//		localInertia
//	);
//
//	//	物理エンジン適用エリアに登録
//	PhysicsCore::GetDynamicsWorld()->addRigidBody( rigidBody );
//	return;
//}
//
////	デストラクタ
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
////	ワールド行列の取得
//void RigidBox::GetMatrix( float* dst ) const
//{
//	const btTransform&		matrix		= rigidBody->getWorldTransform();
//
//	matrix.getOpenGLMatrix( dst );
//
//	return;
//}
//
////	運動ベクトルを設定
//void RigidBox::SetForce( const math::Vector3& force )
//{
//	rigidBody->applyCentralForce( btVector3( force.x, force.y, force.z ) );
//
//	return;
//}
//
////	運動ベクトルと位置を設定
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
////	回転ベクトルを設定
//void RigidBox::SetTorque( const math::Vector3& torque )
//{
//	rigidBody->applyTorque( btVector3( torque.x, torque.y, torque.z ) );
//
//	return;
//}
//
//}	//	physics end
//}	//	iruna end
