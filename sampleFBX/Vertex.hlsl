// 頂点シェーダ

// グローバル
cbuffer global : register(b0) {
	matrix g_mWVP;
	matrix g_mWorld;
	matrix g_mTexture;
};

cbuffer global_shadowCamera : register(b3)
{
	float4x4 cameraview;
}
// パラメータ
struct VS_INPUT {
	float3	Position	: POSITION;
	float3	Normal		: NORMAL;
	float2	TexCoord	: TEXCOORD0;
	float4	Diffuse		: COLOR0;
};

struct VS_OUTPUT {
	float4	Position	: SV_Position;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Diffuse		: COLOR0;
	float4 lightpos :TEXCOORD3;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 P = float4(input.Position, 1.0f);
	output.Position = mul(P, g_mWVP);
	output.Pos4PS = mul(P, g_mWorld).xyz;
	output.Normal = mul(float4(input.Normal, 0.0f), g_mWorld).xyz;
	output.TexCoord = mul(float4(input.TexCoord, 0.0f, 1.0f), g_mTexture).xy;
	output.Diffuse = input.Diffuse;
	output.lightpos = mul(float4(output.Pos4PS,1), cameraview);
	return output;
}
