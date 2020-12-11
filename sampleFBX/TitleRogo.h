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
	float m_fadeValue;
	float m_endPos;

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
	bool Move(float startPos, float endPosX, int time);
	bool IsArrive();

	bool MovePower(float power);

	bool Fade(float speed);

	bool FadeOUT(float speed);

	void InitParam();
};

// EOF