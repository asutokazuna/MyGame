/**
 * @file MissileCtrl
 * @brief 弾の制御コンポーネント
 * @author Ariga
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

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT MissileCtrl::Init()
{
	m_nLife = 0;
	m_target = nullptr;

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void MissileCtrl::Update()
{
	--m_nLife;

	// 追尾
	if (m_target != nullptr) {
		Vector3 dir = m_target->GetTransform().position - m_ParentTransform->position;
		m_ParentTransform->quaternion = MyMath::LookRotation(m_ParentTransform->GetForward(), dir, 1 / 30.0f);
		if (m_target->GetActive() == false) {
			m_target = nullptr;
		}
	}

	if (m_nLife <= 0) {
		m_Parent->SetActive(false);
	}
}

/**
 * @brief 弾の発射処理
 * @param[in] pos 発射座標
 * @return なし
 */
void MissileCtrl::Fire(Vector3* pos)
{
	m_Parent->SetActive(true);
	m_ParentTransform->position = *pos;
	m_nLife =  2.5f * 60;		// 2.5秒
}

/**
 * @brief 弾の発射処理
 * @param[in] pos 発射座標
 * @param[in] quat 発射方向
 * @return なし
 */
void MissileCtrl::Fire(Vector3* pos, Quaternion quat)
{
	Fire(pos);
	m_ParentTransform->quaternion = quat;
}

/**
 * @brief 弾の発射処理
 * @param[in] pos 発射座標
 * @param[in] quat 発射方向
 * @param[in] target 追従オブジェクト
 * @return なし
 */
void MissileCtrl::Fire(Vector3* pos, Quaternion quat, GameObject* target)
{
	Fire(pos, quat);
	m_target = target;
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