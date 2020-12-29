/**
 * @file�@WeaponBulletCount
 * @brief ����̎c��c�e���̕\���R���|�[�l���g
 */
#pragma once
#include "Component.h"

class NumberList;
class Missile;

class WeaponBulletCount: public Component
{
private:
	NumberList* m_BulletNum;
public:
	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	HRESULT Init();

	/**
	 * @brief �X�V����
	 * @return �Ȃ�
	 */
	void Update();
};

// EOF