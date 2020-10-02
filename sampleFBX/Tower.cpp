/**
 * @file Tower
 * @brief Towerクラス
 */
#include "Tower.h"
#include "Object3D.h"
#include "ModelData.h"
#include "TowerCollision.h"
#include "TowerEnergy.h"
#include "FbxModel.h"
#include "Gauge.h"

 /**
  * @brief 初期化処理
  * @return なし
  */
void Tower::Awake()
{
	tag = OBJ_TAG_TOWER;

	m_Object3D = &AddComponent<Object3D>()->SetModel(MODEL_TOWER);
	transform->scale = 0.5f;
	m_collision = AddComponent<Collision>();
	m_Energy = AddComponent<TowerEnergy>();
	m_LifeGauge = new Gauge();
	m_LifeGauge->Init();
	m_LifeGauge->SetOffset({ 0, 150, 0 });
	material = new TFbxMaterial();

	m_collision->SetModelKind(MODEL_TOWER);
}

/**
 * @brief 終了処理
 * @return なし
 */
void Tower::Uninit()
{
	m_LifeGauge->Uninit();
	delete m_LifeGauge;
	GameObject::Uninit();
	delete material;
}

/**
 * @brief 更新処理
 * @return なし
 */
void Tower::Update()
{
	m_LifeGauge->SetTransform(*transform);
	m_LifeGauge->Update();
	float value = (float)m_Energy->GetEnergy();
	m_LifeGauge->SetValue(value);
	GameObject::Update();
}

/**
 * @brief 描画処理
 * @return なし
 */
void Tower::Draw()
{
	m_LifeGauge->Draw();
	ChangeColor();
	GameObject::Draw();
}

void Tower::ChangeColor()
{
	if (m_Energy->GetEnergy() >= ENERGY_MAX) {
		color = XMFLOAT3(0, 1, 0);
	}
	else if (m_Energy->GetEnergy() <= 0) {
		color = XMFLOAT3(1, 0, 0);
	}
	else{
		color = XMFLOAT3(1, 1, 1);
	}
	material->Kd.x = color.x;
	material->Kd.y = color.y;
	material->Kd.z = color.z;
	material->Ke.x = 0.1f;
	material->Ke.y = 0.1f;
	material->Ke.z = 0.1f;
	material->Ka.w = 1.0f;
	material->Ks.w = 1.0f;
	m_Object3D->SetMaterial(*material);
}

Tower* Tower::SetPos(Vector3 pos)
{
	transform->position = pos;

	return this;
}

// EOF