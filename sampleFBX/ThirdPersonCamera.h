/**
 * @file 
 * @brief 三人称視点の通常時ゲームカメラコンポーネント
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

class ThirdPersonCamera :public Component
{
private:
	Vector3 m_pos;
	Vector3 m_oldPos;
	float m_threshold;
public:
	ThirdPersonCamera();
	~ThirdPersonCamera();
	/**
	* @brief 初期化処理
	* @return なし
	*/
	void Awake();
	//HRESULT Init();
	//void Uninit();
	//void LateUpdate();
	//void Draw();
};

// EOF