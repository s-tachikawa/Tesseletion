// �萔�o�b�t�@�O
// �O���[�o���ϐ�
cbuffer cbBuffer0 : register( b0 )
{
  // ��D��
  column_major float4x4 g_matWVP : packoffset( c0 );   // ���[���h �~ �r���[ �~ �ˉe �s��
};

// �萔�o�b�t�@�P
cbuffer cbBuffer1 : register( b1 )
{
  float g_TessFactor       : packoffset( c0.x );   // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
  float g_InsideTessFactor : packoffset( c0.y );   // �p�b�`�����̃e�b�Z���[�V�����W��
};

// �e�N�X�`���[
Texture2D g_Tex : register( t0 );

// �T���v���[�X�e�[�g
SamplerState  g_Sampler;

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
  float3 pos   : POSITION;   // ���_���W
  float2 texel : TEXCOORD0;  // �e�N�Z��
};

// ���_�V�F�[�_�[�̏o�̓p�����[�^
struct VS_OUT
{
  float3 pos    : POSITION;
  float2 texel  : TEXCOORD0;
};

// �n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y�p�̏o�̓p�����[�^
struct CONSTANT_HS_OUT
{
  float Edges[4] : SV_TessFactor;        // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
  float Inside[2] : SV_InsideTessFactor; // �p�b�`�����̃e�b�Z���[�V�����W��
};

// �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y�p�̏o�̓p�����[�^
struct HS_OUT
{
  float3 pos   : POSITION;
  float2 texel : TEXCOORD0;
};

// �h���C���V�F�[�_�[�̏o�̓p�����[�^
struct DS_OUT
{
  float4 pos   : SV_POSITION;
  float2 texel : TEXCOORD0;
};

// *****************************************************************************************
// ���_�V�F�[�_�[
// *****************************************************************************************
VS_OUT VS_Main( VS_IN In )
{
   VS_OUT Out;

  // ���_�V�F�[�_�[�ł͂��̂܂ܓn��
  Out.pos = In.pos;
  Out.texel = In.texel;
  return Out;
}

// *****************************************************************************************
// �n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y
// *****************************************************************************************
CONSTANT_HS_OUT ConstantsHS_Main( InputPatch<VS_OUT, 4> ip, uint PatchID : SV_PrimitiveID )
{
  CONSTANT_HS_OUT Out;

  // �萔�o�b�t�@�̒l�����̂܂ܓn��
  Out.Edges[0] = Out.Edges[1] = Out.Edges[2] = Out.Edges[3] = g_TessFactor;  // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
  Out.Inside[0] = g_InsideTessFactor;  // �p�b�`�����̉����@�̃e�b�Z���[�V�����W��
  Out.Inside[1] = g_InsideTessFactor;  // �p�b�`�����̏c���@�̃e�b�Z���[�V�����W��
  //Out.Edges[0] = 7;
  //Out.Edges[1] = 9;
  //Out.Edges[2] = 5;
  //Out.Edges[3] = 2;

  //Out.Inside[0] = 7;
  //Out.Inside[1] = 7;
  return Out;
}

// *****************************************************************************************
// �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y
// *****************************************************************************************
[domain("quad")]                             // �e�b�Z���[�g���郁�b�V���̌`����w�肷��
[partitioning("integer")]                    // �p�b�`�̕����Ɏg�p����A���S���Y�����w�肷��(�����ŕ������邩���������_�ŕ������邩)
[outputtopology("triangle_ccw")]             // ���b�V���̏o�͕��@���w�肷��(�����v����܂��͎��v����)
[outputcontrolpoints(4)]                     // �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y���R�[��������(�ݒ肷��R���g���[���|�C���g�œ���������K�v����)
[patchconstantfunc("ConstantsHS_Main")]      // �Ή�����n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y�̃��C���֐�
HS_OUT HS_Main( InputPatch<VS_OUT, 4> In, uint i : SV_OutputControlPointID, uint PatchID : SV_PrimitiveID )
{
  HS_OUT Out;

  // ���̂܂ܓn��
  Out.pos = In[i].pos;
  Out.texel = In[i].texel;
  return Out;
}

// *****************************************************************************************
// �h���C���V�F�[�_�[
// *****************************************************************************************
[domain("quad")]
DS_OUT DS_Main( CONSTANT_HS_OUT In, float2 uv : SV_DomainLocation, const OutputPatch<HS_OUT, 4> patch )
{
  DS_OUT Out;
  
  // ���_���W
  float3 p1 = lerp( patch[1].pos, patch[0].pos, uv.x );
  float3 p2 = lerp( patch[3].pos, patch[2].pos, uv.x );
  float3 p3 = lerp( p1, p2, uv.y );

  Out.pos =  mul( float4( p3, 1.0f ), g_matWVP );

  // �e�N�Z��
  float2 t1 = lerp( patch[1].texel, patch[0].texel, uv.x );
  float2 t2 = lerp( patch[3].texel, patch[2].texel, uv.x );
  float2 t3 = lerp( t1, t2, uv.y );
  Out.texel = t3;

  return Out;
}

// *****************************************************************************************
// �s�N�Z���V�F�[�_
// *****************************************************************************************
float4 PS_Main( DS_OUT In ) : SV_TARGET
{
  return g_Tex.Sample( g_Sampler, In.texel );
}