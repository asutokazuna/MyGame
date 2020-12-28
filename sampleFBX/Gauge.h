/**
 * @file Gauge
 * @brief �Q�[�W�\���N���X
 */
#pragma once
#include "GameObject.h"
#include "MyMath.h"

// �O���錾
class Mesh;

/**
 * @class Gauge
 * @brief �Q�[�W
 */
class Gauge :public GameObject
{
private:
	float m_Min;
	float m_Max;
	int* m_Value;

	GameObject* m_LifeGauge;
	GameObject* m_frame;
	Transform* m_transform;

	Mesh* barmesh;
	Vector3 m_myColor;
	Vector3 m_EnemyColor;
	Vector3 m_offset;
public:

	/**
	 * @brief �R���X�g���N�^
	 */
	Gauge();

	/**
	 * @brief ����������
	 * @return �Ȃ�
	 */
	void Awake();
};

// EOF