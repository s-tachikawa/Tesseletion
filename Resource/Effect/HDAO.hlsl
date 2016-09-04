// HDAO

//! �R���X�^���g�o�b�t�@
cbuffer global : register(b0)
{
	float4	g_ScreenParam		: packoffset( c0 );		// (width, height, 1.0/width, 1.0/height)
	float4	g_ProjParam			: packoffset( c1 );		// (near, far, tan(fovy), aspect)
	float	g_CheckRadius		: packoffset( c2.x );
	float	g_RejectDepth		: packoffset( c2.y );
	float	g_AcceptDepth		: packoffset( c2.z );
	float	g_Intensity			: packoffset( c2.w );
	float	g_AcceptAngle		: packoffset( c3.x );
	int		g_UseNormal			: packoffset( c3.y );
	float	g_NormalScale		: packoffset( c3.z );
	float	g_Offset : packoffset(c3.w);
};

//! �e�N�X�`���ƃT���v��
Texture2D			texNormalDepth		: register( t0 );
//Texture2D			texHalfNormalDepth	: register( t1 );
//Texture2D			texHDAO				: register( t2 );
SamplerState		samPoint			: register( s0 );
//SamplerState		samLinear			: register( s1 );

// �����O�̌��Ǝ擾�s�N�Z���̌�
#define RING_MAX			(4)
#define NUM_RING_1_GATHERS	(2)
#define NUM_RING_2_GATHERS	(6)
#define NUM_RING_3_GATHERS	(12)
#define NUM_RING_4_GATHERS	(20)

// �T���v�����O�p�^�[��
static const float2 kRingPattern[NUM_RING_4_GATHERS] = 
{
	// Ring 1
	{ 1, -1 },
	{ 0, 1 },

	// Ring 2
	{ 0, 3 },
	{ 2, 1 },
	{ 3, -1 },
	{ 1, -3 },
	    
	// Ring 3
	{ 1, -5 },
	{ 3, -3 },
	{ 5, -1 },
	{ 4, 1 },
	{ 2, 3 },
	{ 0, 5 },

	// Ring 4
	{ 0, 7 },
	{ 2, 5 },
	{ 4, 3 },
	{ 6, 1 },
	{ 7, -1 },
	{ 5, -3 },
	{ 3, -5 },
	{ 1, -7 },
};

// �E�F�C�g
static const float4 kRingWeight[NUM_RING_4_GATHERS] = 
{
	// Ring 1 (Sum = 5.30864)
	{ 1.00000, 0.50000, 0.44721, 0.70711 },
	{ 0.50000, 0.44721, 0.70711, 1.00000 },

	// Ring 2 (Sum = 6.08746)
	{ 0.30000, 0.29104, 0.37947, 0.40000 },
	{ 0.42426, 0.33282, 0.37947, 0.53666 },
	{ 0.40000, 0.30000, 0.29104, 0.37947 },
	{ 0.53666, 0.42426, 0.33282, 0.37947 },

	// Ring 3 (Sum = 6.53067)
	{ 0.31530, 0.29069, 0.24140, 0.25495 },
	{ 0.36056, 0.29069, 0.26000, 0.30641 },
	{ 0.26000, 0.21667, 0.21372, 0.25495 },
	{ 0.29069, 0.24140, 0.25495, 0.31530 },
	{ 0.29069, 0.26000, 0.30641, 0.36056 },
	{ 0.21667, 0.21372, 0.25495, 0.26000 },

	// Ring 4 (Sum = 7.00962)
	{ 0.17500, 0.17365, 0.19799, 0.20000 },
	{ 0.22136, 0.20870, 0.24010, 0.25997 },
	{ 0.24749, 0.21864, 0.24010, 0.28000 },
	{ 0.22136, 0.19230, 0.19799, 0.23016 },
	{ 0.20000, 0.17500, 0.17365, 0.19799 },
	{ 0.25997, 0.22136, 0.20870, 0.24010 },
	{ 0.28000, 0.24749, 0.21864, 0.24010 },
	{ 0.23016, 0.22136, 0.19230, 0.19799 },
};

// �E�F�C�g�l�̍��v
static const float kTotalRingWeight[RING_MAX] =
{
	5.30864,
	11.39610,
	17.92677,
	24.93639,
};

