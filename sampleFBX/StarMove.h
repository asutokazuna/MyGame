/**
 * @file StarMove
 * @brief 星のエフェクトの動き
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

// 前方宣言
class Transform;
class ShaderInfo;

/**
 * @class StarMove
 * @brief 星のエフェクトの動き
 */
class StarMove :public Component
{
private:
	Transform * m_parentTrans;
	ShaderInfo* m_backshader;
	Vector3 m_size;
	Vector3 m_move;
	int m_time;
public:
	/**
	 * @brief 初期化
	 * @retrun なし
	 */
	void Awake();
		
	/**
	 * @brief 生成時処理
	 * @retrun なし
	 */;
	void Create(Vector3 pos);
	
	/**
	 * @brief 移動処理
	 * @return なし
	 */
	void Move();
	bool IsLife();

	/**
	 * @brief パーティクルの背景のシェーダーをセット
	 * @param[in] shader セットするシェーダー
	 * @return なし
	 */
	void SetBackShader(ShaderInfo* shader) {
		m_backshader = shader;
	}
};

// EOF