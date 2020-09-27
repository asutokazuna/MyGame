/**
 * @file Light
 * @brief ライトクラス
 */
#include "Light.h"
#include "FbxModel.h"
#include <direct.h>

using namespace DirectX;
//
//#define LIGHT0_DIFFUSE	XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
//#define LIGHT0_AMBIENT	XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
//#define LIGHT0_SPECULAR	XMFLOAT4(0.f,0.f,0.f,1.0f)
//#define LIGHT0_DIR	XMFLOAT3(0.0f,-1.0f,-1.0f)

#define LIGHT0_DIFFUSE	XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define LIGHT0_AMBIENT	XMFLOAT4(0.2f,0.2f,0.2f,1.0f)
#define LIGHT0_SPECULAR	XMFLOAT4(1.0f,1.0f,1.0f,1.0f)

#define LIGHT0_DIR_X	(-1.0f)
#define LIGHT0_DIR_Y	(-1.0f)
#define LIGHT0_DIR_Z	(1.0f)
CFbxLight* Light::m_light = nullptr;

CFbxLight* Light::Get()
{
	if (m_light == nullptr) {
		m_light = new CFbxLight();
		XMFLOAT3 vecDir;
		m_light->m_diffuse = LIGHT0_DIFFUSE;
		m_light->m_ambient = LIGHT0_AMBIENT;
		m_light->m_specular = LIGHT0_SPECULAR;

		// ライトの方向の設定
		//vecDir = LIGHT0_DIR;
		//XMStoreFloat3(&m_light->m_direction, XMVector3Normalize(XMLoadFloat3(&vecDir)));
		XMStoreFloat3(&m_light->m_direction,
			XMVector3Normalize(XMVectorSet(LIGHT0_DIR_X, LIGHT0_DIR_Y, LIGHT0_DIR_Z, 0.0f)));
		//m_light->m_direction = XMFLOAT3(0, 0, 0);
	}
	return m_light;
}

void Light::Fin()
{
	delete m_light;
}

// EOF