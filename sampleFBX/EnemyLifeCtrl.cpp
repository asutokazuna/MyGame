/**
 * @class EnemyLifeCtrl
 * @brief 敵のHPの管理コンポーネント
 */
#include "EnemyLifeCtrl.h"
#include "GameObject.h"
#include "collision.h"
#include "MissileCtrl.h"
#include "ObjectManager.h"
#include "CharacterSpawnCtrl.h"

#define MAX_ENEMY_LIFE (10)

 /**
 * @brief 初期化処理
 * @return なし
 */
HRESULT EnemyLifeCtrl::Init()
{
	m_Life = MAX_ENEMY_LIFE;

	return E_NOTIMPL;
}

/**
 * @brief 当たった時の処理
 * @return なし
 */
void EnemyLifeCtrl::OnCollisionEnter(GameObject* gameObj)
{
	if (gameObj->CompareTag(OBJ_TAG_PLAYERMISSILE))
	{
		int power = gameObj->GetComponent<MissileCtrl>()->GetPower();

		m_Life -= power;

		gameObj->SetActive(false);

		// 倒されたとき
		if (m_Life <= 0)
		{
			ObjectManager::GetInstance().FindObject<GameObject>("CharacterSpawner")->GetComponent<CharacterSpawnCtrl>()->Set(m_Parent);
			m_Parent->SetActive(false);
		}

	}
}

/**
 * @brief HPの取得
 * @return 現在HPの取得
 */
int EnemyLifeCtrl::GetLife()
{
	return m_Life;
}

/**
 * @brief HPの取得
 * @return 現在HPの取得
 */
float EnemyLifeCtrl::GetLifePercent()
{
	return m_Life / (float)MAX_ENEMY_LIFE;
}

// EOF