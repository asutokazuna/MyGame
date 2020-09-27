/**
 * @file Tower
 * @brief TowerƒNƒ‰ƒX
 */
#include "Tower.h"
#include "Object3D.h"
#include "ModelData.h"
#include "TowerCollision.h"
#include "TowerEnergy.h"
#include "FbxModel.h"
#include "Gauge.h"

HRESULT Tower::Init()
{
	m_Object3D = &AddComponent<Object3D>()->SetModel(MODEL_TOWER);
	transform->scale = 0.5f;
	m_collision = AddComponent<TowerCollision>();
	m_Energy = AddComponent<TowerEnergy>();
	m_LifeGauge = new Gauge();
	m_LifeGauge->Init();
	m_LifeGauge->SetOffset({0, 150, 0});
	material = new TFbxMaterial();
	return S_OK;
}

void Tower::Uninit()
{
	m_LifeGauge->Uninit();
	delete m_LifeGauge;
	GameObject::Uninit();
	delete material;
}

void Tower::Update()
{
	m_LifeGauge->SetTransform(*transform);
	m_LifeGauge->Update();
	float value = m_Energy->GetEnergy();
	m_LifeGauge->SetValue(value);
	GameObject::Update();
}

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
	m_collision->UpdatePos();

	return this;
}

// EOF