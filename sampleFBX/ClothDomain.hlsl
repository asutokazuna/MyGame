// パラメータ
struct DS_OUTPUT {
	float4	Position	: SV_POSITION;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};
struct DS_IN {
	float3	Position	: POSITION;
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

// 出力パッチ定数データ。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[4]			: SV_TessFactor; // たとえば、クワド ドメインの [4] になります
	float InsideTessFactor[2]			: SV_InsideTessFactor; // たとえば、クワド ドメインの Inside[2] になります
	// TODO: 他のスタッフの変更/追加
};

#define NUM_CONTROL_POINTS 4

[domain("quad")]
DS_OUTPUT main(
	HS_CONSTANT_DATA_OUTPUT input,
	float2 domain : SV_DomainLocation,
	const OutputPatch<DS_IN, NUM_CONTROL_POINTS> patch)
{
	DS_OUTPUT Output;
// 頂点座標
  	float3 p1 = lerp( patch[1].Position, patch[0].Position, domain.x );
  	float3 p2 = lerp( patch[3].Position, patch[2].Position, domain.x );
	float3 p3 = lerp( p1, p2, domain.y );

	float3 n1 = lerp( patch[1].Normal, patch[0].Normal, domain.x );
	float3 n2 = lerp( patch[3].Normal, patch[2].Normal, domain.x );
	float3 n3 = lerp( n1, n2, domain.y );


  // テクセル
  float2 t1 = lerp( patch[1].TexCoord, patch[0].TexCoord, domain.x );
  float2 t2 = lerp( patch[3].TexCoord, patch[2].TexCoord, domain.x );
  float2 t3 = lerp( t1, t2, domain.y );
 Output.TexCoord = mul(float4(t3, 0.0f, 1.0f), g_mTexture).xy;

 
  float4 c1 = lerp( patch[1].Color, patch[0].Color, domain.x );
  float4 c2 = lerp( patch[3].Color, patch[2].Color, domain.x );
  float4 c3 = lerp( c1, c2, domain.y );

  Output.Color=  c3;

	float poswave = sin(value.x + (t3.x * t3.x + t3.y * t3.y) * 2) * 0.2;

	p3.x += poswave;
	//p3.z += poswave.x;
	p3.y += poswave;

	float2 normaloff = -cos(value.x + (t3.x * t3.x + t3.y * t3.y) * 2);

	n3.x += normaloff.x + normaloff.y;
	n3.y += normaloff.x + normaloff.y;

	n3 = normalize(n3);

	Output.Position=  mul( float4( p3, 1.0f ), g_mWVP );
	Output.Pos4PS = mul(p3, g_mWorld).xyz;

	Output.Normal = mul(n3, g_mWorld);
	//float4 P = Output.Position;
	//Output.Position = mul(P, g_mWVP);
	//Output.Pos4PS = mul(P, g_mWorld).xyz;
	//Output.Normal = mul(float4(Output.Normal, 0.0f), g_mWorld).xyz;
	//Output.TexCoord = mul(float4(Output.TexCoord, 0.0f, 1.0f), g_mTexture).xy;

	return Output;
}
