//---------------------------------------------------------
// 
//	iruna_bone.cpp
//	モデルボーン管理クラス
//	作成日 11月01日
//	製作者 立川 翔野
// 
//---------------------------------------------------------
/*----インクルード---------------------------------*/
#include "../Include/iruna_bone.h"

/*----ネームスペース---------------------------------*/
namespace iruna
{
namespace graphics
{
// コンストラクタ
Bone::Bone()
{
	// 行列の初期化
	D3DXMatrixIdentity( &init );
	D3DXMatrixIdentity( &offset );
	D3DXMatrixIdentity( &tran );
	D3DXMatrixIdentity( &comb );
	D3DXMatrixIdentity( &test );
	D3DXMatrixIdentity( &skin );

	id			= -1;
	parentId	= -1;
}

// ボーンの相対座標を親の相対座標に変える
void Bone::BoneRun(iruna::math::Matrix* parentOffset)
{
	//子ボーンがいるなら自分のオフセット行列を渡して
	//親との相対姿勢に直します
	for( int i = 0; i< (int)child.size();i++ )
		child[ i ]->BoneRun( &offset );

	//ルートボーンは計算しない
	if( parentOffset )
		init *= *parentOffset;

	return;
}

// ボーンの姿勢更新
void Bone::BoneUpDate( iruna::math::Matrix parent )
{
	D3DXMatrixIdentity( &skin );
	D3DXMatrixIdentity( &comb );
	//変換行列と親行列から合成行列の作成
	comb = (tran) * parent;
	
	//子ボーンがいるならの子ボーンの更新	
	for( int i = 0; i <  (int)child.size(); i++)
		child[ i ]->BoneUpDate( comb );
		
	//スキニング行列の作成
	skin = offset * comb;
		
	return;
}

// ボーンの初期姿勢の設定(Matrix ver)
void Bone::SetInitMatrix( math::Matrix initMat )
{
	init = initMat;
	return;
}

//	ボーンの初期姿勢の設定(Vector ver)
void Bone::SetInitMatrix( math::Vector3 bonePos )
{

	D3DXMatrixTranslation(	&init,
							bonePos.x,
							bonePos.y,
							bonePos.z
							);

	//	初期姿勢からオフセット行列を生成
	D3DXMatrixInverse( &offset, 0, &init );
	return;
}

}	//	graphics	end
}	//	iruna		end