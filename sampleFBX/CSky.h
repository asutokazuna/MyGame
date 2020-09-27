/**
 * @file CSky.h
 * @brief �X�J�C�h�[���N���X
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

