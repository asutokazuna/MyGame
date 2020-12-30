/**
 * @file CoreEnemyGauge
 * @brief �G�R�A�̎c��HP�\���R���|�[�l���g
 */
#include "CoreEnemyGauge.h"
#include "ObjectManager.h"
#include "UIMesh.h"
#include "ShaderInfo.h"
#include "GameObject.h"
#include "CoreState.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void CoreEnemyGauge::Awake()
{
	CoreGauge::Awake();
	m_mesh->ChangeSize(400, 50, 0)->ChangePos(0, SCREEN_CENTER_Y - 102, 0);
	m_shader->ChangeColor(1, 0, 0);
	m_state = ObjectManager::GetInstance().FindObject<GameObject>("CoreEnemy")->GetComponent<CoreState>();
}

// EOF