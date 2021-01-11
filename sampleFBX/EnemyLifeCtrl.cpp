/**
 * @class EnemyLifeCtrl
 * @brief �G��HP�̊Ǘ��R���|�[�l���g
 */
#include "EnemyLifeCtrl.h"
#include "GameObject.h"
#include "collision.h"
#include "MissileCtrl.h"
#include "ObjectManager.h"
#include "CharacterSpawnCtrl.h"

#define MAX_ENEMY_LIFE (10)

 /**
 * @brief ����������
 * @return �Ȃ�
 */
HRESULT EnemyLifeCtrl::Init()
{
	m_Life = MAX_ENEMY_LIFE;

	return E_NOTIMPL;
}

/**
 * @brief �����������̏���
 * @return �Ȃ�
 */
void EnemyLifeCtrl::OnCollisionEnter(GameObject* gameObj)
{
	if (gameObj->CompareTag(OBJ_TAG_PLAYERMISSILE))
	{
		int power = gameObj->GetComponent<MissileCtrl>()->GetPower();

		m_Life -= power;

		gameObj->SetActive(false);

		// �|���ꂽ�Ƃ�
		if (m_Life <= 0)
		{
			ObjectManager::GetInstance().FindObject<GameObject>("CharacterSpawner")->GetComponent<CharacterSpawnCtrl>()->Set(m_Parent);
			m_Parent->SetActive(false);
		}

	}
}

/**
 * @brief HP�̎擾
 * @return ����HP�̎擾
 */
int EnemyLifeCtrl::GetLife()
{
	return m_Life;
}

/**
 * @brief HP�̎擾
 * @return ����HP�̎擾
 */
float EnemyLifeCtrl::GetLifePercent()
{
	return m_Life / (float)MAX_ENEMY_LIFE;
}

// EOF