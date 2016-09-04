// SNN

//! コンスタントバッファ
cbuffer cbPixelParam : register( b0 )
{
	float4	uvOffset			: packoffset( c0 );
	int4	halfWidth			: packoffset( c1 );
};

//! テクスチャとサンプラ
Texture2D		texAlbedo	: register( t0 );
SamplerState	samAlbedo	: register( s0 );

struct OutputVS
{
	float4	pos			: SV_POSITION;
	float2	texCoord	: TEXCOORD;
};

//! 頂点シェーダ
OutputVS SnnVS(float4 Pos : POSITION ,float2 Tex : TEXCOORD)
{
	OutputVS	outVert;

	outVert.pos = Pos;
	outVert.texCoord = Tex;

	return outVert;
}

float4 GetSNN( float4 centerColor, float2 uv, float2 offset )
{
	float4	col0 = texAlbedo.Sample( samAlbedo, uv + offset );
	float4	col1 = texAlbedo.Sample( samAlbedo, uv - offset );
	float3	d0 = col0.rgb - centerColor.rgb;
	float3	d1 = col1.rgb - centerColor.rgb;
	if( dot(d0, d0) < dot(d1, d1) )
	{
		return col0;
	}
	return col1;
}
//! ピクセルシェーダ
float4 SnnPS( OutputVS inPixel ) : SV_TARGET
{
	
	const int	width = halfWidth.x;

	float4	centerColor = texAlbedo.Sample( samAlbedo, inPixel.texCoord );
	float4	outColor = centerColor;
	float	pixels = 1.0f;
	float4  uvOff;
	uvOff.x = 1.0f / 680.0f;
	uvOff.y = 1.0f / 480.0f;
	for( int y = -7; y < 7; ++y )
	{
		float	yOffset = uvOff.y * (float)y;
		for( int x = -7; x <= 7; ++x )
		{
			float2	offset = { uvOff.x * (float)x, yOffset };
			outColor += GetSNN( centerColor, inPixel.texCoord, offset ) * 2.0f;
			pixels += 2.0f;
		}
	}
	for( int x = -7; x < 0; ++x )
	{
		float2	offset = { uvOff.x * (float)x, 0.0f };
		outColor += GetSNN( centerColor, inPixel.texCoord, offset ) * 2.0f;
		pixels += 2.0f;
	}
	outColor /= pixels;

	return outColor;
	//return float4( 1,1,0,1 );
}