//*********************************************************************
/*!
	@file	white_color4.h
	@brief	a,r,g,b�̐F������
	@author	���� �Ė�
	@date	2011/06/23	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_COLOR4_H
#define IRUNA_COLOR4_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	ColorChannel
//! @brief	RED BULE GREEN ALPHA���w�肷�邽�߂̈ꗗ
//!
//!=====================================================================
struct ColorChannel
{
//	�p�u���b�N	�^��`
public:
	enum Type{
		BLUE,
		GREEN,
		RED,
		ALPHA,
		MAX
	};
};

//!=====================================================================
//!
//! @union	Color4
//! @brief	�����^��RED BULE GREEN ALPHA���������p��
//!
//!=====================================================================
union Color4
{
//	�p�u���b�N	�����o�ϐ�
public:
	U_CHAR	channel[ ColorChannel::MAX ];	//!< 1�F���ق����p
	U_LONG	color;							//!< �S���܂Ƃ߂Ăق����p

//	�p�u���b�N	�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(U_LONG�ŏ���������^�C�v)
	//! @param	[in] setColor	- ���̐F�ŏ���������
	//! 
	//!--------------------------------------------------------------------
	Color4( U_LONG setColor = 0 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(U_CHAR�~4�ŏ���������^�C�v)
	//! @param	[in] r	- ���b�h�͂���ŏ���������
	//! @param	[in] g	- �O���[���͂���ŏ���������
	//! @param	[in] b	- �u���[�͂���ŏ���������
	//! @param	[in] a	- �A���t�@�͂���ŏ���������
	//! 
	//!--------------------------------------------------------------------
	Color4( U_CHAR r, U_CHAR g, U_CHAR b, U_CHAR a = 255 );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	������U_LONG�ȂƂ���ɂ����ނ�U_LONG�Ƃ��Ĉ�����
	//! @retval	U_LONG�^�̐F(4�F�܂Ƃ߂�)
	//! 
	//!--------------------------------------------------------------------
	inline	operator U_LONG() const;

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�z��̓Y�����A�N�Z�X�̂悤�Ɉ�F���F���擾����
	//! @retval	U_CHAR�^�̐F(1�F����)
	//! 
	//!--------------------------------------------------------------------
	inline const U_CHAR&	operator []( UINT getChannel ) const;
};

// �C�����C�������o�֐��̎���
// ������U_LONG�ȂƂ���ɂ����ނ�U_LONG�Ƃ��Ĉ�����
inline Color4::operator U_LONG() const
{
	return color;
}

// �z��̓Y�����A�N�Z�X�̂悤�Ɉ�F���F���擾����
inline const U_CHAR& Color4::operator []( UINT getChannel ) const
{
	return channel[ getChannel ];
}

//!=====================================================================
//!
//! @struct	Color4F
//! @brief	���������_�^��RED BULE GREEN ALPHA�������\����
//!
//!=====================================================================
struct Color4F
{
// �p�u���b�N		�����o�ϐ�
public:
	float	r;	//!< ��
	float	g;	//!< ��
	float	b;	//!< ��
	float	a;	//!< �����x

// �p�u���b�N		�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(�S��0�ŏ���������^�C�v)
	//! 
	//!--------------------------------------------------------------------
	Color4F();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(D3DCOLORVALUE�ŏ���������^�C�v)
	//! 
	//!--------------------------------------------------------------------
	Color4F( D3DCOLORVALUE colorValue );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^(����w�肵�ď���������^�C�v)
	//! @param	[in] setR	- ���b�h�͂���ŏ���������
	//! @param	[in] setG	- �O���[���͂���ŏ���������
	//! @param	[in] setB	- �u���[�͂���ŏ���������
	//! @param	[in] setA	- �A���t�@�͂���ŏ���������
	//! 
	//!--------------------------------------------------------------------
	Color4F( float setR, float setG, float setB, float setA );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	������D3DCOLORVALUE�ȂƂ���ɂ����ނ�D3DCOLORVALUE�Ƃ��Ĉ�����
	//! @retval	D3DCOLORVALUE�^
	//! 
	//!--------------------------------------------------------------------
	inline	operator D3DCOLORVALUE() const;
};

// �C�����C�������o�֐��̎���
// ������D3DCOLORVALUE�ȂƂ���ɂ����ނ�D3DCOLORVALUE�Ƃ��Ĉ�����
inline Color4F::operator D3DCOLORVALUE() const
{
	D3DCOLORVALUE	temp;

	temp.r	= r;
	temp.g	= g;
	temp.b	= b;
	temp.a	= a;

	return temp;
}


}	// graphics	end
}	// iruna	end

/*----�֐� �錾----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!--------------------------------------------------------------------
//! 
//! @brief	Color4F����Color4�ɕϊ�����
//! @param	[in] colorValue	- �ϊ�������Color4F
//! @retval	Color4�ɂȂ����F
//! 
//!--------------------------------------------------------------------
inline const Color4 ToColor4( const Color4F& colorValue )
{
	return Color4( static_cast< U_CHAR >( colorValue.r * 255.f ),
				   static_cast< U_CHAR >( colorValue.g * 255.f ),
				   static_cast< U_CHAR >( colorValue.b * 255.f ),
				   static_cast< U_CHAR >( colorValue.a * 255.f ));
}

//!--------------------------------------------------------------------
//! 
//! @brief	Color4����Color4F�ɕϊ�����
//! @param	[in] color4	- �ϊ�������Color4
//! @retval	Color4F�ɂȂ����F
//! 
//!--------------------------------------------------------------------
inline const Color4F ToColor4F( const Color4& color4 )
{
	return Color4F( color4[ ColorChannel::RED   ] / 255.f,
					color4[ ColorChannel::GREEN ] / 255.f,
					color4[ ColorChannel::BLUE  ] / 255.f,
					color4[ ColorChannel::ALPHA ] / 255.f);
}


}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_COLOR4_H	end