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
OutputVS DotVS(float4 Pos : POSITION ,float2 Tex : TEXCOORD)
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
// RGBをグレースケールに変換する
float Luminance( float3 InRGB )
{
	float OutLum = 0.0f;

	// 輝度の計算かけているのは各RGBに対する係数
	float Lum = InRGB.r * 0.29891f + InRGB.g * 0.58661f + InRGB.b * 0.11448f;
	
	OutLum = Lum;

	return OutLum;
}
//! ピクセルシェーダ
float4 DotPS( OutputVS inPixel ) : SV_TARGET
{
	
	const int	width = halfWidth.x;

	// 中心の色を取得
	float4	centerColor = texAlbedo.Sample( samAlbedo, inPixel.texCoord );
	
	float4	outColor = centerColor;
	
	float4 col = 0;
	float count = 0;
	float minLum = 1;
	float maxLum = 0;

	// デプステクスチャの周り9ピクセルから深度値を参照して代表色を決定する
	for (int x = 0; x <3; x++)
	{
		for (int y = 0; y <3; y++)
		{
			/*
			float2 uv2 = i.uv + _PixelSize.xy * float2(x, y);
			float4 c = tex2D(_MainTex, uv2);
			float4 depthnormal = tex2D(_CameraDepthNormalsTexture, uv2);
			float3 viewNorm;
			float depth;
			DecodeDepthNormal(depthnormal, depth, viewNorm);

			// 有効ピクセルのみ処理する
			if (abs(depth - minDepth) < 0.01)
			{
			float Lum = Luminance(c.rgb);
			float alpha = pow(Lum - 0.5, 2) * 4;	// 白と黒を強調する(重み付け)
			col += c * alpha;
			count += alpha;

			minLum = min(minLum, Lum);
			maxLum = max(maxLum, Lum);
			}
			*/
			// 今回は1枚絵なのでデプスを考慮しない
			
			
			float2 PixelSize;
			PixelSize.x = 1.0f / 680.0f;
			PixelSize.y = 1.0f / 480.0f;
			
			float2 uv2 = inPixel.texCoord + PixelSize.xy * float2(x, y);
			float4 c = texAlbedo.Sample(samAlbedo, uv2);
			float Lum = Luminance(c.rgb);
			float alpha = pow(Lum - 0.5, 2) * 4;	// 白と黒を強調する(重み付け)
			col += c * alpha;
			count += alpha;

			minLum = min(minLum, Lum);
			maxLum = max(maxLum, Lum);
			
		}
	}
	col /= count;
	outColor = col;
	/*
	// エッジ強調
	if (maxLum - minLum > 0.5)
	{
	col = nearCol;
	}
	*/
	return outColor;
	//return float4( 1,1,0,1 );
}