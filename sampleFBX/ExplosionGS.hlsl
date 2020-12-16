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

/**
 * @brief 乱数生成関数
 * @param[in] co シード値
 * @return 生成した乱数
 */
float rand(float2 co){
    return frac(sin(dot(co.xy ,float2(12.9898,78.233))) * 43758.5453);
}

/**
 * @brief 2次ベジェ曲線
 * @param[in] start	初期座標
 * @param[in] ctrl	制御点
 * @param[in] end	終了座標
 * @param[in] t		変化量
 * @return 移動後座標
 */
float calcBezier(float start, float ctrl, float end, float t)
{
	return (1 - t) * (1 - t) * start + 2 * (1 - t) * t * ctrl + t *t * end;
}

/**
 * @brief 3次ベジェ曲線
 * @param[in] start	初期座標
 * @param[in] ctrl	制御点1
 * @param[in] ctrl2	制御点2
 * @param[in] end	終了座標
 * @param[in] t		変化量
 * @return 移動後座標
 */
float calcBezier3(float start, float ctrl, float ctrl2, float end, float t)
{
	return (1 - t) * (1 - t) * (1 - t) * start + 3 * (1 - t) * (1 - t) * t * ctrl + 3 * (1 - t) * t * t * ctrl2 + t*  t *t * end;
}

/**
 * @brief ハルシェーダで分割したものをポリゴン単位で分け、移動させる
 */
[maxvertexcount(3)]
void main(
	triangle GS_IN input[3], 
	inout TriangleStream< GS_OUT > TriStream
)
{
	GS_OUT output;		//!< 出力情報
	float2 pos;			//!< 表示座標
	float2 start;		//!< ベジェ曲線の開始点
	float2 ctrl;		//!< ベジェ曲線の制御点1
	float2 ctrl2;		//!< ベジェ曲線の制御点2
	float2 dist = 0;	//!< uvの中心からの合計距離
	float2 d;			//!< 乱数値
	float scalar;		//!< uv値の内積

	// uvの中心からの距離の合計を求める
	for (uint i = 0; i < 3; i++)
	{
		dist += input[i].TexCoord * 2 - 1;	
	}

	float2 dotuv = dot(dist.x / 3,dist.y / 3);
	
	// 求めた距離をシードとし乱数を出す
	d.x = rand(float2(dotuv.x,dotuv.y)) * 2 - 1;
	d.y = rand(float2(dotuv.y * 2,dotuv.x)) * 2 - 1;

	for (uint i = 0; i < 3; i++)
	{
		pos = input[i].Position;
		start = float2(input[i].Position.x - d.x, input[i].Position.y-d.y)/10;
		ctrl.x =(d.x + d.y) * 2;
		ctrl.y = (d.x * d.y * input[i].Position.y +start)*2;
		ctrl2.x = d.x * 2;
		ctrl2.y = d.y * 5;
		scalar = abs(dot(input[i].TexCoord.x,input[i].TexCoord.y)) ;

		pos.x = calcBezier3(start.x,ctrl.x,ctrl2.x, input[i].Position.x,clamp(value.y+(1 - scalar) * clamp(value.y ,0,1),0,1));
		pos.y = calcBezier3(start.y,ctrl.y,ctrl2.y, input[i].Position.y,clamp(value.y+(1 - scalar) * clamp(value.y,0,1),0,1));

		// ワールド変換など
		output.Position = mul( float4(pos,input[i].Position.z, 1.0f ), g_mWVP );
		output.Pos4PS = mul(input[i].Position, g_mWorld).xyz;
		output.Normal = mul(input[i].Normal, g_mWorld);
		output.TexCoord =mul(float4(input[i].TexCoord, 0.0f, 1.0f), g_mTexture).xy;
		output.Color = input[i].Color;
		TriStream.Append(output);
	}
}

// EOF