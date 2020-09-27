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

void ModelData::Init()
{
	ModelData::GetInstance().Initinstance();
}

void ModelData::Uninit()
{
	ModelData::GetInstance().UninitInstance();
}

CFbxModel * ModelData::GetData(ModelKind kind)
{
	return ModelData::GetInstance().m_data.Get(kind);
}

// EOF