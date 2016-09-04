//---------------------------------------------------------
// 
//	iruna_matrix.cpp
//	行列関連
//	作成日 8月6日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_matrix.h"

namespace iruna
{
namespace math
{
//=====================================================================
//	クラス名	:	WoldMatrix
//=====================================================================

// コンストラクタ
WoldMatrix::WoldMatrix()
{
	// 行列の初期化
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