// �@���`�F�b�N�p�^�[��
#define NUM_NORMAL_LOADS	(4)
static const int2 kNormalPattern[NUM_NORMAL_LOADS] = 
{
	{ 1, 8 },
	{ 8, -1 },
	{ 5, 4 },
	{ 4, -4 },
};

//! ���_����
struct OutputVS
{
	float4	pos			: SV_POSITION;
	float2	texCoord0	: OUT_TEXCOORD0;
};

//! ���_�V�F�[�_
OutputVS RenderFullScreenVS(float4 Pos : POSITION,float2 Tex : TEXCOORD0)
{
	OutputVS	outVert;
	/*
	// ���W�v�Z
	float	x = (float)(vertexID & 0x01);
	float	y = (float)((vertexID >> 1) & 0x01);
	outVert.pos = float4( x * 2.0 - 1.0, y * -2.0 + 1.0, 1.0, 1.0 );

	// UV�v�Z
	float2	uv = { x, y };
	outVert.texCoord0 = uv;
	*/
	/*
	*/
	outVert.pos = Pos;
	outVert.texCoord0 = Tex;

	return outVert;
}

//! �T���v�����O���郊���O�̐������߂�
int CalcRings( float depth )
{
	float z = depth * g_ProjParam.y;
	float pixel = (g_CheckRadius / (z * g_ProjParam.z)) * (g_ScreenParam.y * 0.5);
	return (int)(pixel / 2.0);		// �����O1�ɂ�2�s�N�Z����
}

//! ���ʂɂǂ̒��x�߂������ׂ�
float CheckNormalPattern( int2 texCoord )
{
	float summed = 0.0f;

	for (int i = 0; i < NUM_NORMAL_LOADS; ++i)
	{
		// �p�^�[���ɏ]���A�@�����擾����
		int2 mirror_pattern = (kNormalPattern[i] + int2(1, 1)) * int2(-1, -1);
			int2 t0 = texCoord + kNormalPattern[i];
			int2 t1 = texCoord + mirror_pattern;
			float3 n1 = texNormalDepth.Load(int3(t0, 0)).xyz;
			float3 n2 = texNormalDepth.Load(int3(t1, 0)).xyz;

			float d = dot(n1, n2);
		summed += (d > g_AcceptAngle) ? 0.0f : (1.0 - (abs(d) * 0.25));
	}

	return 0.5 + summed * 0.25;
}

