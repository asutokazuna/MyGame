/**
 * @file Light
 * @brief ���C�g�N���X
 */
#pragma once

class CFbxLight;
class Light
{
private:
	static CFbxLight* m_light;
public:
	Light();
	~Light();
	static CFbxLight* Get();
	static void Fin();
};

// EOF