#include "ShadowCamera.h"
#include "Light.h"
#include "FbxModel.h"
#include "ImGui/imgui.h"

const float NEARZ = 10.0f;
const float FAR_Z = 10000.0f;

void ShadowCamera::Awake()
{
	transform->position = Vector3(Light::GetPos().x, Light::GetPos().y, Light::GetPos().z);
	m_vLook = Vector3(0.0f, 0.0f, 0.0f); 
	transform->position  + Vector3(Light::Get()->m_direction.x, Light::Get()->m_direction.y, Light::Get()->m_direction.z);
	m_vUp = Vector3(0.0f, 1.0f, 0.0f);

	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_width  = 1000;
	m_height = 1000;
	m_fNearZ = NEARZ;
	m_fFarZ = FAR_Z;

	transform->quaternion = MyMath::LookAt(transform->position, m_vLook);
	UpdateMatrixOrthograph();
}

void ShadowCamera::Draw()
{
#if _DEBUG
	if (ImGui::TreeNode("shadowCamera")) {
		float *size[2] = { &m_width , &m_height};
		ImGui::SliderFloat2("size", *size, 1.0f, 1000.0f);
		ImGui::TreePop();
	}
#endif
	UpdateMatrixOrthograph();
}

// EOF