//---------------------------------------------------------
// 
//	iruna_base_shader.cpp
//	シェーダーファイル管理クラスのベース
//	作成日 1月14日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_pixel_shader.h"
#include "../Source/iruna_device.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
ShaderBase::ShaderBase()
:	m_pcConstantBuffer( NULL )
{
}

// デストラクタ
ShaderBase::~ShaderBase()
{
	if( m_pcConstantBuffer )
	{
		SafeRelease( m_pcConstantBuffer );
	}
}

// シェーダータイプを取得する
ShaderBase::eCreateShaderType ShaderBase::GetShaderType()
{
	return m_eType;
}

}
}
