// �萔�o�b�t�@�O
// �O���[�o���ϐ�
cbuffer cbBuffer0 : register(b0)
{
	// ��D��
	column_major float4x4 g_matWVP : packoffset(c0);   // ���[���h �~ �r���[ �~ �ˉe �s��
};

// �萔�o�b�t�@�P
cbuffer cbBuffer1 : register(b1)
{
	float g_TessFactor : packoffset(c0.x);   // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
	float g_InsideTessFactor : packoffset(c0.y);   // �p�b�`�����̃e�b�Z���[�V�����W��
};

// �e�N�X�`���[
Texture2D g_Tex : register(t0);

// �T���v���[�X�e�[�g
SamplerState  g_Sampler;

// ���_�V�F�[�_�[�̓��̓p�����[�^
struct VS_IN
{
	float3 pos   : POSITION;   // ���_���W
	float3 normal : NORMAL;
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
	float Edges[3] : SV_TessFactor;        // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
	float Inside : SV_InsideTessFactor; // �p�b�`�����̃e�b�Z���[�V�����W��
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
VS_OUT VS_Main(VS_IN In)
{
	VS_OUT Out;

	// ���_�V�F�[�_�[�ł͂��̂܂ܓn��
	Out.pos = mul(In.pos, g_matWVP);
	//Out.texel = In.texel;
	return Out;
}

// *****************************************************************************************
// �n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y
// *****************************************************************************************
CONSTANT_HS_OUT ConstantsHS_Main(InputPatch<VS_OUT, 3> ip)
{
	CONSTANT_HS_OUT Out;

	// �萔�o�b�t�@�̒l�����̂܂ܓn��
	//Out.Edges[0] = Out.Edges[1] = Out.Edges[2] = g_TessFactor;  // �p�b�`�̃G�b�W�̃e�b�Z���[�V�����W��
	//Out.Inside = g_InsideTessFactor;  // �p�b�`�����̉����@�̃e�b�Z���[�V�����W��
	return Out;
}

// *****************************************************************************************
// �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y
// *****************************************************************************************
[domain("tri")]                             // �e�b�Z���[�g���郁�b�V���̌`����w�肷��
[partitioning("integer")]                    // �p�b�`�̕����Ɏg�p����A���S���Y�����w�肷��(�����ŕ������邩���������_�ŕ������邩)
[outputtopology("triangle_ccw")]             // ���b�V���̏o�͕��@���w�肷��(�����v����܂��͎��v����)
[outputcontrolpoints(3)]                     // �n���V�F�[�_�[�̃R���g���[�� �|�C���g �t�F�[�Y���R�[��������(�ݒ肷��R���g���[���|�C���g�œ���������K�v����)
[patchconstantfunc("ConstantsHS_Main")]      // �Ή�����n���V�F�[�_�[�̃p�b�`�萔�t�F�[�Y�̃��C���֐�
HS_OUT HS_Main(InputPatch<VS_OUT, 3> In, uint i : SV_OutputControlPointID)
{
	HS_OUT Out;

	// ���̂܂ܓn��
	//Out.pos = In[i].pos;
	//Out.texel = In[i].texel;
	return Out;
}

// *****************************************************************************************
// �h���C���V�F�[�_�[
// *****************************************************************************************
[domain("tri")]
DS_OUT DS_Main(CONSTANT_HS_OUT In, float3 uv : SV_DomainLocation, const OutputPatch<HS_OUT, 3> patch)
{
	DS_OUT Out;
	//float3 pos = patch[0].pos * SV_DomainLocation.z + patch[1].pos * SV_DomainLocation.x + patch[2].pos * SV_DomainLocation.y;
	//Out.pos = float4(pos,1.0f);
	//Out.pos = mul(Out.pos, g_matWVP);
	return Out;
}

// *****************************************************************************************
// �s�N�Z���V�F�[�_
// *****************************************************************************************
float4 PS_Main(DS_OUT In) : SV_TARGET
{
	return g_Tex.Sample(g_Sampler, In.texel);
}