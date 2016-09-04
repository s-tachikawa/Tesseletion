////---------------------------------------------------------
//// 
////	iruna_bord.cpp
////	�|���̃f�t�H���g�N���X(�h�����ăr���{�[�h�Ƃ��ɂ���)
////	�쐬�� 6��24��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Include/iruna_bord.h"
//
///*----�f�[�^�^ �錾------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
//// �ÓI�����o�ϐ��̎���
//VertexDeclaration	Board::declaration;
//
//// �R���X�g���N�^
//Board::Board()
//{
//	// ���_�o�b�t�@�N���X�̊m��
//	positionBuffer	= new VertexBuffer;
//	texcoordBuffer	= new VertexBuffer;
//	colorBuffer		= new VertexBuffer;
//	normalBuffer	= new VertexBuffer;
//
//	//	���_�o�b�t�@�̐���
//	positionBuffer->Create( VertexBuffer::FLOAT3, 4 );
//	texcoordBuffer->Create( VertexBuffer::FLOAT2, 4 );
//	colorBuffer->Create(	VertexBuffer::COLOR,  4 );
//	normalBuffer->Create( 	VertexBuffer::FLOAT3, 4 );
//
//	// �o�b�N�A�b�v�p�f�[�^��������
//	for( int i = 0; i < 4; i++ )
//	{
//		size[ i ]	= math::Vector3( 0.f, 0.f, 0.f );
//		color[ i ]	= Color4( 0xFFFFFFFF );
//	}
//	
//	// UV���W�̏�����
//	texcoord[ 0 ]	= math::Vector2( 0.f, 0.f );
//	texcoord[ 1 ]	= math::Vector2( 1.f, 0.f );
//	texcoord[ 2 ]	= math::Vector2( 0.f, 1.f );
//	texcoord[ 3 ]	= math::Vector2( 1.f, 1.f );
//
//	// �@��
//	normal[ 0 ] = math::Vector3( 0, 0, -1 );
//	normal[ 1 ] = math::Vector3( 0, 0, -1 );
//	normal[ 2 ] = math::Vector3( 0, 0, -1 );
//	normal[ 3 ] = math::Vector3( 0, 0, -1 );
//
//	// ���_�o�b�t�@�ɒl���Z�b�g
//	positionBuffer->SetBuffer( size,	 0, 4 );
//	texcoordBuffer->SetBuffer( texcoord, 0, 4 );
//	colorBuffer->SetBuffer(	   color,	 0, 4 );
//	normalBuffer->SetBuffer( normal, 0, 4 );
//
//	render	= new DeviceController;
//
//	// ���_�錾
//	static VertexDeclaration::Element	element[] = {
//	// ���_
//	{ 0, 0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0 },
//	// �@��
//	{ 1, 0, D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	0 },
//	// UV
//	{ 2, 0, D3DDECLTYPE_FLOAT2,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,		0 },
//	// �J���[
//	{ 3, 0, D3DDECLTYPE_D3DCOLOR,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,	0 },
//
//	D3DDECL_END()
//	};
//
//	// �ݒ肵�����_�錾���ƂɃf�N�����[�V�����𐶐�
//	declaration.Create( element );
//
//	return;
//}
//
//// �f�X�g���N�^(���z�֐�)
//Board::~Board()
//{
//	declaration.Release();
//
//	SafeDelete( positionBuffer );
//	SafeDelete( texcoordBuffer );
//	SafeDelete( normalBuffer );
//	SafeDelete( colorBuffer	   );
//	SafeDelete( render		   );
//
//	return;
//}
//
//// �|���S���̃T�C�Y��ݒ肷��(���z�֐�)
//void Board::SetSize( math::Vector2 setSize )
//{
//	size[ 0 ]		= math::Vector3( -setSize.x / 2.f,  setSize.y / 2.f, 0.f );
//	size[ 1 ]		= math::Vector3(  setSize.x / 2.f,  setSize.y / 2.f, 0.f );
//	size[ 2 ]		= math::Vector3( -setSize.x / 2.f, -setSize.y / 2.f, 0.f );
//	size[ 3 ]		= math::Vector3(  setSize.x / 2.f, -setSize.y / 2.f, 0.f );
//
//	positionBuffer->SetBuffer( size, 0, 4 );
//
//	return;
//}
//
//// �|���S���Ƀe�N�X�`���̂ǂ̕�����\�邩(���z�֐�)
//void Board::SetTexUV( math::RectF uvRect )
//{
//	texcoord[ 0 ]	= math::Vector2( uvRect.left,	uvRect.top		);
//	texcoord[ 1 ]	= math::Vector2( uvRect.right,	uvRect.top		);
//	texcoord[ 2 ]	= math::Vector2( uvRect.left,	uvRect.bottom	);
//	texcoord[ 3 ]	= math::Vector2( uvRect.right,	uvRect.bottom	);
//
//	texcoordBuffer->SetBuffer( texcoord, 0, 4 );
//
//	return;
//}
//
//// �|���S���̐F��ݒ肷��(���z�֐�)
//void Board::SetColor( Color4 setColor )
//{
//	for( int i = 0; i < 4; i++ )
//		color[ i ]	= setColor;
//
//	colorBuffer->SetBuffer( color, 0, 4 );
//
//	return;
//}
//
//// �|���S����\������(���z�֐�)
//bool Board::Draw()
//{
//	
//	declaration.Set();
//
//	positionBuffer->IntoStream( 0 );
//	normalBuffer->IntoStream( 1 );
//	colorBuffer->IntoStream( 3 );
//	texcoordBuffer->IntoStream( 2 );
//
//	return render->DrawPrimitive( Primitive::TRIANGLE_STRIP, 2 );
//}
//
//}	//	graphicd	end
//}	//	iruna		end