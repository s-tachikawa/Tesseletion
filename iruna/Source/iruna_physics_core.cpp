//
///*----インクルード-------------------------------------------------*/
//#include "../Source/iruna_physics_core.h"
//
///*----データ型宣言-------------------------------------------------*/
//namespace iruna
//{
//namespace physics
//{
//
////	静的変数の初期化
//btDynamicsWorld*			PhysicsCore::world = NULL;
//btDispatcher*				PhysicsCore::dispatcher = NULL;
//btBroadphaseInterface*		PhysicsCore::sweep = NULL;
//btConstraintSolver*			PhysicsCore::solver = NULL;
//btCollisionConfiguration*	PhysicsCore::config = NULL;
//
////	コンストラクタ
//PhysicsCore::PhysicsCore()
//{
//	return;
//}
//
////	デストラクタ
//PhysicsCore::~PhysicsCore()
//{
//	PhysicsCoreRelese();
//	return;
//}
//
////	物理エンジンの初期化
//int PhysicsCore::PhysicsCoreInit( math::Vector3* minWold, math::Vector3* maxWold )
//{
//	//	すでに物理ワールドが生成されている
//	if( world )
//		return -1;
//
//	btVector3		worldAabbMin;
//	btVector3		worldAabbMax;
//
//	if( minWold )
//	{
//		worldAabbMin.setX( minWold->x );
//		worldAabbMin.setY( minWold->y );
//		worldAabbMin.setZ( minWold->z );
//	}
//	else
//	{
//		worldAabbMin.setX( -500 );
//		worldAabbMin.setY( -500 );
//		worldAabbMin.setY( -500 );
//	}
//	if( maxWold )
//	{
//		worldAabbMin.setX( maxWold->x );
//		worldAabbMin.setY( maxWold->y );
//		worldAabbMin.setZ( maxWold->z );
//	}
//	else
//	{
//		worldAabbMin.setX( 500.0f );
//		worldAabbMin.setY( 500.0f );
//		worldAabbMin.setY( 500.0f );
//	}
//
//	//	物理エンジンの作成
//	config		= new btDefaultCollisionConfiguration;
//	dispatcher	= new btCollisionDispatcher( config );
//	sweep		= new btAxisSweep3( worldAabbMin, worldAabbMax );
//	solver		= new btSequentialImpulseConstraintSolver;
//
//	world		= new btDiscreteDynamicsWorld(
//		dispatcher,
//		sweep,
//		solver,
//		config
//	);
//
//	world->setGravity( btVector3( 0, -10, 0 ) );
//
//	return 0;
//}
//
////	物理エンジンの解放
//void PhysicsCore::PhysicsCoreRelese()
//{
//	if( world == NULL )
//		return;
//
//	SafeDelete( world );
//	SafeDelete( solver );
//	SafeDelete( sweep );
//	SafeDelete( dispatcher );
//	SafeDelete( config );
//
//	return;
//}
//
////	物理エンジン設定クラスの取得
//btDynamicsWorld* PhysicsCore::GetDynamicsWorld()
//{
//	return world;
//}
//
//}	//	physics	end
//}	//	iruna	end