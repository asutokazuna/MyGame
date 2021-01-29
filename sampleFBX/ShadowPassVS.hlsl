// 頂点シェーダ

// グローバル
cbuffer global : register(b0) {
	matrix g_mWVP;
	matrix g_mWorld;
	matrix g_mTexture;
};

// パラメータ
struct VS_INPUT {
	float3	Position	: POSITION;
	float3	Normal		: NORMAL;
	float2	TexCoord	: TEXCOORD0;
	float4	Diffuse		: COLOR0;
};

struct VS_OUTPUT {
	float4	Position	: SV_Position;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 P = float4(input.Position, 1.0f);
	output.Position = mul(P, g_mWVP);
	return output;
}
