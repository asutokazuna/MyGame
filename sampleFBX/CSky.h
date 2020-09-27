/**
 * @file CSky.h
 * @brief スカイドームクラス
 */
#pragma once
#include "main.h"
#include "GameObject.h"
#include <Windows.h>

class CFbxModel;

class CSky: public GameObject
{
private:
	CFbxModel* m_Model;
public:
	HRESULT Init();
	void Draw();
};

