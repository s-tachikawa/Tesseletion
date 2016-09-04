//---------------------------------------------------------
// 
//	iruna_material.cpp
//	�����Ȃǂ̏�������
//	�쐬�� 6��23��
//	����� ���� �Ė�
// 
//---------------------------------------------------------

/*----�C���N���[�h-------------------------------------------------*/
#include "../Include/iruna_material.h"

/*----�f�[�^�^ �錾------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// �R���X�g���N�^(�S��0�ŏ���������^�C�v)
Material::Material()
{
	memset( this, 0, sizeof( Material ) );

	return;
}

// �R���X�g���N�^(1���w�肵�ď���������^�C�v)
Material::Material( Color4F setDiffuse, Color4F setAmbient, Color4F setSpecular, Color4F setEmissive, float setPower )
	: diffuse ( setDiffuse  ),
	  ambient ( setAmbient  ),
	  specular( setSpecular ),
	  emissive( setEmissive ),
	  power	  ( setPower	)
{
	return;
}

// �R���X�g���N�^(D3DMATERIAL9�ŏ���������^�C�v)
Material::Material( D3DMATERIAL9 setMaterial )
{
	diffuse	 = setMaterial.Diffuse;
	ambient	 = setMaterial.Ambient;
	specular = setMaterial.Specular;
	emissive = setMaterial.Emissive;
	power	 = setMaterial.Power;

	return;
}

// D3DMATERIAL9�^�Ŏ擾����
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