/**
 * @file TitleStart
 * @brief タイトルのスタートボタン
 */
#pragma once
#include "GameObject.h"

// 前方宣言
class Mesh;
class DefaultShaderInfo;

/**
 * @class TitleStart
 * @brief フェードしながらスタートテキストを表示する
 */
class TitleStart :public GameObject
{
private:
	Mesh* m_mesh;		//!< メッシュ
	float m_add;		//!< アルファ値の変化量
	DefaultShaderInfo* m_shader;	//!< シェーダー
	float m_alpha;		//!< アルファ値

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 更新
	 * @return なし
	 */
	void Update();
};

// EOF