/**
 * @file Gauge
 * @brief ゲージ表示クラス
 */
#pragma once
#include "GameObject.h"

class Mesh;

class Gauge :public GameObject
{
private:
	float m_Min;
	float m_Max;
	float m_Value;

	GameObject* m_bar;
	GameObject* m_frame;
	Transform m_transform;

	Mesh* barmesh;
public:
	Vector3 m_offset;
	Gauge();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	void SetParam(float max, float min);
	void SetValue(float value);
	void SetTransform(Transform& trans);
	void SetOffset(Vector3 value);
};

// EOF