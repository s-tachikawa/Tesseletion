////---------------------------------------------------------
//// 
////	iruna_lua_loader.cpp
////	Lua�X�N���v�g�ǂݍ���
////	�쐬�� 1��30��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
///*----�C���N���[�h------------------------------------------------*/
//#include "../Include/iruna_lua_loader.h"
//
///*----�l�[���X�y�[�X------------------------------------------------*/
//namespace iruna
//{
//namespace script
//{
//
////	�R���X�g���N�^
//LuaLoader::LuaLoader()
//:lua( NULL )
//{
//	return;
//}
//
////	�f�X�g���N�^
//LuaLoader::~LuaLoader()
//{
//	return;
//}
//
////	Lua�X�N���v�g�ǂݍ���
//bool LuaLoader::Load( std::string in_path )
//{
//	//	Lua�X�e�[�g�̐���
//	lua = luaL_newstate();
//
//	//	Lua�X�N���v�g�̓ǂݍ���
//	if( luaL_loadfile( lua, in_path.c_str() ) != 0 )
//	{
//		//	�������̊��蓖�Ă�������Lua���̍\���G���[
//		return false;
//	}
//
//	return true;
//}
//
////	�������
//void LuaLoader::Relese()
//{
//	if( lua != NULL )
//	{
//		lua_close( lua );
//	}
//	return;
//}
//
////	Lua�����̃f�[�^�擾 ( bool �^ )
//bool LuaLoader::GetScriptData( bool &out_data, std::string in_path, int index )
//{
//	//	�w�肵���ԍ���Bool�^�ł͂Ȃ�
//	if( lua_type( lua, index ) != LuaType::Bool )
//	{
//		return false;
//	}
//
//	out_data = lua_toboolean( lua, index );
//
//	return true;
//}
//
////	Lua�����̃f�[�^�擾 ( double �^ )
//bool LuaLoader::GetScriptData(double &out_data, std::string in_path, int index)
//{
//	//	�w�肵���ԍ���double�^�ł͂Ȃ�
//	//if( lua_type( lua, index ) != LuaType::Double )
//	//{
//	//	return false;
//	//}
//
//	lua_getglobal( lua, in_path.c_str() );
//
//	out_data = lua_tonumber( lua, index );
//
//	return true;
//}
//
////	Lua�����̃f�[�^�擾 ( void* �^ )
//bool LuaLoader::GetScriptData( const void* out_data, std::string in_path, int index )
//{
//	//	�w�肵���ԍ��� void* �^�ł͂Ȃ�
//	if( lua_type( lua, index ) != LuaType::Void )
//	{
//		return false;
//	}
//
//	out_data = lua_topointer( lua, index );
//	return true;
//}
//
//}	//	end script
//}	//	end	iruna