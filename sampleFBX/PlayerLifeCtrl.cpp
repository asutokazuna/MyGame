/**
 * @class PlayerLifeCtrl
 * @brief プレイヤーのHPの管理
 */
#include "PlayerLifeCtrl.h"
#include "collision.h"
#include "GameObject.h"
#include "MissileCtrl.h"
#include "NumberList.h"
#include "NumberListCtrl.h"

#define MAX_LIFE (256)

/**
 * @brief 初期化処理
 * @return なし
 */
void PlayerLifeCtrl::Awake()
{
	m_Life = MAX_LIFE;
}

HRESULT PlayerLifeCtrl::Init()
{
	m_numberUI = m_Parent->GetChild<NumberList>("LifeUI");
	m_numberUI->GetComponent<NumberListCtrl>()->SetWidth(30);

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void PlayerLifeCtrl::Update()
{
	m_numberUI->GetComponent<NumberListCtrl>()->SetNumber(m_Life);
	m_numberUI->GetComponent<NumberListCtrl>()->SetPos(Vector3(-SCREEN_CENTER_X + 100, -SCREEN_CENTER_Y + 50, 0));
}

void PlayerLifeCtrl::OnCollisionEnter(GameObject* gameObj)
{
	if (gameObj->CompareTag(OBJ_TAG_ENEMYMISSILE)) 
	{
		int power = gameObj->GetComponent<MissileCtrl>()->GetPower();

		if (m_Life < power) {
			m_Life = 0;
		}
		else {
			m_Life = power;
		}
	}
}

/**
 * @brief HPの取得
 * @return 現在HPの取得
 */
unsigned int PlayerLifeCtrl::GetLife()
{
	return m_Life;
}

// EOF