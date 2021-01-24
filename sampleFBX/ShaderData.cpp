/**
 * @file ShaderData
 * @brief シェーダーデータクラス
 */
#include "ShaderData.h"
#include "Shader.h"

enum LAYOUT_KIND
{
	IL_2D,
	IL_3D,
	IL_MAX,
};

/**
 * @struct シェーダーデータのテーブル
 */
struct SHADER_TABLE {
	int type;
	const char* filename;
};

struct VERTEX_TABLE
{
	SHADER_TABLE table;
	LAYOUT_KIND layoutKind;

};

/**
 * @biref バーテックスシェーダー
 */
VERTEX_TABLE VS_Table[] = 
{
	{ShaderData::VS_VERTEX, "Vertex",IL_2D },
	{ShaderData::VS_VERTEX3D, "FbxModelVertex",IL_3D },
	{ShaderData::VS_CLOTH, "ClothVertex",IL_2D },
	{ShaderData::VS_DEFAULT, "DefaultVS",IL_2D },
};

/**
 * @biref ピクセルシェーダ
 */
SHADER_TABLE PS_Table[] = 
{
	{ShaderData::PS_PIXEL, "Pixel"},
	{ShaderData::PS_PIXEL3D, "FbxModelPixel"},
	{ShaderData::PS_CLOTH, "ClothPixel"},
	{ShaderData::PS_EXPLOSION, "ExplosionPS"},
	{ShaderData::PS_LIFEGAUGE, "LifeGaugePS"},
};
/**
 * @biref ハルシェーダ
 */
SHADER_TABLE HS_Table[] = 
{
	{ShaderData::HS_CLOTH, "ClothHull"},
	{ShaderData::HS_DEFAULT, "DefaultHS"},
};

/**
 * @biref ドメインシェーダ
 */
SHADER_TABLE DS_Table[] = 
{
	{ShaderData::DS_CLOTH, "ClothDomain"},
	{ShaderData::DS_DEFAULT, "DefaultDS"},
};

/**
 * @biref ジオメトリシェーダ
 */
SHADER_TABLE GS_Table[] = 
{
	{ShaderData::GS_EXPLOSION, "ExplosionGS"},
};


/**
 * @brief　データの初期化
 * @return なし
 */
void ShaderData::InitInstance()
{
	// シェーダ初期化
	static const D3D11_INPUT_ELEMENT_DESC layout2D[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	// 頂点フォーマットの定義、生成
	static const D3D11_INPUT_ELEMENT_DESC layout3D[] = {
		{ "POSITION",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",      0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BONE_INDEX",  0, DXGI_FORMAT_R32G32B32A32_UINT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "BONE_WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	static const D3D11_INPUT_ELEMENT_DESC* pLayout[] = {
		layout2D,layout3D
	};

	static const int layoutCnt[] = {
		_countof(layout2D), _countof(layout3D)
	};

	ID3D11VertexShader* workVs;
	ID3D11InputLayout* workIl;
	ID3D11PixelShader* workPs;
	ID3D11HullShader* workHs;
	ID3D11DomainShader* workDs;
	ID3D11GeometryShader* workGs;

	for (int i = 0; i < VS_MAX; i++)
	{
		LoadVertexShader(VS_Table[i].table.filename, &workVs, &workIl, pLayout[VS_Table[i].layoutKind], layoutCnt[VS_Table[i].layoutKind]);
		m_VS.Set(VS_Table[i].table.type,workVs);
		m_IL.Set(VS_Table[i].table.type,workIl);
	}
	for (int i = 0; i < PS_MAX; i++)
	{
		LoadPixelShader(PS_Table[i].filename, &workPs);
		m_PS.Set(PS_Table[i].type,workPs);
	}
	for (int i = 0; i < HS_MAX; i++)
	{
		LoadHullShader(HS_Table[i].filename, &workHs);
		m_HS.Set(HS_Table[i].type, workHs);
	}
	for (int i = 0; i < DS_MAX; i++)
	{
		LoadDomainShader(DS_Table[i].filename, &workDs);
		m_DS.Set(DS_Table[i].type, workDs);
	}
	for (int i = 0; i < GS_MAX; i++)
	{
		LoadGeometryShader(GS_Table[i].filename, &workGs);
		m_GS.Set(GS_Table[i].type, workGs);
	}
}

/**
 * @biref 初期化処理
 * @return なし
 */
void ShaderData::Init()
{
	ShaderData::GetInstance().InitInstance();
}

/**
 * @brief 終了処理
 * @return なし
 */
void ShaderData::Uninit()
{
	// 処理なし
}

/**
 * @brief バーテックスシェーダーの取得
 * @param[in] 取得したい種類のenum
 * @return 引数に対応したシェーダーデータ
 */
ID3D11VertexShader* ShaderData::GetVertexShader(int kind)
{
	if (VS_KIND::VS_MAX <= kind ||
		kind < 0) {
		return nullptr;
	}
	return ShaderData::GetInstance().m_VS.Get(kind);
}

/**
 * @brief ピクセルシェーダーの取得
 * @param[in] 取得したい種類のenum
 * @return 引数に対応したシェーダーデータ
 */
ID3D11PixelShader* ShaderData::GetPixelShader(int kind)
{
	if (PS_KIND::PS_MAX <= kind ||
		kind < 0) {
		return nullptr;
	}
	return ShaderData::GetInstance().m_PS.Get(kind);
}

ID3D11HullShader * ShaderData::GetHullShader(int kind)
{
	if (HS_KIND::HS_MAX <= kind ||
		kind < 0) {
		return nullptr;
	}
	return ShaderData::GetInstance().m_HS.Get(kind);
}

ID3D11DomainShader * ShaderData::GetDomainShader(int kind)
{
	if (DS_KIND::DS_MAX <= kind ||
		kind < 0) {
		return nullptr;
	}
	return ShaderData::GetInstance().m_DS.Get(kind);
}

ID3D11GeometryShader* ShaderData::GetGeometryShader(int kind)
{
	if (GS_KIND::GS_MAX <= kind ||
		kind < 0) {
		return nullptr;
	}
	return ShaderData::GetInstance().m_GS.Get(kind);
}

/**
 * @brief インプットレイアウトの取得
 * @param[in] 取得したい種類のenum
 * @return 引数に対応したインプットレイアウト
 */
ID3D11InputLayout* ShaderData::GetInputLayout(int kind)
{
	if (VS_KIND::VS_MAX <= kind ||
		kind < 0) {
		return nullptr;
	}
	return ShaderData::GetInstance().m_IL.Get(kind);
}

// EOF