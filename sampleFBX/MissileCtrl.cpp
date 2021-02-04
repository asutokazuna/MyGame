/**
 * @file MissileCtrl
 * @brief 弾の制御コンポーネント
 */
#include "MissileCtrl.h"
#include "GameObject.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void MissileCtrl::Awake()
{
	m_power = 1;		// 弾の攻撃力
	m_nLife = 0;
}

HRESULT MissileCtrl::Init()
{
	m_nLife = 0;
	//m_ParentTransform = &m_Parent->GetTransform();
	m_target = nullptr;

	return E_NOTIMPL;
}

void MissileCtrl::Update()
{
	--m_nLife;

	// 追尾
	if (m_target != nullptr) {
		Vector3 dir = m_target->GetTransform().position - m_ParentTransform->position;
		m_ParentTransform->quaternion = MyMath::LookRotation(m_ParentTransform->GetForward(), dir, 1 / 30.0f);
	}

	if (m_nLife <= 0) {
		m_Parent->SetActive(false);
	}
}

// Offsetがモデル座標でのミサイルの位置らしいよ
bool MissileCtrl::Fire(Vector3* pos)
{
	m_Parent->SetActive(true);
	m_ParentTransform->position = *pos;
	m_nLife =  2.5f * 60;		// 2.5秒
	return true;
}

bool MissileCtrl::Fire(Vector3* pos, Quaternion quat)
{
	Fire(pos);
	m_ParentTransform->quaternion = quat;
	return true;
}

bool MissileCtrl::Fire(Vector3* pos, Quaternion quat, GameObject* target)
{
	Fire(pos, quat);
	m_target = target;
	return true;
}

/**
 * 弾の威力の取得
 * @return 弾の威力
 */
int MissileCtrl::GetPower()
{
	return m_power;
}

// EOF