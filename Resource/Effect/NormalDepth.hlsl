// 法線・深度描画

//! コンスタントバッファ
cbuffer global : register(b0)
{
	matrix g_mWorld : packoffset(c0);		//	ワールドマトリックス
	matrix g_mView : packoffset(c4);		//	ビューマトリックス
	matrix g_mProj : packoffset(c8);		//	プロジェクショントリックス
	matrix g_mWorldInv : packoffset(c12);		//	プロジェクショントリックス
};


//! 頂点属性
struct InputVS
{
	float4	pos			: POSITION;
	float3	normal		: NORMAL;
};

struct OutputVS
{
	float4	pos			: SV_POSITION;
	float3	normal		: NORMAL;
	float4	depth		: DEPTH;
};

//! 頂点シェーダ
OutputVS RenderVS( InputVS inVert )
{
	OutputVS	outVert = (OutputVS)0;

	outVert.pos = mul(inVert.pos, g_mWorld);
	outVert.pos = mul(outVert.pos, g_mView);
	outVert.pos = mul(outVert.pos, g_mProj);

	float4 posVP = mul(inVert.pos, g_mView);
	posVP = mul(posVP, g_mProj);
	outVert.depth.z = posVP.z / posVP.w;

	outVert.normal = mul(inVert.normal, g_mWorldInv);
	outVert.normal = mul(outVert.normal, g_mView);
	
	/*
	// 座標計算
	float4	posW = float4(
	dot( mtxWorld[0], inVert.pos ),
	dot( mtxWorld[1], inVert.pos ),
	dot( mtxWorld[2], inVert.pos ), 1.0f );
	float4	posWV = float4(
	dot( mtxView[0], posW ),
	dot( mtxView[1], posW ),
	dot( mtxView[2], posW ), 1.0f );
	outVert.pos.x = dot( mtxProj[0], posWV );
	outVert.pos.y = dot( mtxProj[1], posWV );
	outVert.pos.z = dot( mtxProj[2], posWV );
	outVert.pos.w = dot( mtxProj[3], posWV );

	outVert.depth = -posWV.z / screenParam.y;

	// 法線
	float3	normalW = float3(
	dot( mtxWorldIt[0].xyz, inVert.normal.xyz ),
	dot( mtxWorldIt[1].xyz, inVert.normal.xyz ),
	dot( mtxWorldIt[2].xyz, inVert.normal.xyz ) );
	outVert.normal.x = dot( mtxView[0].xyz, normalW );
	outVert.normal.y = dot( mtxView[1].xyz, normalW );
	outVert.normal.z = dot( mtxView[2].xyz, normalW );
	*/


	return outVert;
}
//! ピクセルシェーダ
float4 RenderPS( OutputVS inPixel ) : SV_TARGET
{
	float3	normal = normalize(inPixel.normal);
	//float depth = inPixel.depth.x / inPixel.depth.w;
	float depth = inPixel.depth.z;

	return float4(normal, depth);
	//return float4(normal, 1.0f);
	//return float4(depth, depth, depth, 1.0f);
	//return float4(1.0f,0.0f,1.0f, 1.0f);
}
