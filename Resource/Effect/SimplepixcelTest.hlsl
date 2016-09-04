
// �O���[�o���ϐ�
//! �R���X�^���g�o�b�t�@
cbuffer global : register(b0)
{
	float4	g_ScreenParam		: packoffset(c0);		// (width, height, 1.0/width, 1.0/height)
	float4	g_ProjParam			: packoffset(c1);		// (near, far, tan(fovy), aspect)
	float1	g_CheckRadius : packoffset(c2.x);
	float1	g_RejectDepth : packoffset(c2.y);
	float1	g_AcceptDepth : packoffset(c2.z);
	float1	g_Intensity : packoffset(c2.w);
	float	g_AcceptAngle : packoffset(c3.x);
	float	g_UseNormal : packoffset(c3.y);
	float	g_NormalScale : packoffset(c3.z);
	float	g_Offset : packoffset(c3.w);
};

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
   // output.Pos = mul( Pos, g_mWVP );
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
	//float4 outColor = g_texDecal.Sample( g_samLinear, input.Tex ) + float4( 0.0f, 0.0, 0.0, 1.0f );
	//return outColor;
	if (g_ScreenParam.x > 1.0f)
	{
		return float4(1.0f, 0.0, 0.0, 1.0f);
	}
	else
	{
		return float4(0.0f, 0.0, 0.0, 1.0f);
	}
	//return float4( 1.0f, 0.0, 1.0, 1.0f );
}