#include "ThirdPersonCamera.h"


// 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const Vector3 g_vEye(0.0f, 50.0f, -150.0f);
	const Vector3 g_vLook(0.0f, 50.0f, 0.0f);
	const Vector3 g_vUp(0.0f, 1.0f, 0.0f);
}

ThirdPersonCamera::ThirdPersonCamera()
{
}


ThirdPersonCamera::~ThirdPersonCamera()
{
}

void ThirdPersonCamera::Awake()
{
	HRESULT hr = S_OK;
	//m_isActive = false;
	//m_vLook = g_vLook;
	//m_fFOVY = XMConvertToRadians(45);
	//m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	//m_fNearZ = 10.0f;
	//m_fFarZ = 10000.0f;
	//m_vUp = g_vUp;
	//transform->position = g_vEye;
	//m_pos = m_oldPos = Vector3();
	//UpdateMatrix();
}
