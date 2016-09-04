//---------------------------------------------------------
// 
//	iruna_material.cpp
//	質感などの情報を扱う
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_material.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ(全て0で初期化するタイプ)
Material::Material()
{
	memset( this, 0, sizeof( Material ) );

	return;
}

// コンストラクタ(1つずつ指定して初期化するタイプ)
Material::Material( Color4F setDiffuse, Color4F setAmbient, Color4F setSpecular, Color4F setEmissive, float setPower )
	: diffuse ( setDiffuse  ),
	  ambient ( setAmbient  ),
	  specular( setSpecular ),
	  emissive( setEmissive ),
	  power	  ( setPower	)
{
	return;
}

// コンストラクタ(D3DMATERIAL9で初期化するタイプ)
Material::Material( D3DMATERIAL9 setMaterial )
{
	diffuse	 = setMaterial.Diffuse;
	ambient	 = setMaterial.Ambient;
	specular = setMaterial.Specular;
	emissive = setMaterial.Emissive;
	power	 = setMaterial.Power;

	return;
}

// D3DMATERIAL9型で取得する
D3DMATERIAL9 Material::GetMaterial() const
{
	D3DMATERIAL9	temp;

	temp.Diffuse	= diffuse;
	temp.Ambient	= ambient;
	temp.Specular	= specular;
	temp.Emissive	= emissive;
	temp.Power		= power;

	return temp;
}

}	//	graphics	end
}	//	iruna		end