/**
 * @file CorePlayerGauge
 * @brief 味方コアの残りHP表示コンポーネント
 */
#include "CorePlayerGauge.h"
#include "ObjectManager.h"
#include "UIMesh.h"
#include "ShaderInfo.h"
#include "GameObject.h"
#include "CoreState.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void CorePlayerGauge::Awake()
{
	CoreGauge::Awake();
	//m_mesh->ChangeSize(400, 50, 0)->ChangePos(0, SCREEN_CENTER_Y - 50, 0);
	//m_shader->ChangeColor(0, 0, 1);
	//m_state = ObjectManager::GetInstance().FindObject<GameObject>("CorePlayer")->GetComponent<CoreState>();
}

HRESULT CorePlayerGauge::Init()
{
	m_mesh->ChangeSize(400, 50, 0)->ChangePos(0, SCREEN_CENTER_Y - 50, 0);
	m_shader->ChangeColor(0, 0, 1);
	m_state = ObjectManager::GetInstance().FindObject<GameObject>("CorePlayer")->GetComponent<CoreState>();
	return S_OK;
}

// EOF