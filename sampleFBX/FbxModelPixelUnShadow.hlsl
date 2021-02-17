// FBXpsNZVF[_ (FbxModelPixel.hlsl)

// O[o
cbuffer global : register(b0) {
	matrix	g_WorldViewProj;	// [h~r[~Ëesń
	matrix	g_World;			// [hsń
	float4	g_cameraPos;		// _ŔW([hóÔ)
	float4	g_lightDir;			// őšűü([hóÔ)
	float4	g_lightAmbient;		// ÂŤő
	float4	g_lightDiffuse;		// gUő
	float4	g_lightSpecular;	// žĘ˝Ëő
};

// }eA
cbuffer global2 : register(b1) {
	float4	g_Ambient;			// ÂŤF
	float4	g_Diffuse;			// gUF
	float4	g_Specular;			// žĘ˝ËF
	float4	g_Emissive;			// ­őF
};

Texture2D    g_texture		: register(t0);	// eNX`
Texture2D    g_texEmissive	: register(t1);	// ­őeNX`
SamplerState g_sampler		: register(s0);	// Tv

// p[^
struct VS_OUTPUT {
	float4	Pos			: SV_Position;
	float2	Tex			: TEXCOORD0;
	float3	Normal		: TEXCOORD1;
	float3	PosForPS	: TEXCOORD2;
	float4 lightpos :TEXCOORD3;
};

//
// sNZVF[_
//
float4 main(VS_OUTPUT input) : SV_Target0
{
	float3 Diff = g_Diffuse.rgb;
	float Alpha = g_Diffuse.a;
	if (g_Ambient.a != 0.0f) {								// eNX`Lł
		float4 TexDiff = g_texture.Sample(g_sampler, input.Tex);
		Diff *= TexDiff.rgb;
		Alpha *= TexDiff.a;
	}
	clip(Alpha - 0.0001f);
	
	if (g_lightDir.x != 0.0f || g_lightDir.y != 0.0f || g_lightDir.z != 0.0f) {
		float3 L = normalize(-g_lightDir.xyz);					// őšÖĚxNg
		float3 N = normalize(input.Normal);						// @üxNg
		float3 V = normalize(g_cameraPos.xyz - input.PosForPS);	// _ÖĚxNg
		float3 H = normalize(L + V);							// n[txNg
		Diff = g_lightAmbient.rgb * g_Ambient.rgb +
			g_lightDiffuse.rgb * Diff * saturate(dot(L, N));	// gUF + ÂŤF
			float aaa = max(g_Specular.a,0.0001f);
		float3 Spec = g_Specular.rgb * g_lightSpecular.rgb *
			pow(saturate(dot(N, H)), aaa);				// žĘ˝ËF
			float3 zero3 = float3(0,0,0);
		Diff += Spec;
	}

	float3 Emis = g_Emissive.rgb;								// ­őF
	if (g_Emissive.a != 0.0f) {
		float4 Emis4 = g_texEmissive.Sample(g_sampler, input.Tex);
		Emis *= (Emis4.rgb * Emis4.a);
	}
	//Diff += Emis;

	return float4(Diff, Alpha);
}
