////---------------------------------------------------------
//// 
////	iruna_font.cpp
////	フォント関連
////	作成日 6月24日
////	製作者 立川 翔野
//// 
////---------------------------------------------------------
//
///*----インクルード-------------------------------------------------*/
//#include"../Include/iruna_font.h"
//
///*----データ型 宣言------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// コンストラクタ
//Font::Font( U_INT size, LPCSTR type )
//{
//	Style	temp = {
//		size,
//		0,
//		0,
//		0,
//		0,
//		0,
//		0,
//		0,
//		SHIFTJIS_CHARSET,
//		OUT_TT_ONLY_PRECIS,
//		CLIP_DEFAULT_PRECIS,
//		PROOF_QUALITY,
//		FIXED_PITCH | FF_MODERN,
//	};
//	strcpy_s( temp.lfFaceName, LF_FACESIZE, type );
//
//	style	= temp;
//
//	return;
//}
//
//// デストラクタ
//Font::~Font()
//{
//	FontMap::iterator	cur = pool.begin();
//	FontMap::iterator	end = pool.end();
//	
//	for( cur; cur != end; ++cur )
//		SafeDelete( cur->second );
//
//	return;
//}
//
//// プールから文字テクスチャを取得する、なければ作成しプールに追加する
//Texture* Font::GetTexture( LPCSTR str )	
//{
//	if( pool.end() != pool.find( str ) )
//		return pool[ str ];
//
//	// 文字のビットマップを取得する
//	TEXTMETRIC		textMetaric;
//	GLYPHMETRICS	glyphMetaric;
//	U_INT			code	= 0;
//	
//	// 1バイト文字のコードは1バイト目のUINT変換、
//	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
//	char*	temp = const_cast< char* >( str );
//	if( IsDBCSLeadByte( static_cast< BYTE >( *temp ) ) )
//		code = static_cast< BYTE >( str[ 0 ] ) << 8 | static_cast< BYTE >( str[ 1 ] );
//	else
//		code = static_cast< BYTE >( str[ 0 ] );
//
//	HDC				hDc		= GetDC( 0 );
//	HFONT			hFont	= CreateFontIndirectA( &style );
//	HFONT			oldFont = static_cast< HFONT >( SelectObject( hDc, hFont ) );
//
//	GetTextMetrics( hDc, &textMetaric );
//	const MAT2		Mat		= { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
//	size_t			size	= GetGlyphOutlineA( hDc, code, GGO_GRAY2_BITMAP, &glyphMetaric, 0, 0, &Mat );
//	BYTE*			bitmap	= new BYTE[ size ];
//
//	GetGlyphOutline( hDc, code, GGO_GRAY2_BITMAP, &glyphMetaric, size, bitmap, &Mat );
//
//	SelectObject( hDc, oldFont );
//	DeleteObject( hFont );
//	ReleaseDC( 0, hDc );
//
//	// 文字のビットマップからテクスチャを作成する
//	U_INT				 offsetX = glyphMetaric.gmptGlyphOrigin.x;
//	U_INT				 offsetY = textMetaric.tmAscent - glyphMetaric.gmptGlyphOrigin.y;
//	U_INT				 width	 = glyphMetaric.gmBlackBoxX + ( 4 - glyphMetaric.gmBlackBoxX ) % 4;
//	U_INT				 height	 = glyphMetaric.gmBlackBoxY;
//	U_INT				 level	 = 5;
//	Texture*			 tex	 = new Texture;
//	Texture::LockedRect info;
//
//	tex->Create( glyphMetaric.gmCellIncX, textMetaric.tmHeight, D3DUSAGE_DYNAMIC );
//	tex->Lock( info );
//
//	FillMemory( info.pBits, info.Pitch * textMetaric.tmHeight, 0 );
//
//	for( UINT y = offsetY; y < offsetY + height; y++ )
//		for( UINT x = offsetX; x < offsetX + width; x++ )
//		{
//			DWORD	alpha	= 255 * bitmap[ x - offsetX + width * ( y - offsetY ) ] / ( level - 1 );
//			DWORD	color	= 0x00FFFFFF | ( alpha << 24 );
//
//			memcpy( static_cast< BYTE* >( info.pBits ) + info.Pitch * y + 4 * x, &color, sizeof( DWORD ) );
//		}
//
//	tex->Unlock();
//	SafeArrayDelete( bitmap );
//
//	pool.insert( std::make_pair( str, tex ) );
//
//	return tex;
//}
//
//// プールから文字サイズを取得する、なければ x：0　y：0 を返す
//POINT Font::GetSize( LPCSTR str )
//{
//	if( pool.end() != pool.find( str ) )
//		return pool[ str ]->GetSize();
//
//	return POINT();
//}
//
//// 設定されている文字の書式を取得
//Font::Style Font::GetStyle()
//{
//	return style;
//}
//
//}	//	graphics	end
//}	//	iruna		end