//*********************************************************************
/*!
	@file	iruna_texture.h
	@brief	�e�N�X�`�����Ǘ�����
	@author	���� �Ė�
	@date	2011/06/23	- �쐬
	@date	2013/12/30	- �X�V�@DirectX11�d�l�ɕύX
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_TEXTURE_H
#define IRUNA_TEXTURE_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_color4.h"
#include "../Include/iruna_surface.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	Texture
//! @brief	�e�N�X�`���Ǘ��N���X
//!
//!=====================================================================
class Texture
{
//	�p�u���b�N	�^��`
public:
	
	typedef	D3DLOCKED_RECT	LockedRect; //!< �e�N�X�`���ɃA�N�Z�X���邽�߂̍\����

//	�v���C�x�[�g	�����o�ϐ�
private:
	ID3D11ShaderResourceView*	m_pcTexture;			//!< �e�N�X�`���N���X�̃|�C���^
	ID3D11RenderTargetView*		m_pcRenderTargetView;	//!< �o�b�N�o�b�t�@�p�����_�[�^�[�Q�b�g�r���[
	ID3D11DepthStencilView*		m_pcDepthStencilView;	//!< �f�v�X�X�e���V���r���[
	ID3D11Texture2D*			m_pcDynamicTexture;		//!< ���I�e�N�X�`���p�e�N�X�`���|�C���^
	ID3D11Texture2D*			m_pcDepthStencil;		//!< �f�v�X�X�e���V���p�e�N�X�`���|�C���^
	ID3D11SamplerState*			m_pcSampleLinear;		//!< �e�N�X�`���[�̃T���v���[
	
	std::string					recoveryPath;			//!< �e�N�X�`���[�̃p�X

private:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�����_�[�^�[�Q�b�g���쐬����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	CreateRenderTerget();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�v�X�X�e���V�����쐬����
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	CreateDepthStecil( U_INT width, U_INT height );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�V�F�[�_���\�[�X�r���[�̍쐬
	//! @param	[in] path		- �t�@�C���ւ̃p�X
	//! @param	[in] color		- �J���[�L�[�A���ߐF�̐ݒ�(�f�t�H���g��0)
	//! @param	[in] mipLevel	- �~�b�v�}�b�v���x���A0�`8���w��(�f�t�H���g��1)
	//! @param	[in] filter		- �t�B���^�����O(�f�t�H���g��D3DX_FILTER_LINEAR)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	CreateShaderResourceView();

//	�p�u���b�N	�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	Texture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~Texture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�摜�t�@�C������e�N�X�`����ǂݍ���
	//! @param	[in] path		- �t�@�C���ւ̃p�X
	//! @param	[in] color		- �J���[�L�[�A���ߐF�̐ݒ�(�f�t�H���g��0)
	//! @param	[in] mipLevel	- �~�b�v�}�b�v���x���A0�`8���w��(�f�t�H���g��1)
	//! @param	[in] filter		- �t�B���^�����O(�f�t�H���g��D3DX_FILTER_LINEAR)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Load( std::string path, Color4 color = 0, U_INT mipLevel = 0, DWORD filter = D3DX_FILTER_LINEAR );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�摜�t�@�C������e�N�X�`����ǂݍ���
	//! @param	[in] path		- �t�@�C���ւ̃p�X
	//! @param	[in] color		- �J���[�L�[�A���ߐF�̐ݒ�(�f�t�H���g��0)
	//! @param	[in] mipLevel	- �~�b�v�}�b�v���x���A0�`8���w��(�f�t�H���g��1)
	//! @param	[in] filter		- �t�B���^�����O(�f�t�H���g��D3DX_FILTER_LINEAR)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	CreateSamplerSate();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�J���̓��I�e�N�X�`�����쐬����
	//! @param	[in] width		- �e�N�X�`���̉���
	//! @param	[in] height		- �e�N�X�`���̍���
	//! @param	[in] usage		- �g�p���@(D3DUSAGE_DYNAMIC or D3DUSAGE_RENDERTARGET)
	//! @param	[in] mipLevel	- �~�b�v�}�b�v���x���A0�`8���w��(�f�t�H���g��1)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	CreateTexture( U_INT width, U_INT height, DWORD usage = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, U_INT mipLevel = 1, DXGI_FORMAT eFormat = DXGI_FORMAT_R8G8B8A8_TYPELESS );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�N�X�`�����������
	//! 
	//!--------------------------------------------------------------------
	void	Release();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�N�X�`�������b�N���A�A�N�Z�X���邽�߂�LockedRect��Ԃ�(���I�e�N�X�`���̂�)
	//! @param	[out] rect		- �e�N�X�`���ɃA�N�Z�X���邽�߂̍\����
	//! @param	[in] flag		- �I�v�V�����t���O(�f�t�H���g��D3DLOCK_DISCARD)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Lock( LockedRect& rect, DWORD flag = D3DLOCK_DISCARD );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�N�X�`�����A�����b�N���A�A�N�Z�X�ł��Ȃ��悤�ɂ���(���I�e�N�X�`���̂�)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Unlock();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�N�X�`�����擾
	//! @retval	�e�N�X�`���f�[�^
	//! 
	//!--------------------------------------------------------------------
	ID3D11ShaderResourceView* const GetTexture();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�N�X�`�����擾
	//! @retval	�e�N�X�`���f�[�^
	//! 
	//!--------------------------------------------------------------------
	ID3D11SamplerState*	const GetSamplerState();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�����_�[�^�[�Q�b�g�̎擾
	//! @retval	�e�N�X�`���f�[�^
	//! 
	//!--------------------------------------------------------------------
	ID3D11RenderTargetView*	const GetRenderTerget();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�v�X�X�e���V���r���[�̎擾
	//! @retval	�e�N�X�`���f�[�^
	//! 
	//!--------------------------------------------------------------------
	ID3D11DepthStencilView*	const GetDepthStencil();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�e�N�X�`���̃T�C�Y���擾
	//! @retval	�e�N�X�`���T�C�Y
	//! 
	//!--------------------------------------------------------------------
	POINT GetSize();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	������ID3D11Texture2D*�ȂƂ���ɂ����ނ�ID3D11Texture2D*�Ƃ��Ĉ�����
	//! @retval	ID3D11Texture2D*�^
	//! 
	//!--------------------------------------------------------------------
	inline	operator ID3D11ShaderResourceView*();

};

}	//	graphics	end
}	//	iruna		end

#endif	//	IRUNA_TEXTURE_H	end