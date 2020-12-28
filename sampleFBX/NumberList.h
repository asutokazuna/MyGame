/**
 * @file NumberList
 * @brief 文字表示オブジェクト
 */
#pragma once
#include "GameObject.h"
#include "MyMath.h"

class DigitNumber;

class NumberList :public GameObject
{
public:
	NumberList(int num);
	void Awake();
};

