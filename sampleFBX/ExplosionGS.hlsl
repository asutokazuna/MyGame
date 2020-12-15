// パラメータ
struct GS_IN {
	float3	Position	: POSITION;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};

struct GS_OUT {
	float4	Position	: SV_POSITION;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};


// グローバル
cbuffer global : register(b0) {
	matrix g_mWVP;
	matrix g_mWorld;
	matrix g_mTexture;
	float4 value;
};

float rand(float2 co){
    return frac(sin(dot(co.xy ,float2(12.9898,78.233))) * 43758.5453);
}

float calcBezier(float start, float ctrl, float end, float t)
{
	return (1 - t) * (1 - t) * start + 2 * (1 - t) * t * ctrl + t *t * end;
}

float calcBezier3(float start, float ctrl, float ctrl2, float end, float t)
{
	return (1 - t) * (1 - t) * (1 - t) * start + 3 * (1 - t) * (1 - t) * t * ctrl + 3 * (1 - t) * t * t * ctrl2 + t*  t *t * end;
}

[maxvertexcount(3)]
void main(
	triangle GS_IN input[3], 
	inout TriangleStream< GS_OUT > TriStream
)
{
	GS_OUT output;

	float2 pos;
	float2 start;
	float2 ctrl;
	float2 ctrl2;
	float2 dist = 0;
	float2 d;
float scalar;

	for (uint i = 0; i < 3; i++)
	{
		dist += input[i].TexCoord * 2 - 1;
		
	}
		float2 dotuv = dot(dist.x / 3,dist.y / 3);
		
		d.x = rand(float2(dotuv.x,dotuv.y)) * 2 - 1;
		d.y = rand(float2(dotuv.y * 2,dotuv.x)) * 2 - 1;

//scalar /= 3;
	float2x2 rotate = float2x2(cos(value.x),-sin(value.x),sin(value.x),cos(value.x));

	for (uint i = 0; i < 3; i++)
	{
		scalar = abs(dot(input[i].TexCoord.x,input[i].TexCoord.y)) ;
		pos = input[i].Position;
		start = float2(scalar,scalar);
		ctrl.x =(d.x + d.y);
		ctrl.y = (d.x * d.y * input[i].Position.y +start)*2;
		ctrl2.x = d.x * 2;
		ctrl2.y = d.y * 5;
		//start.x += d.x * 2;
		//start.y += d.y * 3;

		pos.x = calcBezier3(start.x,ctrl.x,ctrl2.x, input[i].Position.x,clamp(value.y+(1 -scalar) * 0.6,0,1));
		pos.y = calcBezier3(start.y,ctrl.y,ctrl2.y, input[i].Position.y,clamp(value.y+(1 -scalar) * 0.6,0,1));

		pos = mul(pos,rotate);

		// ワールド変換など
		output.Position = mul( float4(pos,input[i].Position.z, 1.0f ), g_mWVP );
		output.Pos4PS = mul(input[i].Position, g_mWorld).xyz;
		output.Normal = mul(input[i].Normal, g_mWorld);
		output.TexCoord =mul(float4(input[i].TexCoord, 0.0f, 1.0f), g_mTexture).xy;
		output.Color = input[i].Color;
		//output.Position.x = output.Position.x + (output.TexCoord.x)*0.25;
		//output.Position.y = output.Position.y + -(output.TexCoord.y)*0.25;
		TriStream.Append(output);
	}

}