//---------------------------------------------------------
// 
//	iruna_matrix.cpp
//	�s��֘A
//	�쐬�� 8��6��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_matrix.h"

namespace iruna
{
namespace math
{
//=====================================================================
//	�N���X��	:	WoldMatrix
//=====================================================================

// �R���X�g���N�^
WoldMatrix::WoldMatrix()
{
	// �s��̏�����
	D3DXMatrixIdentity( &tran );
	D3DXMatrixIdentity( &rota );
	D3DXMatrixIdentity( &scal );
	return;
}

void WoldMatrix::SetTranslation(float vecX, float vecY, float vecZ)
{
	D3DXMatrixTranslation(&tran , vecX , vecY , vecZ );
	return;
}
void WoldMatrix::SetRotation(float radX, float radY, float radZ)
{
	D3DXMatrixRotationYawPitchRoll( &rota, radY, radX, radZ );
	return;
}
void WoldMatrix::SetScal(float scalX, float scalY, float scalZ)
{
	D3DXMatrixScaling( &scal, scalX, scalY, scalZ );
	return;
}

Matrix WoldMatrix::GetWoldMatrix()
{
	Matrix wold;

	wold = scal * rota * tran;

	return wold;
}

}	//	math	end
}	//	iruna	end