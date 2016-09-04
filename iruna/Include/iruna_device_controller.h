//*********************************************************************
/*!
	@file	iruna_device_controller.h
	@brief	�f�o�C�X�R���e�L�X�g���ԐړI�ɑ��삷��
	@author	���� �Ė�
	@date	2011/06/23	- �쐬
	@date	2013/12/31	- �X�V	DirectX11�p�Ɏd�l��ύXDevice�ł͂Ȃ�DeviceContext�𑀍삷��悤�ɕύX
*/
//*********************************************************************

/*----���d�C���N���[�h�h�~-------------------------------------------------*/
#ifndef IRUNA_DEVICE_CONTROLLER_H
#define IRUNA_DEVICE_CONTROLLER_H

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_utility.h"
#include "../Include/iruna_math.h"

/*----�N���X�̑O���錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{
	class Texture;
	class Viewport;
}
}

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!=====================================================================
//!
//! @struct	Primitive
//! @brief	�|���S���̌`�̈ꗗ
//!
//!=====================================================================
struct Primitive
{
	enum Type
	{
		POINT_LIST		= D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,					//!< D3DPT_POINTLIST
		LINE_LIST		= D3D11_PRIMITIVE_TOPOLOGY_LINELIST,					//!< D3DPT_LINELIST
		LINE_STRIP		= D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,					//!< D3DPT_LINESTRIP
		TRIANGLE_LIST	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,				//!< D3DPT_TRIANGLELIST
		TRIANGLE_STRIP	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,				//!< D3DPT_TRIANGLESTRIP

		CONTROL_POINT_2 = D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
		CONTROL_POINT_3 = D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,	//!< 3���_�h���C���R���g���[���|�C���g
		CONTROL_POINT_4 = D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,	//!< 4���_�h���C���R���g���[���|�C���g
	};
};

//!=====================================================================
//!
//! @class	DeviceController
//! @brief	�f�o�C�X����N���X(���m�X�e�[�g)
//!
//!=====================================================================
class DeviceController
{
//	�v���C�x�[�g	�����o�ϐ�
private:
	static ID3D11DeviceContext*		m_pcD3dDeviceContext;		// �f�o�C�X�R���e�L�X�g�ւ̃|�C���^
//	�p�u���b�N		�����o�֐�
public:
	//!--------------------------------------------------------------------
	//! 
	//! @brief	�R���X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	DeviceController();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�X�g���N�^
	//! 
	//!--------------------------------------------------------------------
	~DeviceController();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�`������s
	//! @param	[in] nVertexCount	- ���_�̐�
	//! @param	[in] nIndexCount	- �`�悷�钸�_�̍ŏ��̃C���f�b�N�X
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	DrawPrimitive( int nVertexCount, int nIndexCount );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�C���f�b�N�X���g�����`������s(���_�f�[�^�̓n�[�h�E�F�A����)
	//! @param	[in] nIndexCount	- �C���f�b�N�X��
	//! @param	[in] nStartIndex	- �`�悷��C���f�b�N�X�ԍ�
	//! @param	[in] nOffsett		- �`�悷��C���f�b�N�X
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	bool	DrawIndexPrimitive( int nIndexCount, int nStartIndex, int nOffset );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	1�̃|���S���������_�ō\������邩���f�o�C�X�R���e�L�X�g�ɐݒ�
	//! @param	[in] nIndexCount	- �C���f�b�N�X��
	//! @param	[in] nStartIndex	- �`�悷��C���f�b�N�X�ԍ�
	//! @param	[in] nOffsett		- �`�悷��C���f�b�N�X
	//! @retval	���ʃt���O	ture�F�����@false�F���s
	//! 
	//!--------------------------------------------------------------------
	void	SetMeshTopology( Primitive::Type type );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	Z�o�b�t�@�ɕ`�����ނ��`�����܂Ȃ����̐ݒ肷��
	//! @param	[in] flag			- ture�F�`�����ށ@false�F�`�����܂Ȃ�
	//! 
	//!--------------------------------------------------------------------
	void	SetZBufferState( bool flag );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�w�肵�������_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɐݒ�
	//! @param	[in] flag			- ture�F�`�����ށ@false�F�`�����܂Ȃ�
	//! 
	//!--------------------------------------------------------------------
	void	SetRnderTerget( ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil );

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�t�H���g�̃����_�[�^�[�Q�b�g���o�b�N�o�b�t�@�ɃZ�b�g
	//! 
	//!--------------------------------------------------------------------
	void	SetDefaultRnderTerget();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�t�H���g�̃r���[�|�[�g��ݒ�
	//! 
	//!--------------------------------------------------------------------
	void	SetDefaultViewPort();

	//!--------------------------------------------------------------------
	//! 
	//! @brief	�f�o�C�X�����X�g���Ă��邩���X�g���ĂȂ������擾����
	//! @retval	���X�g�t���O	ture�F���X�g���Ă���@false�F���X�g���Ă��Ȃ�
	//! 
	//!--------------------------------------------------------------------
	bool	IsLostDevice();
};

}	//	graphics	end
}	//	iruna		end

/*----�O���[�o���֐� �錾----------------------------------------------------*/
namespace iruna
{
namespace graphics
{

//!--------------------------------------------------------------------
//! 
//! @brief	�w�肵�������_�[�^�[�Q�b�g���N���A����
//! @retval	���ʃt���O	ture�F�����@false�F���s
//! 
//!--------------------------------------------------------------------
bool ClearRenderTerget( math::Vector4 vColor, ID3D11RenderTargetView* pcRenderTerget, ID3D11DepthStencilView* pcDepthStencil );

//!--------------------------------------------------------------------
//! 
//! @brief	����ʂ��N���A���A�`����J�n����
//! @retval	���ʃt���O	ture�F�����@false�F���s
//! 
//!--------------------------------------------------------------------
bool ClearScreen( float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f );

//!--------------------------------------------------------------------
//! 
//! @brief	�`����I�����A����ʂɕ`�������̂�\��ʂ֓]��
//! @retval	���ʃt���O	ture�F�����@false�F���s
//! 
//!--------------------------------------------------------------------
bool SwapScreen();

}	//	graphics	end
}	//	iruna		end


#endif	//	IRUNA_DEVICE_CONTROLLER_H	end