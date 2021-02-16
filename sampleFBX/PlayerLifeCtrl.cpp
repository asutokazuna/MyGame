/**
 * @class PlayerLifeCtrl
 * @brief プレイヤーのHPの管理
 * @author Ariga
 */
#include "PlayerLifeCtrl.h"
#include "collision.h"
#include "GameObject.h"
#include "MissileCtrl.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void PlayerLifeCtrl::Awake()
{
	m_Life = MAX_LIFE;
}

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerLifeCtrl::Init()
{
	m_Life = MAX_LIFE;

	return E_NOTIMPL;
}

/**
 * @brief 当たった時の処理
 * @return なし
 */
void PlayerLifeCtrl::OnCollisionEnter(GameObject* gameObj)
{
	// 弾と当たった時
	if (gameObj->CompareTag(OBJ_TAG_ENEMYMISSILE)) 
	{
		int power = gameObj->GetComponent<MissileCtrl>()->GetPower();

		if (m_Life < power) {
			m_Life = 0;
		}
		else {
			m_Life -= power;
		}
		gameObj->SetActive(false);
	}
}

/**
 * @brief HPの取得
 * @return 現在HPの取得
 */
int PlayerLifeCtrl::GetLife()
{
	return m_Life;
}

// EOF