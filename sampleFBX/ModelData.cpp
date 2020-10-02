/**
 * @file ModelData
 * @brief モデルデータクラス
 */
#include "ModelData.h"
#include "Graphics.h"
#include "Light.h"

#define PATH_MODELSKY		"data/model/sky.fbx"
#define PATH_MODELPLAYER	"data/model/cube.fbx"
#define PATH_MODELENEMY		"data/model/eagle.fbx"
#define PATH_MISSILE		"data/model/bullet.fbx"
#define PATH_TOWER			"data/model/tower.fbx"
#define PATH_CORE			"data/model/core.fbx"

struct MODEL_TABLE
{
	LPCSTR filename;
	ModelKind kind;
};

MODEL_TABLE m_table[MODEL_MAX] = {
	{PATH_MODELSKY, MODEL_SKY},
	{PATH_MODELPLAYER, MODEL_PLAYER},
	{PATH_MODELENEMY, MODEL_ENEMY},
	{PATH_MISSILE, MODEL_MISSILE},
	{PATH_TOWER, MODEL_TOWER},
	{PATH_CORE, MODEL_CORE},
};

/**
 * @brief 初期化
 * @return なし
 */
void ModelData::Initinstance()
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();

	m_light = *Light::Get();

	// FBXファイルの読み込み
	for (int i = 0; i < MODEL_MAX; i++)
	{
		CFbxModel* temp = new CFbxModel();
		hr = temp->Init(pDevice, pDeviceContext, m_table[i].filename);
		temp->SetLight(m_light);
		if (SUCCEEDED(hr)) {
			m_data.Set(m_table[i].kind, temp);
		}
	}
}

void ModelData::UninitInstance()
{
}

/**
 * @brief 初期化
 * @return なし
 */
void ModelData::Init()
{
	ModelData::GetInstance().Initinstance();
}

void ModelData::Uninit()
{
	ModelData::GetInstance().UninitInstance();
}

/**
 * @brief モデルデータの取得
 * @param[in] kind 取得したいテクスチャのID
 * @return 引数に合わせたモデルデータ
 */
CFbxModel * ModelData::GetData(ModelKind kind)
{
	return ModelData::GetInstance().m_data.Get(kind);
}

/**
 * @brief モデルの大きさの取得
 * @param[in] kind モデルの種類
 * @return モデルサイズ
 */
Vector3 ModelData::GetSize(int kind)
{
	Vector3 size;
	size.x = ModelData::GetInstance().m_data.Get(kind)->GetBBox().x * 100;
	size.y = ModelData::GetInstance().m_data.Get(kind)->GetBBox().y * 100;
	size.z = ModelData::GetInstance().m_data.Get(kind)->GetBBox().z * 100;

	return size;
}

// EOF