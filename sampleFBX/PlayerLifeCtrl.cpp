/**
 * @class PlayerLifeCtrl
 * @brief �v���C���[��HP�̊Ǘ�
 */
#include "PlayerLifeCtrl.h"
#include "collision.h"
#include "GameObject.h"
#include "MissileCtrl.h"
#include "NumberList.h"
#include "NumberListCtrl.h"
#include "LifeGaugeShaderInfo.h"

#define MAX_LIFE (10)

/**
 * @brief ����������
 * @return �Ȃ�
 */
void PlayerLifeCtrl::Awake()
{
	m_Life = MAX_LIFE;
}

/**
 * @brief ����������
 * @return �Ȃ�
 */
HRESULT PlayerLifeCtrl::Init()
{
	m_numberUI = m_Parent->GetChild<NumberList>("LifeUI");
	m_numberUI->GetComponent<NumberListCtrl>()->SetWidth(30);
	m_numberUI->GetComponent<NumberListCtrl>()->SetPos(Vector3(-SCREEN_CENTER_X + 120, -SCREEN_CENTER_Y + 50, 0));

	m_gauge = m_Parent->GetChild<GameObject>("LifeGauge");
	m_gauge->GetTransform().scale = Vector3(100, 40, 0);
	m_gauge->GetTransform().position = Vector3(-SCREEN_CENTER_X + 200, -SCREEN_CENTER_Y + 50, 0);

	return E_NOTIMPL;
}

/**
 * @brief �X�V����
 * @return �Ȃ�
 */
void PlayerLifeCtrl::Update()
{
	m_numberUI->GetComponent<NumberListCtrl>()->SetNumber(m_Life);
	m_gauge->GetComponent<LifeGaugeShaderInfo>()->SetFloat("Life", m_Life / (float)MAX_LIFE);
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
			m_Life -= power;
		}
		gameObj->SetActive(false);
	}
}

/**
 * @brief HP�̎擾
 * @return ����HP�̎擾
 */
unsigned int PlayerLifeCtrl::GetLife()
{
	return m_Life;
}

// EOF