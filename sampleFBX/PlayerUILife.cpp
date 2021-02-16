/**
 * @class PlayerUILife
 * @breif プレイヤーのステータスをUIに表示するコンポーネント
 * @author Ariga
 */
#include "PlayerUILife.h"
#include "ObjectManager.h"
#include "PlayerLifeCtrl.h"
#include "NumberList.h"
#include "NumberListCtrl.h"
#include "LifeGaugeShaderInfo.h"

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerUILife::Init()
{
	m_playerObj = ObjectManager::GetInstance().FindObject<GameObject>("Player");
	m_playerLife = m_playerObj->GetComponent<PlayerLifeCtrl>();

	m_numberUI = m_Parent->GetChildTest("PlayerLifeUI");
	m_LifeNum = m_numberUI->GetComponent<NumberListCtrl>();
	m_LifeNum->SetNumber(m_playerLife->GetLife());
	m_LifeNum->SetWidth(30);
	m_LifeNum->SetPos(Vector3(-SCREEN_CENTER_X + 120, -SCREEN_CENTER_Y + 50, 0));

	m_gauge = m_Parent->GetChildTest("LifeGauge");
	m_gauge->GetTransform().scale = Vector3(100, 40, 0);
	m_gauge->GetTransform().position = Vector3(-SCREEN_CENTER_X + 200, -SCREEN_CENTER_Y + 50, 0);

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void PlayerUILife::Update()
{
	int life = m_playerLife->GetLife();
	m_LifeNum->SetNumber(life);
	m_gauge->GetComponent<LifeGaugeShaderInfo>()->SetFloat("Life", life / (float)MAX_LIFE);
}

// EOF