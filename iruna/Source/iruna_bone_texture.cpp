//
///*----�C���N���[�h------------------------------------------------*/
//#include "../Include/iruna_bone_texture.h"
//#include "../Include/iruna_math.h"
//
///*----�f�[�^�^-------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
////	�R���X�g���N�^
//BoneTexture::BoneTexture()
//:		tran( NULL ),
//		rot( NULL ),
//		tranRt( NULL ),
//		rotRt( NULL ),
//		render( NULL )
//{
//	render	= new DeviceController;
//	tran	= new Texture;
//	rot		= new Texture;
//	tranRt	= new Surface;
//	rotRt	= new Surface;
//	
//
//
//	tran->GetSurface( ( *tranRt ) );
//	rot->GetSurface( ( *rotRt ) );
//
//	width = 0;
//	height = 0;
//
//	return;
//}
//
////	�f�X�g���N�^
//BoneTexture::~BoneTexture()
//{
//	SafeDelete( tran );
//	SafeDelete( rot );
//	SafeDelete( tranRt );
//	SafeDelete( rotRt );
//	SafeDelete( render );
//	return;
//}
////	�E�B���h�E�T�C�Y�̐ݒ�
//void BoneTexture::SetWindowSize( int in_width, int in_height )
//{
//	width = in_width;
//	height = in_height;
//
//	return;
//}
//
////	�e�N�X�`���̍X�V
//void BoneTexture::TextureUpDate( math::Matrix* skinData )
//{
//	
//	int boneNum = sizeof( *skinData ) / sizeof( math::Matrix );
//
//	//	�{�[���̐�����e�N�X�`���T�C�Y��ݒ�
//	//	MRT�ł�邽�ߏc��1���̓{�[�����Ńs�N�Z���������킹��
//	tran->Create( boneNum, 1, D3DUSAGE_RENDERTARGET );
//	rot->Create( boneNum, 1, D3DUSAGE_RENDERTARGET );
//	
//	Surface			backBuffer;		
//	Viewport		oldViewport;	
//	Viewport		newViewport;	
//	
//	newViewport.SetSize( 0, 0, width, height );
//
//	Surface		oldDepthTarget;
//	Surface		newDepthTarget;
//
//	newDepthTarget.CreateDepth( width, height,Surface::Z_D16 );
//
//	GetViewport( oldViewport );
//	GetBackBuffer( backBuffer );
//	GetDepthTarget( oldDepthTarget );
//
//	//	�����ւ�
//	newDepthTarget.SetDepthTarget();
//	newViewport.SetViewport();
//	tranRt->SetRenderTarget( 0 );
//	rotRt->SetRenderTarget( 1 );
//
//	return;
//}
//
////	���s�ړ������e�N�X�`���̎擾
//Texture* BoneTexture::GetTransTexture()
//{
//	return tran;
//}
//
//Texture* BoneTexture::GetRotTexture()
//{
//	return rot;
//}
//
//}	//	graphics	end
//}	//	iruna		end