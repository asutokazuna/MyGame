/**
 * @file PlayerCtrl
 * @brief プレイヤーの制御クラス
 */
#include "PlayerCtrl.h"
#include "input.h"
#include "Transform.h"
#include "GameObject.h"
#include "PlayerMissile.h"

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT PlayerCtrl::InitParam(std::list<PlayerMissile*>& missile)
{
	m_Missile = missile;
	m_ParentTrans = &m_Parent->GetTransform();

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void PlayerCtrl::Update()
{	 
	//ミサイル発射
	if (CInput::GetKeyTrigger(VK_L)) {
		for (auto m : m_Missile) {
			bool flg = false;
			flg = m->Fire(&m_ParentTrans->position, m_ParentTrans->quaternion);
			if (flg == true) {
				break;
			}
		}
	}
}

// EOF