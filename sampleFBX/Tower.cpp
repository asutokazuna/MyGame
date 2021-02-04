/**
 * @file Tower
 * @brief Towerクラス
 */
#include "Tower.h"
#include "Object3D.h"
#include "ModelData.h"
#include "TowerEnergy.h"
#include "FbxModel.h"
#include "Gauge.h"
#include "TowerCtrl.h"
#include "collision.h"
#include "GaugeCtrl.h"
#include "ObjectManager.h"

 /**
  * @brief 初期化処理
  * @return なし
  */
void Tower::Awake()
{
	tag = OBJ_TAG_TOWER;
	transform->scale = Vector3(0.3f, 0.3f, 0.3f);
	m_LifeGauge = //new Gauge();
	ObjectManager::Create<Gauge>("TowerGauge");
	m_LifeGauge->SetParent(this);

	m_Object3D = &AddComponent<Object3D>()->SetModel(MODEL_TOWER);
	m_collision = AddComponent<Collision>()->SetModelKind(MODEL_TOWER);
	m_Energy = AddComponent<TowerEnergy>();
	m_ctrl = AddComponent<TowerCtrl>();
	m_LifeGauge->GetComponent<GaugeCtrl>()->SetOffset({ 0, 150, 0 });
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT Tower::Init()
{
	m_LifeGauge->GetComponent<GaugeCtrl>()->SetTarget(transform);
	GameObject::Init();

	return E_NOTIMPL;
}

// EOF