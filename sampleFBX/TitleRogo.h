/**
 * @file TitleRogo
 * @brief タイトルロゴ
 */
#pragma once
#include "GameObject.h"

class Mesh;

/**
 * @class TitleRogo
 */
class TitleRogo :public GameObject
{
private:
	Mesh* m_mesh;
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF