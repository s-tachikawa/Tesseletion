
// グローバル変数
cbuffer global
{
	matrix g_mWVP;//	ワールドマトリックス
}

Texture2D g_texDecal: register(t0);//テクスチャー
SamplerState g_samLinear : register(s0);//サンプラー

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//頂点シェーダー
VS_OUTPUT VS( float4 Pos : POSITION ,float2 Tex : TEXCOORD )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul( Pos, g_mWVP );
    output.Tex  = Tex;

    return output;
}

//VS_OUTPUT VS( float4 Pos : POSITION )
//{
//    VS_OUTPUT output = (VS_OUTPUT)0;
//    output.Pos = mul( Pos, g_mWVP );

//    return output;
//}

//ピクセルシェーダー
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	float4 outColor = g_texDecal.Sample( g_samLinear, input.Tex ) + float4( 0.0f, 0.0, 0.0, 1.0f );
	return outColor;
	//return float4( 1.0f, 0.0, 1.0, 1.0f );
}