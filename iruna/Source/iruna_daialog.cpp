//---------------------------------------------------------
// 
//	iruna_dialog.cpp
//	windows�_�C�A���O���o��
//	�쐬�� 10��21��
//	����� ���� �Ė�
// 
//---------------------------------------------------------
#include "../Include/iruna_dialog.h"
#include "../Include/iruna_system.h"

namespace iruna
{
namespace core
{
LPCTSTR			CD_FILTER_LOAD_MODEL="SGD�`��(*.sgd)\0*.sgd\0FBX�`��(*.fbx)\0*.fbx\0���ׂẴt�@�C��(*.*)\0*.*\0\0";
LPCTSTR			CD_FILTER_SAVE_MODEL="SGD�`��(*.sgd)\0*.sgd\0���ׂẴt�@�C��(*.*)\0*.*\0\0";
LPCTSTR			CD_FILTER_TEXTURE	="TGA�`��(*.tga)\0*.tga\0DDS�`��(*.dds)\0*.dds\0BMP�`��(*.bmp)\0*.bmp\0JPG�`��(*.jpg)\0*.jpg\0PNG�`��(*.png)\0*.png\0���ׂẴt�@�C��(*.*)\0*.*\0\0";
LPCTSTR			CD_FILTER_SHEDER	="�G�t�F�N�g�t�@�C��(*.fx)\0*.fx\0���ׂẴt�@�C��(*.*)\0*.*\0\0";

const DWORD		CD_FLAGS_SAVE		= ( OFN_OVERWRITEPROMPT );
const DWORD		CD_FLAGS_LOAD		= ( OFN_FILEMUSTEXIST );

}	//	core
}	//	iruna

namespace iruna
{
namespace core
{

// ���O�����ĕۑ��̃_�C�A���O��\��
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
	ofnParams.lpstrTitle		= _T( "���O�����ĕۑ�" );
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

// �J���_�C�A���O�̕\��
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
	ofnParams.lpstrTitle		= _T( "�J��" );
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