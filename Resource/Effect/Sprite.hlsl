

Texture2D g_texDecal: register(t0);//�e�N�X�`���[
SamplerState g_samLinear : register(s0);//�T���v���[

//�\����
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//���_�V�F�[�_�[
VS_OUTPUT VS( float4 Pos : POSITION ,float2 Tex : TEXCOORD )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
   //output.Pos = mul( Pos, g_mWorldProj );
   //output.Pos.x = Pos.x * ( 2.0f / 680.0f );
   //output.Pos.y = Pos.y * ( 2.0f / 480.0f );
   output.Pos = Pos;
    output.Tex  = Tex;

    return output;
}

//VS_OUTPUT VS( float4 Pos : POSITION )
//{
//    VS_OUTPUT output = (VS_OUTPUT)0;
//    output.Pos = mul( Pos, g_mWVP );

//    return output;
//}

//�s�N�Z���V�F�[�_�[
float4 PS( VS_OUTPUT input  ) : SV_Target
{
	float4 outColor = g_texDecal.Sample( g_samLinear, input.Tex );
	return outColor;
	//return float4( 1.0f, 0.0, 1.0, 1.0f );
}