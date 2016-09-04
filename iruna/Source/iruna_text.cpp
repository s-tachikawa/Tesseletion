////---------------------------------------------------------
//// 
////	iruna_text.h
////	������`��
////	�쐬�� 6��24��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Include/iruna_text.h"
//
///*----�f�[�^�^ �錾------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//// �ÓI�����o�ϐ��̎���
//Text*	Text::instance	= 0;
//
//// �R���X�g���N�^
//Text::Text()
//	: nowFont( 0 )
//{
//	setlocale( LC_CTYPE, "jpn" );
//
//	sprite	= new Sprite;
//	render	= new DeviceController;
//
//	return;
//}
//
//// �f�X�g���N�^
//Text::~Text()
//{
//	SafeDelete( render );
//	SafeDelete( sprite );
//
//	for( U_INT i = 0; i < fontArray.size(); i++ )
//	{
//		SafeDelete( fontArray[ i ] );
//	}
//
//	return;
//}
//
//// �e�L�X�g�N���X�̗B��̃C���X�^���X��������֐�(�ÓI�����o�֐�)
//Text*& Text::GetInstance()
//{
//	if( !instance )
//	{
//		instance	= new Text;
//	}
//
//	return instance;
//}
//
//// �g�����������̏�����ݒ肷��
//void Text::SetStyle( int size, std::string type )
//{
//	// ���ɂ������炻�������g��
//	for( U_INT i = 0; i < fontArray.size(); i++ )
//	{
//		Font::Style	temp = fontArray[ i ]->GetStyle();
//		if( 0	 == type.compare( temp.lfFaceName ) &&
//			size == temp.lfHeight )
//		{
//			nowFont	= i;
//
//			return;
//		}
//	}
//
//	// �Ȃ���������
//	nowFont	= fontArray.size();
//	fontArray.push_back( new Font( size, type.c_str() ) );
//
//	return;
//}
//
//// �w�肵���ʒu�ɕ�����\������
//bool Text::Draw( float x, float y, LPCSTR str, Color4 color )
//{
//	float			trans	= 0;
//	int				length	= 0;
//	std::string		string	= str;
//
//	for( U_INT i = 0; i < string.size(); i += length )
//	{
//		length	= mblen( &string[ i ], MB_CUR_MAX );
//		std::string		temp = string.substr( i, length );
//
//		math::Vector2	position( x + trans, y );
//		Texture*		texture	= fontArray[ nowFont ]->GetTexture( temp.data() );
//		POINT			size	= fontArray[ nowFont ]->GetSize( temp.data() );
//
//		render->SetTexture( 0, texture->GetTexture() );
//
//		sprite->SetColor( color );
//		sprite->SetSize( math::Vector2( static_cast< float >( size.x ), static_cast< float >( size.y ) ) );
//		if( !sprite->Draw( position ) )
//		{
//			return false;
//		}
//
//		trans	+= size.x;
//	}
//
//	return true;
//}
//
//}	//	graphics	end
//}	//	iruna		end
//
///*----�O���[�o���֐� ��`----------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// �\�����镶���̏����̐ݒ������
//void SetFontStyle( U_INT size, std::string type )
//{
//	Text::GetInstance()->SetStyle( size, type );
//
//	return;
//}
//
//// �w�肵���ʒu�ɕ�����\������
//bool DrawString( float x, float y, LPCSTR str, Color4 color )
//{
//	return Text::GetInstance()->Draw( x, y, str, color );
//}
//
//// �w�肵���ʒu�ɕ����{���l��\������
//bool DrawFormatString( float x, float y, Color4 color, LPCSTR str, ... )
//{
//	va_list		list;
//	char		temp[ 512 ];
//
//	va_start( list, str );
//	vsprintf_s( temp, 512, str, list );
//	va_end( list );
//
//	return Text::GetInstance()->Draw( x, y, temp, color );
//}
//
//}	//	graphics	end
//}	//	iruna		end