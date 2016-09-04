// テッセレーションサンプル

// コンスタントバッファ
cbuffer cbTessParam : register( b0 )
{
	// 列優先
	float4x4 g_matWVP;   // ワールド × ビュー × 射影 行列
};
cbuffer cbTessParam : register(b1)
{
	
	float	g_TessFactor;
	float	g_InsideFactor;
	//uint	g_Mode;

};

// テクスチャー
Texture2D g_Tex : register(t0);

// サンプラーステート
SamplerState  g_Sampler;

// 構造体
struct InputVS
{
	float3	pos			: POSITION0;
	float2 uv			:TEXCOORD0;
};

struct InputPS
{
	float4	pos			: SV_POSITION;
	float2 uv			:TEXCOORD0;
};

struct TriConstant
{
	float	tessFactor[3]	: SV_TessFactor;
	float	insideFactor	: SV_InsideTessFactor;
};

// Vertex Shader
InputVS RenderVS( InputVS inVert )
{
	InputVS outVert;

	outVert.pos = inVert.pos;
	outVert.uv = inVert.uv;

	return outVert;
}

// Hull Constant Shader
TriConstant RenderTriConstantHS( InputPatch<InputVS, 3> iPatch )
{
	TriConstant outConst;

	float3 retf;
	float  ritf, uitf;
	switch (1)
	{
	case 0:
	default:
		ProcessTriTessFactorsAvg( g_TessFactor, g_InsideFactor, retf, ritf, uitf );
		break;
	case 1:
		ProcessTriTessFactorsMax( g_TessFactor, g_InsideFactor, retf, ritf, uitf );
		break;
	case 2:
		ProcessTriTessFactorsMin( g_TessFactor, g_InsideFactor, retf, ritf, uitf );
		break;
	case 3:
				break;
	}


	outConst.tessFactor[0] = retf.x;
	outConst.tessFactor[1] = retf.y;
	outConst.tessFactor[2] = retf.z;
	outConst.insideFactor = ritf;
	
	
	
	return outConst;
}


// Hull Shader
[domain("tri")]					// tri, quad, isoline
[partitioning("integer")]		// integer, fractional_even, fractional_odd, pow2
[outputtopology("triangle_ccw")]	// point, line, triangle_cw, triangle_ccw 
[outputcontrolpoints(3)]
[patchconstantfunc("RenderTriConstantHS")]
InputVS RenderTriIntegerHS( InputPatch<InputVS, 3> iPatch,  uint pointID : SV_OutputControlPointID )
{
	return iPatch[pointID];
}
// Domain Shader
[domain("tri")]
InputPS RenderTriDS( TriConstant inConst, float3 domLoc : SV_DomainLocation, const OutputPatch<InputVS, 3> oPatch )
{
	InputPS outVert;

	outVert.pos.xyz = oPatch[0].pos * domLoc.z + oPatch[1].pos * domLoc.x + oPatch[2].pos * domLoc.y;
	outVert.pos.w = 1.0;
	outVert.pos = mul(outVert.pos, g_matWVP);

	outVert.uv = oPatch[0].uv * domLoc.z + oPatch[1].uv * domLoc.x + oPatch[2].uv * domLoc.y;
	return outVert;
}

// Pixel Shader
float4 RenderPS( InputPS inVert )	: SV_TARGET
{
	return g_Tex.Sample(g_Sampler, inVert.uv);
}

//	EOF
