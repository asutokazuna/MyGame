/**
 * @file MissileCtrl
 * @brief �e�̐���R���|�[�l���g
 */
#include "MissileCtrl.h"
#include "GameObject.h"

/**
 * @brief ����������
 * @return �Ȃ�
 */
void MissileCtrl::Awake()
{
	m_power = 1;		// �e�̍U����
	m_nLife = 0;
}

HRESULT MissileCtrl::Init()
{
	m_nLife = 0;
	m_parentTrans = &m_Parent->GetTransform();
	m_target = nullptr;

	return E_NOTIMPL;
}

void MissileCtrl::Update()
{
	--m_nLife;

	// �ǔ�
	if (m_target != nullptr) {
		Vector3 dir = m_target->GetTransform().position - m_parentTrans->position;
		m_parentTrans->quaternion = MyMath::LookRotation(m_parentTrans->GetForward(), dir, 1 / 30.0f);
	}

	if (m_nLife <= 0) {
		m_Parent->SetActive(false);
	}
}

// Offset�����f�����W�ł̃~�T�C���̈ʒu�炵����
bool MissileCtrl::Fire(Vector3* pos)
{
	m_Parent->SetActive(true);
	m_parentTrans->position = *pos;
	m_nLife =  2.5f * 60;		// 2.5�b
	return true;
}

bool MissileCtrl::Fire(Vector3* pos, Quaternion quat)
{
	Fire(pos);
	m_parentTrans->quaternion = quat;
	return true;
}

bool MissileCtrl::Fire(Vector3* pos, Quaternion quat, GameObject* target)
{
	Fire(pos, quat);
	m_target = target;
	return true;
}

/**
 * �e�̈З͂̎擾
 * @return �e�̈З�
 */
int MissileCtrl::GetPower()
{
	return m_power;
}

// EOF