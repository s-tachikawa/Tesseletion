////---------------------------------------------------------
//// 
////	iruna_cube_texture.cpp
////	�L���[�u�e�N�X�`���[�Ǘ��N���X
////	�쐬�� 6��28��
////	����� ���� �Ė�
//// 
////---------------------------------------------------------
//
///*----�C���N���[�h-------------------------------------------------*/
//#include "../Include/iruna_cube_texture.h"
//#include "../Source/iruna_device.h"
//
///*----�f�[�^�^ �錾------------------------------------------------*/
//namespace iruna
//{
//namespace graphics
//{
//
////	�R���X�g���N�^
//CubeTexture::CubeTexture()
//	:	texture( 0 )
//{
//	return;
//}
//
////	�f�X�g���N�^
//CubeTexture::~CubeTexture()
//{
//	SafeRelease( texture );
//	return;
//}
//
//// �e�N�X�`���̓ǂݍ���
//bool CubeTexture::Load(std::string path, Color4 color, U_INT mipLevel, DWORD filter)
//{
//
//	if( FAILED( D3DXCreateCubeTextureFromFileEx(
//				Device::GetDevice(),
//				path.c_str(),
//				0,
//				mipLevel,
//				0,
//				D3DFMT_A8R8G8B8,
//				D3DPOOL_MANAGED,
//				filter,
//				filter,
//				color,
//				0,
//				0,
//				&texture
//		) ))
//	{
//		//	�e�N�X�`���̓ǂݍ��݂Ɏ��s
//		return false;
//	}
//
//	//	�ǂݍ��ݐ���
//	return true;
//}
//
//// �e�N�X�`���̉��
//void CubeTexture::Release()
//{
//	SafeRelease( texture );
//	recoveryPath.clear();
//	return;
//}
//
//// �e�N�X�`���̎擾
//const LPDIRECT3DCUBETEXTURE9& CubeTexture::GetTexture()
//{
//	return texture;
//}
//
//// �T�[�t�F�[�X�̎擾
//bool CubeTexture::GetSurface( U_INT num, Surface &surface )
//{
//	LPDIRECT3DSURFACE9	temp	= 0;
//
//	if( FAILED( texture->GetCubeMapSurface( (D3DCUBEMAP_FACES)num ,0, &temp ) ) )
//	{
//		return false;
//	}
//
//	surface	= temp;
//		
//	return true;
//
//}
//
//}	//	graphics	end
//}	//	iruna		end