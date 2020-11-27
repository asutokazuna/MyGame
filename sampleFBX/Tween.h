/**
 * @file Tween.cpp
 * @brief 補間クラス
 */
#pragma once
#include <vector>
#include <functional>
#include "MyMath.h"

// 前方宣言
class Transform;

/**
 * @class Tween
 * @brief 補間
 */
class Tween
{
protected:
	//Vector3 m_startPos;
	//Vector3 m_endPos;
	float	m_Threshold;
	//std::function<void(int)> m_easeFunc;
	//
	//static std::vector<Tween> m_List;
	//
	//void CallBacK(const std::function<void()> &callback);
public:
	Tween() {
		m_Threshold = 0;
	}
	//static void Update();
	//
	//Tween* Move(Transform& obj, Vector3 startPos, Vector3 endPos, float time);
};

// EOF