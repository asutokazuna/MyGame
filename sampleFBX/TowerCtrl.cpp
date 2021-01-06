/**
 * @file TowerCtrl
 * @brief TowerCtrlクラス
 */
#include "TowerCtrl.h"
#include "FbxModel.h"
#include "TowerEnergy.h"
#include "GameObject.h"
#include "Object3D.h"
#include "Gauge.h"
#include "LifeGaugeShaderInfo.h"
#include "LifeGauge.h"
#include "TowerEnergy.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void TowerCtrl::Awake()
{
	material = new TFbxMaterial();
	m_state = TOWERSTATE::NONE;
}
/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT TowerCtrl::Init()
{
	m_percent = 0;
	m_gauge = m_Parent->GetChild<Gauge>()->GetChild<LifeGauge>();
	m_shader = m_gauge->GetComponent<LifeGaugeShaderInfo>();
	m_energy = m_Parent->GetComponent<TowerEnergy>();

	return E_NOTIMPL;
}

/**
 * @brief 終了処理
 * @return なし
 */
void TowerCtrl::Uninit()
{
	delete material;
}

/** 
 * @brief 更新処理
 * @return なし
 */
void TowerCtrl::Update()
{
	float per = m_energy->GetEnergyPercent();
	Vector3 color = Vector3(0, 0, 1);
	if (per < 0) {
		color = Vector3(1, 0, 0);
	}
	// ゲージ用
	m_shader->SetFloat("Life", fabsf(per));
	m_shader->ChangeColor(color);


	if (per >= 1) {
		m_state = TOWERSTATE::PLAYER;
	}
	else if (per <= -1) {
		m_state = TOWERSTATE::ENEMY;
	}
	else{
		m_state = TOWERSTATE::NONE;
	}
}

void TowerCtrl::Draw()
{
#ifdef _DEBUG
	//ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Once);
	//if (ImGui::TreeNode("tree1")) {
	//	ImGui::SliderFloat("material x", &material->Kd.x, -1, 1);
	//	ImGui::SliderFloat("material y", &material->Kd.y, -1, 1);
	//	ImGui::SliderFloat("material z", &material->Kd.z, -1, 1);
	//	ImGui::SliderFloat("material w", &material->Kd.w, -1, 1);
	//	ImGui::SliderFloat("material x", &material->Ks.x, -1, 1);

	//	float per = m_energy->GetEnergyPercent();
	//	ImGui::SliderFloat("per y", &per, -1, 1);
	//	ImGui::TreePop();
	//}
#endif
}

/** 
 * @brief 占拠状態の取得
 * @return 1の時プレイヤー、-1で敵、それ以外で未占拠
 */
int TowerCtrl::GetState()
{
	return m_state;
}


void TowerCtrl::ChangeColor()
{
	XMFLOAT3 color;
	float per = m_energy->GetEnergyPercent();
	if (per >= 0.5) {
		 color = XMFLOAT3(0, 0, 1);
	}
	else if (per <= -0.5) {
		color = XMFLOAT3(1, 0, 0);
	}
	else {
		color = XMFLOAT3(0, 1, 0);
	}
	material->Kd.x = color.x;
	material->Kd.y = color.y;
	material->Kd.z = color.z;
	material->Kd.w = 1;
	//material->Ke.x = 0.f;
	//material->Ke.y = 0.f;
	//material->Ke.z = 0.f;
	//material->Ka.w = 1.0f;
	//material->Ka.x = 1.0f;
	//material->Ka.y = 1.0f;
	//material->Ka.z = 1.0f;
	//material->Ks.w = 1.0f;
	//material->Ks.x = 0.0f;
	//material->Ks.y = 0.0f;
	//material->Ks.z = 0.0f;
	m_Parent->GetComponent<Object3D>()->SetMaterial(*material);
}

// EOF