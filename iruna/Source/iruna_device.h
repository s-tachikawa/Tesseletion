//*********************************************************************
/*!
	@file	iruna_device.h
	@brief	�f�o�C�X�̊Ǘ��Ɛ���
	@author	���� �Ė�
	@date	2011/06/22	- �쐬
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_DEVICE_H
#define IRUNA_DEVICE_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"
/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @class	Device
//! @brief	�f�o�C�X�Ǘ��N���X
//!
//!=====================================================================

class Device
{
//	�v���C�x�[�g	�����o�ϐ�
private:

	static ID3D11Device*					m_pcDevice;					//!< �f�o�C�X
	static ID3D11DeviceContext*				m_pcDeviceContext;			//!< D3D11�f�o�C�X�R���e�L�X�g�C���^�t�F�[�X
	static IDXGISwapChain*					m_pcSwapChain;				//!< �X���b�v�`�F�C��
	static ID3D11RenderTargetView*			m_pcRenderTargetView;		//!< �o�b�N�o�b�t�@�p�����_�[�^�[�Q�b�g�r���[
	static ID3D11RasterizerState*			m_pcRasterizestate;			//!< ���X�^���C�Y�p�X�e�[�g
	static ID3D11DepthStencilView*			m_pcDepthStencilView;		//!< �f�v�X�X�e���V���r���[
	static ID3D11Texture2D*					m_pcDepthStencil;			//!< �f�v�X�X�e���V���p�e�N�X�`��

	static D3D11_RASTERIZER_DESC			m_sRas;						//!< ���X�^���C�Y�f�[�^
	static D3D11_VIEWPORT					m_sViewPort;				//!< �r���[�|�[�g
	ID3D11BlendState*						m_pcBlendState;				//!< �e�N�X�`���̃u�����h�X�e�[�g
//	�v���C�x�[�g	�����o�֐�
private:

//	�p�u���b�N		�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	Device();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~Device();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�o�C�X�ƃX���b�v�`�F�C�����쐬����
	//! @param	[in] hWindow	- �E�B���h�E�n���h��
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	Create( HWND hWindow, U_LONG width, U_LONG height, bool mode = true );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	����ʂ��N���A���A�`����J�n����(�ÓI�����o�֐�)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static bool	ClearScreen( float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�`����I�����A����ʂɕ`�������̂�\��ʂ֓]��(�ÓI�����o�֐�)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static bool	SwapScreen();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	����ʂ��N���A���A�`����J�n����(�ÓI�����o�֐�)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static bool	ClearBackBuffer( math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�t�H���g�̃����_�[�^�[�Q�b�g�̎擾(�o�b�N�o�b�t�@�̎擾)
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static ID3D11RenderTargetView* GetRenderTargetView();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�t�H���g�̃f�v�X�X�e���V���r���[�̎擾
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static ID3D11DepthStencilView* GetDepthStencilView();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�t�H���g�̃r���[�|�[�g���擾
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static D3D11_VIEWPORT* GetViewPort();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�t�H���g�̃��X�^���C�Y�X�e�[�g�̎擾
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	static D3D11_RASTERIZER_DESC* GetRasterizerState();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�o�C�X���擾����(�ÓI�����o�֐�)
	//! @retval	�f�o�C�X
	//! 
	//!--------------------------------------------------------------------
	static ID3D11Device*	GetDevice();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�o�C�X�R���e�L�X�g���擾����(�ÓI�����o�֐�)
	//! @retval	�f�o�C�X
	//! 
	//!--------------------------------------------------------------------
	static ID3D11DeviceContext*	GetDeviceContext();
};

}	//	graphics	end
}	//	iruna		end


#endif // IRUNA_DEVICE_H
