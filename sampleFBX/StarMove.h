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
	float m_rot;
	ShaderInfo* m_backshader;
	float m_alpha;
	float m_add;
	Vector3 m_color;
	Vector3 m_size;
	Vector3 m_rogoSize;
	Vector3 m_move;
	int m_time;
public:
	/**
	 * @brief 初期化
	 * @retrun なし
	 */
	void Awake();
		
	/**
	 * @brief 初期化
	 * @retrun なし
	 */
	HRESULT Init();
		
	/**
	 * @brief 更新
	 * @retrun なし
	 */
	void Update();
		
	/**
	 * @brief 生成時処理
	 * @retrun なし
	 */
	void Create();
	void Move();
	void Create(Vector3 pos);
	bool IsLife();
	void SetFrontMesh() {

	}

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