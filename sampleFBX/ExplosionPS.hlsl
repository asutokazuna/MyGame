// ピクセルシェーダ

// グローバル
cbuffer global : register(b1) {
	float4	g_vEye;			// 視点座標
	// 光源
	float4	g_vLightDir;	// 光源方向
	float4	g_vLa;			// 環境光
	float4	g_vLd;			// 拡散反射光
	float4	g_vLs;			// 鏡面反射光
	// マテリアル
	float4	g_vKa;			// アンビエント色(+テクスチャ有無)
	float4	g_vKd;			// ディフューズ色
	float4	g_vKs;			// スペキュラ色(+スペキュラ強度)
	float4	g_vKe;			// エミッシブ色
	float4 value;
};

// パラメータ
struct VS_OUTPUT {
	float4	Position	: SV_Position;
	float3	Pos4PS		: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float2	TexCoord	: TEXCOORD2;
	float4	Diffuse		: COLOR0;
};

Texture2D    g_texture : register(t0);	// テクスチャ
Texture2D    g_noizeTex : register(t1);	// テクスチャ
SamplerState g_sampler : register(s0);	// サンプラ

float4 main(VS_OUTPUT input) : SV_Target0
{
	float3 Diff = input.Diffuse.rgb * g_vKd.rgb;
	float Alpha = input.Diffuse.a * g_vKd.a;
	if (g_vKa.a > 0.0f) {
		// テクスチャ有
		float4 vTd = g_texture.Sample(g_sampler, input.TexCoord);
		Diff *= vTd.rgb;
		Alpha *= vTd.a;
	}
	clip(Alpha - 0.0001f);
	if (Alpha <= 0.0f) discard;

	if(value.x > 0) {
		Alpha = 1 - value.x;
	}

	if (g_vLightDir.x != 0.0f || g_vLightDir.y != 0.0f || g_vLightDir.z != 0.0f) {
		// 光源有効
		float3 L = normalize(-g_vLightDir.xyz);				// 光源へのベクトル
		float3 N = normalize(input.Normal);					// 法線ベクトル
		float3 V = normalize(g_vEye.xyz - input.Pos4PS);	// 視点へのベクトル
		float3 H = normalize(L + V);						// ハーフベクトル

		float3 halframb =  saturate(dot(L, N))*0.5+0.5;

		Diff = g_vLa.rgb * g_vKa.rgb + g_vLd.rgb *
			Diff * halframb;						// 拡散色 + 環境色
		float3 Spec = g_vLs.rgb * g_vKs.rgb *
			pow(saturate(dot(N, H)), g_vKs.a);				// 鏡面反射色
	}

	return float4(Diff, Alpha);
}

// EOF