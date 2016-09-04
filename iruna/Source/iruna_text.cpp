////---------------------------------------------------------
//// 
////	iruna_text.h
////	文字列描画
////	作成日 6月24日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include "../Include/iruna_text.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//// 静的メンバ変数の実体
//Text*	Text::instance	= 0;
//
//// コンストラクタ
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
//// デストラクタ
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
//// テキストクラスの唯一のインスタンス生成する関数(静的メンバ関数)
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
//// 使いたい文字の書式を設定する
//void Text::SetStyle( int size, std::string type )
//{
//	// 既にあったらそっちを使う
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
//	// なかったら作る
//	nowFont	= fontArray.size();
//	fontArray.push_back( new Font( size, type.c_str() ) );
//
//	return;
//}
//
//// 指定した位置に文字を表示する
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
///*----グローバル関数 定義----------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// 表示する文字の書式の設定をする
//void SetFontStyle( U_INT size, std::string type )
//{
//	Text::GetInstance()->SetStyle( size, type );
//
//	return;
//}
//
//// 指定した位置に文字を表示する
//bool DrawString( float x, float y, LPCSTR str, Color4 color )
//{
//	return Text::GetInstance()->Draw( x, y, str, color );
//}
//
//// 指定した位置に文字＋数値を表示する
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