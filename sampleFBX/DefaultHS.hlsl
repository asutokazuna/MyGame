// 入力制御点
struct HS_IN {
	float3	Position	: POSITION;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};

struct HS_OUT {
	float3	Position	: POSITION;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Color		: COLOR0;
};

// 出力パッチ定数データ。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[4]			: SV_TessFactor; 	//!< 辺の分割数
	float InsideTessFactor[2]			: SV_InsideTessFactor; 	//!< 内部の分割数
};

#define NUM_CONTROL_POINTS 4

cbuffer globalTessFactor : register(b0)
{
	float4 g_Factor;	//!< x:辺の分割数, y:中の分割数,　z w未使用
};

HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<HS_IN, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// ここにコードを挿入して出力を計算します
	Output.EdgeTessFactor[0] = 
		Output.EdgeTessFactor[1] = 
		Output.EdgeTessFactor[2] = 
		Output.EdgeTessFactor[3] = g_Factor.x;
		Output.InsideTessFactor[0] = // たとえば、代わりに動的テセレーション係数を計算できます
		Output.InsideTessFactor[1] = g_Factor.y; // たとえば、代わりに動的テセレーション係数を計算できます

	return Output;
}

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_OUT main( 
	InputPatch<HS_IN, NUM_CONTROL_POINTS> ip, 
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID )
{
	HS_OUT Output;

	// ここにコードを挿入して出力を計算します
	Output.Position = ip[i].Position;
	Output.Normal = ip[i].Normal;
	Output.TexCoord = ip[i].TexCoord;
	Output.Color = ip[i].Color;

	return Output;
}

// EOF