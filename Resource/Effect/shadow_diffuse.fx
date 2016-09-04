//------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------
float4x4 	g_world;
float4x4 	g_world_inv;
float4x4 	g_view;
float4x4 	g_proj;
float4		g_color0;
float4		g_color1;
float4		g_light_dir;
texture		g_texture;

texture 	g_shadowbuf;
float4		g_offset;
float4x4	g_vlp;

//------------------------------------------------
// �e�N�X�`���T���v��
//------------------------------------------------
sampler TextureSampler = 
sampler_state
{
    Texture = <g_texture>;
	MipFilter = NONE;
    MinFilter = LINEAR;
    MagFilter = LINEAR;

	AddressU =Clamp;
	AddressV =Clamp;
};	


sampler ShadowBufSampler = 
sampler_state
{
    Texture = <g_shadowbuf>;
    MipFilter = NONE;
    MinFilter = POINT;
    MagFilter = POINT;
	AddressU = Clamp;
	AddressV = Clamp;
};


//------------------------------------------------
// ���_�V�F�[�_
//------------------------------------------------
void BasicVS( 	float3 in_pos : POSITION,
				float3 in_normal : NORMAL,
				float2 in_tex : TEXCOORD0,
 				out float4 out_pos : POSITION,
 				out float4 out_color :COLOR0,
 				out float2 out_tex : TEXCOORD0,
 				out float4 out_pos_light : TEXCOORD1)
{
	// ���W�ϊ�
	float4 world_pos;
	world_pos = mul(float4(in_pos, 1.0f), g_world);
	out_pos = mul(world_pos, g_view);
	out_pos = mul(out_pos, g_proj);

	// �e�N�X�`�����W
	out_tex = in_tex;
	
	// ���_���Ƃ̐F�̌v�Z
	float4 local_light;
	local_light =  normalize( mul(g_light_dir, g_world_inv));
	out_color = saturate(g_color0 + g_color1 * max(0, dot(local_light, in_normal)));
	
	// ��������݂����_�̈ʒu�̌v�Z
	out_pos_light =  mul(world_pos, g_vlp);
}

//------------------------------------------------
// �s�N�Z���V�F�[�_
//------------------------------------------------
void BasicPS( float4 in_color : COLOR0,
 			  float2 in_tex : TEXCOORD0,
 			  float4 in_pos_light : TEXCOORD1,
			  out float4 out_color : COLOR0,
			  uniform bool b_tex)
{
	// �V���h�E�}�b�v����l�̎擾
	float2 shadow_uv = 0.5 * in_pos_light.xy /in_pos_light.w + float2(0.5, 0.5);
	shadow_uv.y = 1.0f - shadow_uv.y;
	shadow_uv .x = shadow_uv.x + g_offset.x;
	shadow_uv .y = shadow_uv.y + g_offset.y;
	float shadow_val =  tex2D(ShadowBufSampler, shadow_uv).r;

	if(b_tex){
		out_color = in_color * tex2D(TextureSampler,in_tex);
	}
	else{
		out_color = in_color;
	}

	// �������璸�_�܂ł̋������v�Z
	float depth = in_pos_light.z / in_pos_light.w;
	
	// �V���h�E�}�b�v�̐[�x�̒l�Ɣ�r
	if( depth - shadow_val> 0.00065f){
		out_color = out_color*0.5; // �e�ɂȂ��Ă���
	}
	
}

//------------------------------------------------
// �e�N�j�b�N�錾
//------------------------------------------------
technique BasicTech
{
    pass P0
    {
        vertexShader = compile vs_2_0 BasicVS();
        pixelShader  = compile ps_2_0 BasicPS(true);
        
	}

}
