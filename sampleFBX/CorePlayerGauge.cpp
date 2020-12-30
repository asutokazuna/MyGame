/**
 * @file CorePlayerGauge
 * @brief �����R�A�̎c��HP�\���R���|�[�l���g
 */
#include "CorePlayerGauge.h"
#include "ObjectManager.h"
#include "UIMesh.h"
#include "ShaderInfo.h"
#include "GameObject.h"
#include "CoreState.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void CorePlayerGauge::Awake()
{
	CoreGauge::Awake();
	m_mesh->ChangeSize(400, 50, 0)->ChangePos(0, SCREEN_CENTER_Y - 50, 0);
	m_shader->ChangeColor(0, 0, 1);
	m_state = ObjectManager::GetInstance().FindObject<GameObject>("CorePlayer")->GetComponent<CoreState>();
}

// EOF