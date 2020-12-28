/**
 * @file DigitNumber
 * @brief 数字表示
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class Mesh;
class ShaderInfo;

/** 
 * @class DigitNumber
 * @brief 数字1桁表示オブジェクト
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