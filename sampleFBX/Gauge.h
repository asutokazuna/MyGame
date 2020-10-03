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

	GameObject* m_bar;
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

	/**
	 * @brief �X�V����
	 * @return �Ȃ�
	 */
	void Update();

	void SetParam(float max, float min, Vector3 myColor, Vector3 enemyColor);
	void SetValue(int& value);
	void SetTransform(Transform* trans);
	void SetOffset(Vector3 value);
};

// EOF