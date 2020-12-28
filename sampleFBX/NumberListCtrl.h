#pragma once
#include "Component.h"
#include <list>
#include "MyMath.h"

class DigitNumber;

/**
 * @class NumberListCtrl
 */
class NumberListCtrl :public Component
{
private:
	std::list<DigitNumber*> m_NumberList;
	float m_width;

public:
	void Awake();
	HRESULT Init();
	void SetNumber(int num);
	void SetPos(Vector3 pos);
	void SetWidth(float width);
};

// EOF