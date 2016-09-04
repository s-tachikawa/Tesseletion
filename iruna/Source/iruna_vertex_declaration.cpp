//---------------------------------------------------------
// 
//	iruna_vertex_declaration.h
//	バーテクスディクラレーションのラップ
//	作成日 6月23日
//	製作者 立川 翔野
// 
//---------------------------------------------------------

/*----インクルード-------------------------------------------------*/
#include "../Include/iruna_vertex_declaration.h"
#include "../Source/iruna_device.h"
#include "../Include/iruna_efect.h"
#include "../Include/iruna_base_shader.h"
#include "../Include/iruna_vertex_shader.h"

/*----データ型 宣言------------------------------------------------*/
namespace iruna
{
namespace graphics
{

// コンストラクタ
VertexDeclaration::VertexDeclaration()
	:   element			( NULL ),
		m_pcVertexLayout( NULL )
{
	return;
}

// コピーコンストラクタ
VertexDeclaration::VertexDeclaration( const VertexDeclaration& another )
{
	return;
}

// デストラクタ
VertexDeclaration::~VertexDeclaration()
{
	Release();

	return;
}

// 頂点宣言を作成する、同じエレメントを突っ込んだ場合参照カウントをインクリメント
bool VertexDeclaration::Create( Element* vertexElement, int nElementCount, ShaderBase* pcShader)
{
	// 既に作られていて、同じ頂点エレメントだったら参照カウントをインクリメント
	if( m_pcVertexLayout && element == vertexElement )
	{
		m_pcVertexLayout->AddRef();
	}

	// 同じじゃなくても作られていたら終了
	if( m_pcVertexLayout )
	{
		return false;
	}

	VertexShader* pcVertexShader = NULL;
	if( pcShader->GetShaderType() != ShaderBase::eVertexShader )
	{
		return false;
	}	
	pcVertexShader = reinterpret_cast< VertexShader* >( pcShader );

	// エレメントのコピー
	element	= vertexElement;
	ID3D11Device* pcDevice = Device::GetDevice();

	HRESULT hr = S_OK;
	hr = pcDevice->CreateInputLayout(
			vertexElement,
			nElementCount,
			pcVertexShader->m_pcShaderBlob->GetBufferPointer(),
			pcVertexShader->m_pcShaderBlob->GetBufferSize(),
			&m_pcVertexLayout
		);

	return true;
}

bool VertexDeclaration::Set()
{
	ID3D11DeviceContext* pcDeviceContext = Device::GetDeviceContext();

	pcDeviceContext->IASetInputLayout( m_pcVertexLayout );
	return true;
}
// 頂点宣言を開放する、参照カウントが0になったら削除する
void VertexDeclaration::Release()
{
	
	if( !m_pcVertexLayout )
	{
		// ディクラレーションデータがある場合は解放しない
		return;
	}

	// 参照カウントが0なら解放
	if( 0 == m_pcVertexLayout->Release() )
	{
		m_pcVertexLayout	= NULL;
		element				= NULL;
	}

	return;
}

}	//	graphics	end
}	//	iruna		end