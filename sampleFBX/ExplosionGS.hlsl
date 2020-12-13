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

[maxvertexcount(3)]
void main(
	triangle GS_IN input[3], 
	inout TriangleStream< GS_OUT > TriStream
)
{
	//float2 dist;
	float2 maxdist = 0;
	float scalar = 0;
	for(int i = 0; i < 3; i++)
	{
		if( scalar < abs(dot(input[i].TexCoord.x * 2 - 1, input[i].TexCoord.y * 2 - 1)))
		{
			scalar = abs(dot(input[i].TexCoord.x * 2 - 1, input[i].TexCoord.y * 2 - 1));
			maxdist = input[i].TexCoord;
		}
	}
	
	GS_OUT output;
	float2 pos;
	float angle = value.y;
	float2x2 rotate = float2x2(cos(angle), -sin(angle), sin(angle), cos(angle));

	float2 end;
	float2 start;
	float2 ctrlpoint;
	float  temp;

	for (uint i = 0; i < 3; i++)
	{

		pos.x = input[i].Position.x +  (maxdist.x * 2 - 1) * 5;
		pos.y = input[i].Position.y + -(maxdist.y * 2 - 1) * 5;
		start = pos;
		end = input[i].Position;
		temp = rand(input[i].TexCoord);
		ctrlpoint.x = (start.x + end.x) + temp;
		ctrlpoint.y = (start.y + end.y) + temp;

		pos.x = calcBezier(start.x, ctrlpoint.x, end.x,value.y);
		pos.y = calcBezier(start.y, ctrlpoint.y, end.y,value.y);

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