#include "ShadowCamera.h"
#include "Light.h"
#include "FbxModel.h"
#include "ImGui/imgui.h"

const float NEARZ = 10.0f;
const float FAR_Z = 10000.0f;

static Vector3 pos;
static Vector3 look;

static const float g_num = -1000;

void ShadowCamera::Awake()
{
	//transform->position = pos = Vector3(Light::GetPos().x, Light::GetPos().y, Light::GetPos().z);
	transform->position = pos = Vector3(Light::Get()->m_direction.x * g_num, Light::Get()->m_direction.y * g_num, Light::Get()->m_direction.z * g_num);
	m_vLook = look = Vector3(0.0f, 0.0f, 0.0f); 
	transform->position  + Vector3(Light::Get()->m_direction.x, Light::Get()->m_direction.y, Light::Get()->m_direction.z);
	m_vUp = Vector3(0.0f, 1.0f, 0.0f);

	m_fFOVY = XMConvertToRadians(45);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_width  = 2000;
	m_height = 2000;
	m_fNearZ = NEARZ;
	m_fFarZ = FAR_Z;

	m_target = nullptr;

	transform->quaternion = MyMath::LookAt(transform->position, m_vLook);
	UpdateMatrixOrthograph();
}

HRESULT ShadowCamera::Init()
{
	CCamera::Init();

	transform->position = Vector3(Light::GetPos().x, Light::GetPos().y, Light::GetPos().z);
	transform->quaternion = MyMath::LookAt(transform->position, m_vLook);
	m_target = nullptr;

	return S_OK;
}

void ShadowCamera::Update()
{
	CCamera::Update();
	if (m_target != nullptr) {
		transform->position = pos + m_target->GetTransform().position;
		m_vLook = look + m_target->GetTransform().position;
	}

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