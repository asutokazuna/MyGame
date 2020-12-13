// パラメータ
struct VS_INPUT {
	float3	Position	: POSITION;
	float3	Normal		: NORMAL;
	float2	TexCoord	: TEXCOORD0;
	float4	Color		: COLOR0;
};

struct VS_OUTPUT {
	float3	Position	: POSITION;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.Position = input.Position;
	output.Normal = input.Normal;
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;
	return output;
}