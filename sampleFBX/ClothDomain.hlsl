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

 
  float4 c1 = lerp( patch[1].Color, patch[0].Color, domain.x );
  float4 c2 = lerp( patch[3].Color, patch[2].Color, domain.x );
  float4 c3 = lerp( c1, c2, domain.y );

  Output.Color=  c3;

	float d = t3.x * t3.x + t3.y * t3.y;
//	float d = t3.x  + t3.y;
	float t =value.x + ( d)* 2;

	float poswave = sin((t)) * 0.1f;

/*
	p3.x += poswave;
	//p3.z += poswave.x;
	p3.y += poswave;

	float2 normaloff = -cos((t))*0.1f;

	n3.x = normaloff.x + normaloff.y;
	n3.y = normaloff.x + normaloff.y;
	n3.z = -500;
	//n3.xy = normaloff;
	n3 = normalize(n3);
	
	//float dwave = 10 * cos(t) * 0.1f;
	//n3 = normalize(float3(dwave,dwave,1));
*/


float _WaveFreq1 = 3;
float _WaveSpeed1 = 1;
float _WaveAmplitude1 = value.y;

float _WaveFreq2 = 2;
float _WaveSpeed2 = 0.5;
float _WaveAmplitude2 = 0.05f;
    // UVの斜め方向のパラメータを t と定義します
    t =t3.x + t3.y;
    t = t3.x * t3.x + t3.y * t3.y;

    // 周波数とスクロール速度から t1 を決定します
    float ang1 = _WaveFreq1 * t + _WaveSpeed1 * value.x ;

    // 波の高さ wave1 を計算します
    float wave1 = _WaveAmplitude1 * sin(ang1);

    // wave1 を t1 で偏微分した dWave1 を計算します
    float dWave1 = _WaveFreq1 * _WaveAmplitude1 * cos(ang1);

    // wave1 と同様にして wave2 を計算します
    float ang2 = _WaveFreq2 * t + _WaveSpeed2 *  value.x ;
    float wave2 = _WaveAmplitude2 * sin(ang2);
    float dWave2 = _WaveFreq2 * _WaveAmplitude2 * cos(ang2);

    // 上部を固定するための値を計算します
    float fixTopScale = (1.0f - t3.y);

    // 2つの波を合成して、頂点座標に反映します
    //float wave = fixTopScale * (wave1 + wave2);
    float wave = (wave1 + wave2);
    //p3 += wave;
    p3 += wave1;

    // 波（位置）を偏微分した勾配から、法線を計算します
    float dWave = fixTopScale * (dWave1 + dWave2);
    //n3 = normalize(float3(dWave, dWave, -100.0f));
    n3 = normalize(float3(dWave1, dWave1, -100.0f));
    //float3 objNormal = normalize(float3(dWave, dWave, -1.0f));
    //o.normal = mul((float3x3)unity_ObjectToWorld, objNormal);

// t3.x += value.x / 80;
// t3.y += value.x / 100;

	Output.Position=  mul( float4( p3, 1.0f ), g_mWVP );
	Output.Pos4PS = mul(p3, g_mWorld).xyz;

	Output.Normal = mul(n3, g_mWorld);
 Output.TexCoord = mul(float4(t3, 0.0f, 1.0f), g_mTexture).xy;
	//float4 P = Output.Position;
	//Output.Position = mul(P, g_mWVP);
	//Output.Pos4PS = mul(P, g_mWorld).xyz;
	//Output.Normal = mul(float4(Output.Normal, 0.0f), g_mWorld).xyz;
	//Output.TexCoord = mul(float4(Output.TexCoord, 0.0f, 1.0f), g_mTexture).xy;

	return Output;
}
