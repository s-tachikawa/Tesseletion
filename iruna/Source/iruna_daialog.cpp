//---------------------------------------------------------
// 
//	iruna_dialog.cpp
//	windowsダイアログを出す
//	作成日 10月21日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
#include "../Include/iruna_dialog.h"
#include "../Include/iruna_system.h"

namespace iruna
{
namespace core
{
LPCTSTR			CD_FILTER_LOAD_MODEL="SGD形式(*.sgd)\0*.sgd\0FBX形式(*.fbx)\0*.fbx\0すべてのファイル(*.*)\0*.*\0\0";
LPCTSTR			CD_FILTER_SAVE_MODEL="SGD形式(*.sgd)\0*.sgd\0すべてのファイル(*.*)\0*.*\0\0";
LPCTSTR			CD_FILTER_TEXTURE	="TGA形式(*.tga)\0*.tga\0DDS形式(*.dds)\0*.dds\0BMP形式(*.bmp)\0*.bmp\0JPG形式(*.jpg)\0*.jpg\0PNG形式(*.png)\0*.png\0すべてのファイル(*.*)\0*.*\0\0";
LPCTSTR			CD_FILTER_SHEDER	="エフェクトファイル(*.fx)\0*.fx\0すべてのファイル(*.*)\0*.*\0\0";

const DWORD		CD_FLAGS_SAVE		= ( OFN_OVERWRITEPROMPT );
const DWORD		CD_FLAGS_LOAD		= ( OFN_FILEMUSTEXIST );

}	//	core
}	//	iruna

namespace iruna
{
namespace core
{

// 名前をつけて保存のダイアログを表示
int SaveDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath )
{
	OPENFILENAME		ofnParams		= { 0 };

	System*	system	= &System::GetInstance();

	system->Run();

	path[0] = _T( '\0' );

	ofnParams.lStructSize		= sizeof ( OPENFILENAME );
	ofnParams.hwndOwner			= NULL;
	ofnParams.hInstance			= GetModuleHandle( NULL );
	ofnParams.lpstrFilter		= filter;
	ofnParams.nFilterIndex		= 0;
	ofnParams.nMaxFile			= MAX_PATH;
	ofnParams.nMaxFileTitle		= MAX_PATH;
	ofnParams.lpstrInitialDir	= _T( "./" );
	ofnParams.lpstrTitle		= _T( "名前をつけて保存" );
	ofnParams.Flags				= flags;
	ofnParams.lpfnHook			= NULL;
	ofnParams.lpTemplateName	= NULL;

	if( fullPath )
		ofnParams.lpstrFile = path;
	else
		ofnParams.lpstrFileTitle = path;

	if( GetSaveFileName( &ofnParams ) )
		return 0;

	return -1;
}

// 開くダイアログの表示
int LoadDialog( LPTSTR path, LPCTSTR filter, DWORD flags, bool fullPath )
{
	OPENFILENAME		ofnParams		= { 0 };

	System::GetInstance().Run();

	path[0] = _T( '\0' );

	ofnParams.lStructSize		= sizeof ( OPENFILENAME );
	ofnParams.hwndOwner			= NULL;
	ofnParams.hInstance			= GetModuleHandle( NULL );
	ofnParams.lpstrFilter		= filter;
	ofnParams.nFilterIndex		= 0;
	ofnParams.nMaxFile			= MAX_PATH;
	ofnParams.nMaxFileTitle		= MAX_PATH;
	ofnParams.lpstrInitialDir	= _T( "./" );
	ofnParams.lpstrTitle		= _T( "開く" );
	ofnParams.Flags				= flags;
	ofnParams.lpfnHook			= NULL;
	ofnParams.lpTemplateName	= NULL;

	if( fullPath )
		ofnParams.lpstrFile = path;
	else
		ofnParams.lpstrFileTitle = path;

	if( GetOpenFileName( &ofnParams ) )
		return 0;

	return -1;
}

}	//	core
}	//	iruna