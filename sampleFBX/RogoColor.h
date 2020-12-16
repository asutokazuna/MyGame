/**
 * @file RogoColor
 * @brief 色付きのタイトルロゴオブジェクト
 */
#pragma once
#include "GameObject.h"

//前方宣言
class DefaultShaderInfo;
class Mesh;

/**
 * @class RogoColor 
 * @brief 色付きのタイトルロゴ
 */
class RogoColor :public GameObject
{
private:
	DefaultShaderInfo* m_shader;	//!< シェーダー
	Mesh* m_mesh;					//!< メッシュ
public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF