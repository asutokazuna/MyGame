/**
 * @file Missile
 * @brief �~�T�C���N���X
 * @date 2020/06/19
 */
#include "Missile.h"
#include "ModelData.h"
#include "Object3D.h"
#include "collision.h"
#include "MissileMove.h"

Missile::Missile() 
{
	m_col = nullptr;
}

HRESULT Missile::Init()
{
	HRESULT hr = S_OK;	
	AddComponent<Object3D>()->SetModel(MODEL_MISSILE);
	m_Move = AddComponent<MissileMove>();

	m_col->SetActive(false);

	return hr;
}

void Missile::Uninit()
{
	GameObject::Uninit();
}

void Missile::Update()
{
	if (m_Move->m_nLife <= 0) {

		m_col->SetActive(false);
		//return;
	}
	GameObject::Update();
}

void Missile::Draw()
{
	if (m_Move->m_nStat == 0) {
		return;
	}
	GameObject::Draw();
}

void Missile::DrawAlpha()
{
	if (m_Move->m_nStat == 0) {
		return;
	}
	GameObject::Draw();
}

// Offset�����f�����W�ł̃~�T�C���̈ʒu�炵����
bool Missile::Fire(Vector3* pos)
{
	if (m_Move->m_nStat != 0) {
		return false;
	}

	m_col->SetActive(true);
	transform->position = *pos;
	m_Move->m_nLife = 3 * 60;		// 5�b
	m_Move->m_nStat = 1;			// �ǔ���
	return true;
}

bool Missile::Fire(Vector3 * pos, Quaternion quat)
{
	if (m_Move->m_nStat != 0) {
		return false;
	}

	m_col->SetActive(true);
	transform->position = *pos;
	transform->quaternion = quat;
	m_col->SetPos(*pos);
	m_Move->m_nLife = 3 * 60;		// 5�b
	m_Move->m_nStat = 1;			// �ǔ���
	return true;
}

// EOF