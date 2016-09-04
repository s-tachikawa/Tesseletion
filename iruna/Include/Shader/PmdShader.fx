
texture		tex;

sampler sampler0	= sampler_state
{
	Texture		= <tex>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	
};

float4x4	world		: WORLD;
float4x4	view		: VIEW;
float4x4	projection	: PROJECTION;

float4	diffuse = float4( 1.0f,1.0f,1.0f,1.0f );		//	ディフューズ(拡散光)
float4	ambient = float4( 1.0f,1.0f,1.0f,1.0f );		//	アンビエント(環境光)
float4	specular = float4( 1.0f,1.0f,1.0f,1.0f );		//	スペキュラー(鏡面光)

float4	lightPos = float4( 0.0f, 40.0f, -70.0f, 1.0f );
float4	lightDir = float4( 2.0f, 5.0f, 0.0f, 0.0f );

struct VsOutput{
	float4	pos	: POSITION;
	float2	uv	: TEXCOORD0;
	float4 normal: TEXCOORD1;
};

VsOutput mainVS(  float3 local	: POSITION, 
				 float3 normal	: NORMAL,
				 float2 uv		: TEXCOORD0 )
{
	VsOutput	vertex = ( VsOutput )0;
	
	vertex.pos	 = mul( float4( local, 1.0f ), world );
	vertex.pos	 = mul( mul( vertex.pos, view ), projection );
	vertex.uv	 = uv;
	vertex.normal = float4( normal,1.0f );

	return vertex;
}

//	テクスチャあり
float4 mainPS( VsOutput input ) : COLOR 
{
	float4 lightVec = lightDir - lightPos;
   float4 Out;
   float p = dot( normalize( input.normal ), normalize( -lightVec ) );
   p = p * 0.5f + 0.5;
   p = p * p;
   
	float4 color =  p * tex2D( sampler0, input.uv );
	color.a = 1.0f;
	return color;
}

//	テクスチャなし
float4 mainPS2( VsOutput input ) : COLOR 
{
	float4 lightVec = lightDir - lightPos;
   float4 Out;
   float p = dot( normalize( input.normal ), normalize( -lightVec ) );
   p = p * 0.5f + 0.5;
   p = p * p;
   
	float4 color =  p * diffuse;
	color.a = 1.0f;
	return color;
}

technique Standard 
{
	pass p0 
	{
	
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CULLMODE			= None;
		VertexShader     = compile vs_2_0 mainVS();
		PixelShader      = compile ps_2_0 mainPS();
	}
	pass p1 
	{
	
		AlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CULLMODE			= None;
		VertexShader     = compile vs_2_0 mainVS();
		PixelShader      = compile ps_2_0 mainPS2();
	}
}
