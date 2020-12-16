// パラメータ
struct DS_OUTPUT {
	float3	Position	: POSITION;
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

// 出力パッチ定数データ。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[4]			: SV_TessFactor;
	float InsideTessFactor[2]			: SV_InsideTessFactor; 
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
	// 法線
	float3 n1 = lerp( patch[1].Normal, patch[0].Normal, domain.x );
	float3 n2 = lerp( patch[3].Normal, patch[2].Normal, domain.x );
	float3 n3 = lerp( n1, n2, domain.y );

	// テクセル
	float2 t1 = lerp( patch[1].TexCoord, patch[0].TexCoord, domain.x );
	float2 t2 = lerp( patch[3].TexCoord, patch[2].TexCoord, domain.x );
	float2 t3 = lerp( t1, t2, domain.y );
	// 色
	float4 c1 = lerp( patch[1].Color, patch[0].Color, domain.x );
	float4 c2 = lerp( patch[3].Color, patch[2].Color, domain.x );
	float4 c3 = lerp( c1, c2, domain.y );

	Output.Position=  p3;
	Output.Normal = n3;
	Output.TexCoord = t3;
	Output.Color=  c3;

	return Output;
}

// EOF