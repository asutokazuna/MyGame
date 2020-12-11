#pragma once
#include "Component.h"
#include "MyMath.h"

class ShaderInfo;

/**
 * @class DotsBGMove
 * @brief 水玉模様の動き
 */
class DotsBGMove :public Component
{
	Vector3 uv;
	ShaderInfo* m_shader;
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
	//HRESULT Init();
		
	/**
	 * @brief 更新
	 * @retrun なし
	 */
	void Update();

	void SetShader(ShaderInfo* shader);
};

// EOF