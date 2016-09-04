//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Source/iruna_physics_core.h"
//
///*----�f�[�^�^�錾-------------------------------------------------*/
//namespace iruna
//{
//namespace physics
//{
//
////	�ÓI�ϐ��̏�����
//btDynamicsWorld*			PhysicsCore::world = NULL;
//btDispatcher*				PhysicsCore::dispatcher = NULL;
//btBroadphaseInterface*		PhysicsCore::sweep = NULL;
//btConstraintSolver*			PhysicsCore::solver = NULL;
//btCollisionConfiguration*	PhysicsCore::config = NULL;
//
////	�R���X�g���N�^
//PhysicsCore::PhysicsCore()
//{
//	return;
//}
//
////	�f�X�g���N�^
//PhysicsCore::~PhysicsCore()
//{
//	PhysicsCoreRelese();
//	return;
//}
//
////	�����G���W���̏�����
//int PhysicsCore::PhysicsCoreInit( math::Vector3* minWold, math::Vector3* maxWold )
//{
//	//	���łɕ������[���h����������Ă���
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
//	//	�����G���W���̍쐬
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
////	�����G���W���̉��
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
////	�����G���W���ݒ�N���X�̎擾
//btDynamicsWorld* PhysicsCore::GetDynamicsWorld()
//{
//	return world;
//}
//
//}	//	physics	end
//}	//	iruna	end