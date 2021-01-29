/**
 * @file Light
 * @brief ライトクラス
 */
#pragma once
#include "main.h"

class CFbxLight;
class Light
{
private:
	static CFbxLight* m_light;
	static XMFLOAT3 pos;
public:
	Light();
	~Light();
	static CFbxLight* Get();
	static void Fin();
	static XMFLOAT3 GetPos() { return pos; }
};

// EOF