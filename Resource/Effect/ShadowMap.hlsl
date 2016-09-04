// グローバル変数
cbuffer global
{
	column_major matrix g_mLightViewProj;// ライトビュープロジェクション
}

//構造体
struct VS_OUTPUT
{
    float4 pos 		: SV_POSITION;
    float2 tex 		: TEXCOORD0;
    float4 depth 	: TEXCOORD1;
};

VS_OUTPUT ShadowVS( float4 in_pos : POSITION,float2 tex : TEXCOORD )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	// 座標変換
	output.pos = mul( in_pos, g_mLightViewProj);
	
	output.tex = tex;
	
	// 位置情報の出力
	output.depth =  output.pos;
	return output;
}

float4 ShadowPS( VS_OUTPUT in_input ) : SV_Target
{
	// ピクセルの深度情報を計算して出力
	float4 color = float4( 0,0,0, 1.0f );
	color = ( in_input.depth.z / in_input.depth.w );
	
	return color;
}