/**
 * @file DigitNumber
 * @brief 数字表示
 * @author Ariga
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
	ShaderInfo* m_shader;	//!< シェーダー
	Mesh* m_mesh;		//!< 表示するメッシュ

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();
};

// EOF