//! �s�N�Z���V�F�[�_
float4 RenderHDAOPS( OutputVS inPixel ) : SV_TARGET
{
	
	int2 texInt = (int2)(inPixel.texCoord0 * g_ScreenParam.xy + float2(0.1, 0.1));

	// �����Ώۂ̃s�N�Z�����擾
	float4	nd_center = texNormalDepth.Load(int3(texInt, 0));
	float	offset_center = nd_center.w - nd_center.z * g_NormalScale;

	// �����ɉ����ăT���v�����O���郊���O�̐���ύX����
	int numRings = min(CalcRings(nd_center.w), RING_MAX);
	//if (numRings == 0)
	//{	// ��������������̂ŋp��
	//	return float4(0, 1, 1, 1);
	//}

	// �ߗׂ̖@���p�^�[�����`�F�b�N���A���ʂɂ��邩�ǂ������ׂ�
	float	fd = CheckNormalPattern(texInt);

	//if (fd <= 0.5)
	//{	// ���ʂƔF�������̂ŋp��
	//	return float4(1, 1, 1, 1);
	//}

	// �T���v���񐔂�ݒ肷��
	int numSamples = NUM_RING_1_GATHERS;
	switch (numRings)
	{
	case 2: numSamples = NUM_RING_2_GATHERS; break;
	case 3: numSamples = NUM_RING_3_GATHERS; break;
	case 4: numSamples = NUM_RING_4_GATHERS; break;
	}

	// �T���v���񐔕��������[�v
	float4 occ4 = (float4)0;
		for (int i = 0; i < numSamples; ++i)
		{
		// �I�t�Z�b�g�ɏ]����8�s�N�Z�����t�F�b�`
		int2 mirror_pattern = (kRingPattern[i] + int2(1, 1)) * int2(-1, -1);
			int2 t0 = texInt + kRingPattern[i];
			int2 t1 = texInt + mirror_pattern;
			float4 pixels_p[4] =
		{
			texNormalDepth.Load(int3(t0, 0), int2(0, 1)),
			texNormalDepth.Load(int3(t0, 0), int2(1, 1)),
			texNormalDepth.Load(int3(t0, 0), int2(1, 0)),
			texNormalDepth.Load(int3(t0, 0), int2(0, 0))
		};
		float4 pixels_n[4] =
		{
			texNormalDepth.Load(int3(t1, 0), int2(0, 1)),
			texNormalDepth.Load(int3(t1, 0), int2(1, 1)),
			texNormalDepth.Load(int3(t1, 0), int2(1, 0)),
			texNormalDepth.Load(int3(t1, 0), int2(0, 0))
		};

		// �[�x���`�F�b�N����
		float4 depth0 = float4(pixels_p[0].w, pixels_p[1].w, pixels_p[2].w, pixels_p[3].w);
			float4 depth1 = float4(pixels_n[0].w, pixels_n[1].w, pixels_n[2].w, pixels_n[3].w);

			float4 diff = nd_center.wwww - depth0;
			float4 compare0 = ((diff < g_RejectDepth.xxxx) ? 1.0 : 0.0) * ((diff > g_AcceptDepth.xxxx) ? 1.0 : 0.0);
			diff = nd_center.wwww - depth1;
		float4 compare1 = ((diff < g_RejectDepth.xxxx) ? 1.0 : 0.0) * ((diff > g_AcceptDepth.xxxx) ? 1.0 : 0.0);

			occ4 += kRingWeight[i].xyzw * (compare0.xyzw * compare1.zwxy) * fd;

		// �@�����g�p����ꍇ
		if (g_UseNormal)
		{
			// �@�������ɐ[�x�����炷
			float4 normal0 = float4(pixels_p[0].z, pixels_p[1].z, pixels_p[2].z, pixels_p[3].z);
				float4 normal1 = float4(pixels_n[0].z, pixels_n[1].z, pixels_n[2].z, pixels_n[3].z);

				// NOTE: �o�b�t�@�ɕۑ����ꂽ�[�x�͐��̒l�����A�@���̓X�N���[����������-1�Ƃ��Ă���
				depth0 -= normal0 * g_NormalScale;
			depth1 -= normal1 * g_NormalScale;

			diff = offset_center.xxxx - depth0;
			compare0 = ((diff < g_RejectDepth.xxxx) ? 1.0 : 0.0) * ((diff > g_AcceptDepth.xxxx) ? 1.0 : 0.0);

			diff = offset_center.xxxx - depth1;
			compare1 = ((diff < g_RejectDepth.xxxx) ? 1.0 : 0.0) * ((diff > g_AcceptDepth.xxxx) ? 1.0 : 0.0);

			occ4 += kRingWeight[i].xyzw * (compare0.xyzw * compare1.zwxy) * fd;
		}
		}

	// �I�N���[�W�����̒l�𐮌`����
	float occ;
	if (g_UseNormal)
	{
		occ = dot(occ4, float4(1, 1, 1, 1)) / (3.0 * kTotalRingWeight[numRings - 1]);
	}
	else
	{
		occ = dot(occ4, float4(1, 1, 1, 1)) / (2.0 * kTotalRingWeight[numRings - 1]);
	}
	occ = 1.0 - saturate(occ * g_Intensity);

	return float4(occ, occ, occ, 1.0f);
}
/*
float4 RenderUpsamplingPS( OutputVS inPixel ) : SV_TARGET
{
const float2 kScreenSize = g_ScreenParam.xy * 2.0;
const float2 kScreenHalfSize = g_ScreenParam.xy;
const float4 kBilinearWeights[4] =
{
float4( 9.0/16.0, 3.0/16.0, 3.0/16.0, 1.0/16.0 ),
float4( 3.0/16.0, 9.0/16.0, 1.0/16.0, 3.0/16.0 ),
float4( 3.0/16.0, 1.0/16.0, 9.0/16.0, 3.0/16.0 ),
float4( 1.0/16.0, 3.0/16.0, 3.0/16.0, 9.0/16.0 )
};

// Hi-Res�s�N�Z���̃C���f�b�N�X�����߂�
int2 hiResUV = (int2)(inPixel.texCoord0 * kScreenSize + float2(0.1, 0.1));
int hiResIndex = (1 - (hiResUV.y & 0x01)) * 2 + (1 - (hiResUV.x & 0x01));
float4 hiResND = texNormalDepth.Load( int3(hiResUV, 0), int2(0, 0) );

// Low-Res����4�s�N�Z���̖@���E�[�x�����߂�
int2 lowResUV = (int2)(inPixel.texCoord0 * kScreenHalfSize.xy + float2(0.1, 0.1));
float4 lowResND[4];
float lowResAO[4];
switch (hiResIndex)
{
case 0:
lowResND[0] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, 0) );
lowResND[1] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(1, 0) );
lowResND[2] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, 1) );
lowResND[3] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(1, 1) );
lowResAO[0] = texHDAO.Load( int3(lowResUV, 0), int2(0, 0) ).r;
lowResAO[1] = texHDAO.Load( int3(lowResUV, 0), int2(1, 0) ).r;
lowResAO[2] = texHDAO.Load( int3(lowResUV, 0), int2(0, 1) ).r;
lowResAO[3] = texHDAO.Load( int3(lowResUV, 0), int2(1, 1) ).r;
break;
case 1:
lowResND[0] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(-1, 0) );
lowResND[1] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, 0) );
lowResND[2] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(-1, 1) );
lowResND[3] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, 1) );
lowResAO[0] = texHDAO.Load( int3(lowResUV, 0), int2(-1, 0) ).r;
lowResAO[1] = texHDAO.Load( int3(lowResUV, 0), int2(0, 0) ).r;
lowResAO[2] = texHDAO.Load( int3(lowResUV, 0), int2(-1, 1) ).r;
lowResAO[3] = texHDAO.Load( int3(lowResUV, 0), int2(0, 1) ).r;
break;
case 2:
lowResND[0] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, -1) );
lowResND[1] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(1, -1) );
lowResND[2] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, 0) );
lowResND[3] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(1, 0) );
lowResAO[0] = texHDAO.Load( int3(lowResUV, 0), int2(0, -1) ).r;
lowResAO[1] = texHDAO.Load( int3(lowResUV, 0), int2(1, -1) ).r;
lowResAO[2] = texHDAO.Load( int3(lowResUV, 0), int2(0, 0) ).r;
lowResAO[3] = texHDAO.Load( int3(lowResUV, 0), int2(1, 0) ).r;
break;
case 3:
lowResND[0] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(-1, -1) );
lowResND[1] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, -1) );
lowResND[2] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(-1, 0) );
lowResND[3] = texHalfNormalDepth.Load( int3(lowResUV, 0), int2(0, 0) );
lowResAO[0] = texHDAO.Load( int3(lowResUV, 0), int2(-1, -1) ).r;
lowResAO[1] = texHDAO.Load( int3(lowResUV, 0), int2(0, -1) ).r;
lowResAO[2] = texHDAO.Load( int3(lowResUV, 0), int2(-1, 0) ).r;
lowResAO[3] = texHDAO.Load( int3(lowResUV, 0), int2(0, 0) ).r;
break;
}

// �@���̃E�F�C�g�����߂�
float totalWeight = 0.0;
float ao = 0.0;
for( int i = 0; i < 4; ++i )
{
// �@���̃E�F�C�g�����߂�
float normalWeight = dot( lowResND[i].xyz, hiResND.xyz );
normalWeight = pow( saturate(normalWeight), 32.0 );

// �[�x�̃E�F�C�g�����߂�
float depthDiff = hiResND.w - lowResND[i].w;
float depthWeight = 1.0 / (1.0 + abs(depthDiff));

// ��������
float weight = normalWeight * depthWeight * kBilinearWeights[hiResIndex][i];
totalWeight += weight;
ao += lowResAO[i] * weight;
}

ao /= totalWeight;

return float4(ao, ao, ao, 1);
}
*/

