////---------------------------------------------------------
//// 
////	iruna_sprite.cpp
////	2D�X�v���C�g�`��
////	�쐬�� 6��24��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Include/iruna_sprite.h"
//
///*----�f�[�^�^ �錾------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// �ÓI�����o�ϐ��̎���
//VertexDeclaration	Sprite::declaration;
//
//// �R���X�g���N�^
//Sprite::Sprite()
//{
//	// ���_���̏�����
//	for( int i = 0; i < 4; i++ )
//	{
//		data[ i ].position	= math::Vector4( 0.f, 0.f, 0.f, 1.f );
//		data[ i ].color		= Color4( 0xFFFFFFFF );
//	}
//
//	// UV���W�̏�����
//	data[ 0 ].texcoord	= math::Vector2( 0.f, 0.f );
//	data[ 1 ].texcoord	= math::Vector2( 1.f, 0.f );
//	data[ 2 ].texcoord	= math::Vector2( 0.f, 1.f );
//	data[ 3 ].texcoord	= math::Vector2( 1.f, 1.f );
//
//	render	= new DeviceController;
//
//	// ���_�錾
//	static VertexDeclaration::Element	element[] = {
//	// ���_
//	{ 0, 0, D3DDECLTYPE_FLOAT4,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT,	0 },
//	// �J���[
//	{ 0,16, D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0 },
//	// uv���W
//	{ 0,20, D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0 },
//
//	D3DDECL_END()
//	};
//
//	// ���_�錾�����Ƀf�N�����[�V�����f�[�^�̍쐬
//	declaration.Create( element );
//
//	return;
//}
//
//// �f�X�g���N�^
//Sprite::~Sprite()
//{
//	declaration.Release();
//
//	SafeDelete( render );
//
//	return;
//}
//
//// �X�v���C�g�̃T�C�Y��ݒ肷��
//void Sprite::SetSize( math::Vector2 setSize )
//{
//	size	= setSize;
//
//	return;
//}
//
//// �X�v���C�g�Ƀe�N�X�`���̂ǂ̕�����\�邩
//void Sprite::SetTexUV( math::RectF uvRect )
//{
//	data[ 0 ].texcoord	= math::Vector2( uvRect.left,	uvRect.top		);
//	data[ 1 ].texcoord	= math::Vector2( uvRect.right,	uvRect.top		);
//	data[ 2 ].texcoord	= math::Vector2( uvRect.left,	uvRect.bottom	);
//	data[ 3 ].texcoord	= math::Vector2( uvRect.right,	uvRect.bottom	);
//
//	return;
//}
//
//// �X�v���C�g�̐F��ݒ肷��
//void Sprite::SetColor( Color4 setColor )
//{
//	for( int i = 0; i < 4; i++ )
//		data[ i ].color	= setColor;
//
//	return;
//}
//
//// �X�v���C�g��\������
//bool Sprite::Draw( math::Vector2 position )
//{
//	render->SetZBufferState( false );
//	declaration.Set();
//
//	data[ 0 ].position.x	= position.x;
//	data[ 0 ].position.y	= position.y;
//
//	data[ 1 ].position.x	= position.x + size.x;
//	data[ 1 ].position.y	= position.y;
//
//	data[ 2 ].position.x	= position.x;
//	data[ 2 ].position.y	= position.y + size.y;
//
//	data[ 3 ].position.x	= position.x + size.x;
//	data[ 3 ].position.y	= position.y + size.y;
//
//	bool	result	= render->DrawPrimitiveUp( Primitive::TRIANGLE_STRIP, 2, data, sizeof( Sprite::Data ) );
//
//	render->SetZBufferState( true );
//	return result;
//}
//
//}	//	graphics	end
//}	//	iruna		end