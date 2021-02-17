// �s�N�Z���V�F�[�_

// �O���[�o��
cbuffer global : register(b1) {
	float4	g_vEye;			// ���_���W
	// ����
	float4	g_vLightDir;	// ��������
	float4	g_vLa;			// ����
	float4	g_vLd;			// �g�U���ˌ�
	float4	g_vLs;			// ���ʔ��ˌ�
	// �}�e���A��
	float4	g_vKa;			// �A���r�G���g�F(+�e�N�X�`���L��)
	float4	g_vKd;			// �f�B�t���[�Y�F
	float4	g_vKs;			// �X�y�L�����F(+�X�y�L�������x)
	float4	g_vKe;			// �G�~�b�V�u�F
};

// �p�����[�^
struct VS_OUTPUT {
	float4	Position	: SV_Position;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Diffuse		: COLOR0;
	float4 lightpos :TEXCOORD3;
};

Texture2D    g_texture : register(t0);	// �e�N�X�`��
SamplerState g_sampler : register(s0);	// �T���v��
SamplerState g_samplershadow : register(s1);	// �T���v��
Texture2D    g_texShadow	: register(t3);	// ?????e?N?X?`??

float4 main(VS_OUTPUT input) : SV_Target0
{
	float3 Diff = input.Diffuse.rgb * g_vKd.rgb;
	float Alpha = input.Diffuse.a * g_vKd.a;
		// �������猩�����W��UV�l�Ŏ擾
	float2 shadowUV ;
	shadowUV.x = 0.5f + (input.lightpos.x / input.lightpos.w * 0.5f);
	shadowUV.y = 0.5f - (input.lightpos.y / input.lightpos.w * 0.5f);
	// �`�悷����W�̐[�x�l���v�Z
	float depth = input.lightpos.z / input.lightpos.w;
	// �e�N�X�`���̐[�x�l���擾
	float shadowDepth = g_texShadow.Sample(g_samplershadow, shadowUV).r;

	if (g_vKa.a > 0.0f) {
		// �e�N�X�`���L
		float4 vTd = g_texture.Sample(g_sampler, input.TexCoord);
		Diff *= vTd.rgb;
		Alpha *= vTd.a;
	}
	clip(Alpha - 0.0001f);
	//if (Alpha <= 0.0f) discard;

	if (g_vLightDir.x != 0.0f || g_vLightDir.y != 0.0f || g_vLightDir.z != 0.0f) {
		// �����L��
		float3 L = normalize(-g_vLightDir.xyz);				// �����ւ̃x�N�g��
		float3 N = normalize(input.Normal);					// �@���x�N�g��
		float3 V = normalize(g_vEye.xyz - input.Pos4PS);	// ���_�ւ̃x�N�g��
		float3 H = normalize(L + V);						// �n�[�t�x�N�g��
		Diff = g_vLa.rgb * g_vKa.rgb + g_vLd.rgb *
			Diff * saturate(dot(L, N));						// �g�U�F + ���F
		float3 Spec = g_vLs.rgb * g_vKs.rgb *
			pow(saturate(dot(N, H)), g_vKs.a);				// ���ʔ��ːF
		Diff += Spec;
	}

	Diff += g_vKe.rgb;										// �����F
	if(depth > shadowDepth+0.0001f)
	{
		Diff.rgb *= 0.3f;
	}
	return float4(Diff, Alpha);
}
