////---------------------------------------------------------
//// 
////	iruna_lua_loader.cpp
////	Luaスクリプト読み込み
////	作成日 1月30日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
///*----インクルード------------------------------------------------*/
//#include "../Include/iruna_lua_loader.h"
//
///*----ネームスペース------------------------------------------------*/
//namespace iruna
//{
//namespace script
//{
//
////	コンストラクタ
//LuaLoader::LuaLoader()
//:lua( NULL )
//{
//	return;
//}
//
////	デストラクタ
//LuaLoader::~LuaLoader()
//{
//	return;
//}
//
////	Luaスクリプト読み込み
//bool LuaLoader::Load( std::string in_path )
//{
//	//	Luaステートの生成
//	lua = luaL_newstate();
//
//	//	Luaスクリプトの読み込み
//	if( luaL_loadfile( lua, in_path.c_str() ) != 0 )
//	{
//		//	メモリの割り当てもしくはLua内の構文エラー
//		return false;
//	}
//
//	return true;
//}
//
////	解放処理
//void LuaLoader::Relese()
//{
//	if( lua != NULL )
//	{
//		lua_close( lua );
//	}
//	return;
//}
//
////	Lua内部のデータ取得 ( bool 型 )
//bool LuaLoader::GetScriptData( bool &out_data, std::string in_path, int index )
//{
//	//	指定した番号がBool型ではない
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
////	Lua内部のデータ取得 ( double 型 )
//bool LuaLoader::GetScriptData(double &out_data, std::string in_path, int index)
//{
//	//	指定した番号がdouble型ではない
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
////	Lua内部のデータ取得 ( void* 型 )
//bool LuaLoader::GetScriptData( const void* out_data, std::string in_path, int index )
//{
//	//	指定した番号が void* 型ではない
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