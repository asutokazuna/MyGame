/**
 * @file DigitNumber
 * @brief �����\��
 */
#pragma once
#include "GameObject.h"

// �O���錾
class Mesh;
class ShaderInfo;

/** 
 * @class DigitNumber
 * @brief ����1���\���I�u�W�F�N�g
 */
class DigitNumber :public GameObject
{
private:
	ShaderInfo* m_shader;
	Mesh* m_mesh;
public:
	void Awake();
};

// EOF