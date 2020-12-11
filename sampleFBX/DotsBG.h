/**
 * @file DotsBG
 * @brief 水玉模様のオブジェクト
 */
#pragma once
#include "GameObject.h"

class Mesh;
class DefaultShaderInfo;

/** 
 * @class DotsBG
 * @biref 水玉背景
 */
class DotsBG :public GameObject
{
private:
	Mesh* m_mesh;
	DefaultShaderInfo* m_shader;

public:
	/**
	 * @brief 初期化
	 * @retrun なし
	 */
	void Awake();
		
	///**
	// * @brief 初期化
	// * @retrun なし
	// */
	//HRESULT Init();
	//	
	///**
	// * @brief 更新
	// * @retrun なし
	// */
	//void Update();
};

// EOF