#pragma once
#include "CCamera.h"

/**
 * @class ShadowCamera
 * @brief 深度バッファシャドウ用カメラ
 */
class ShadowCamera :public CCamera
{
private:
	GameObject* m_target;
public:
	void Awake();
	HRESULT Init();
	void Update();
	void Draw();
	void SetTarget(GameObject* obj) {
		m_target = obj;
	}
};

// EOF