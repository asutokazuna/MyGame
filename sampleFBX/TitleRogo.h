/**
 * @file TitleRogo
 * @brief タイトルロゴ
 */
#pragma once
#include "GameObject.h"

class Mesh;
class ClothShaderInfo;
class DefaultShaderInfo;

/**
 * @class TitleRogo
 */
class TitleRogo :public GameObject
{
private:
	Mesh* m_mesh;
	ClothShaderInfo* m_clothshader;
	DefaultShaderInfo* m_defaultshader;
	float m_time;
	float m_power;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
	void Move();
	bool IsArrive();

	void MovePower();

	void InitParam();
};

// EOF