////---------------------------------------------------------
//// 
////	iruna_font.cpp
////	�t�H���g�֘A
////	�쐬�� 6��24��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include"../Include/iruna_font.h"
//
///*----�f�[�^�^ �錾------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// �R���X�g���N�^
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
//// �f�X�g���N�^
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
//// �v�[�����當���e�N�X�`�����擾����A�Ȃ���΍쐬���v�[���ɒǉ�����
//Texture* Font::GetTexture( LPCSTR str )	
//{
//	if( pool.end() != pool.find( str ) )
//		return pool[ str ];
//
//	// �����̃r�b�g�}�b�v���擾����
//	TEXTMETRIC		textMetaric;
//	GLYPHMETRICS	glyphMetaric;
//	U_INT			code	= 0;
//	
//	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
//	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
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
//	// �����̃r�b�g�}�b�v����e�N�X�`�����쐬����
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
//// �v�[�����當���T�C�Y���擾����A�Ȃ���� x�F0�@y�F0 ��Ԃ�
//POINT Font::GetSize( LPCSTR str )
//{
//	if( pool.end() != pool.find( str ) )
//		return pool[ str ]->GetSize();
//
//	return POINT();
//}
//
//// �ݒ肳��Ă��镶���̏������擾
//Font::Style Font::GetStyle()
//{
//	return style;
//}
//
//}	//	graphics	end
//}	//	iruna		end