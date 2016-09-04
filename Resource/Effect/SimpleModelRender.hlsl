
// グローバル変数
cbuffer global : register(b0)
{
	matrix g_mWorld : packoffset(c0);		//	ワールドマトリックス
	matrix g_mView : packoffset(c4);		//	ビューマトリックス
	matrix g_mProj : packoffset(c8);		//	プロジェクショントリックス

	//float3 lightDir = float3( 1,0,1 );
}

Texture2D g_texDecal: register(t0);//テクスチャー

SamplerState g_samLinear : register(s0);//サンプラー

//構造体
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
};

//頂点シェーダー
VS_OUTPUT VS(	float4 Pos : POSITION ,
				float3 normal : NORMAL,
				float2 Tex : TEXCOORD0 )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    //output.Pos = mul( Pos, g_mWVP );
	output.Pos = mul(Pos, g_mWorld);
	output.Pos = mul(output.Pos, g_mView);
	output.Pos = mul(output.Pos, g_mProj);
	output.Normal = normal;
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
	//float Power = dot(input.Normal.xyz, normalize(-lightDir.xyz));
	//float Power = 1.0f * lightDir.x;
	//Power = Power * 0.5f + 0.5f;
	//Power = Power * Power;

	float4 outColor = g_texDecal.Sample(g_samLinear, input.Tex);
	return outColor;
	//return float4(lightDir.x, lightDir.y, lightDir.z, 1.0f);
	//return float4( 1.0f, 0.0, 1.0, 1.0f );
}