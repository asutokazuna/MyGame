#include "TitleCamera.h"
// 定数
namespace {	// 空のnamespaceを付けるとこのcppだけのグローバル変数になる
	const Vector3 g_vEye(0.0f, 0.0f, 0.0f);
	const Vector3 g_vLook(0.0f, 1.0f, 10.0f);
}

static float radian = 0;

/**
 * 定円
 * 動円
 * 描画円
 * 角度
 */
Vector3 Calctrochoid(float r1, float r2, float r3, float rad)
{
	Vector3 pos = Vector3();

	pos.x = (r1 - r2) * cosf(rad) + r3 * cosf((r1 - r2) / r2 * rad);
	pos.y = (r1 - r2) * sinf(rad) + r3 * sinf((r1 - r2) / r2 * rad);

	return pos;
}

Vector3 Calcgaitrochoid(float r1, float r2, float r3, float rad)
{
	Vector3 pos = Vector3();

	pos.x = (r1 + r2) * cosf(rad) - r3 * cosf((r1 + r2) / r2 * rad);
	pos.z = (r1 + r2) * sinf(rad) - r3 * sinf((r1 + r2) / r2 * rad);

	return pos;
}

void TitleCamera::Awake()
{
	HRESULT hr = S_OK;
	m_isActive = false;
	m_fFOVY = XMConvertToRadians(60);
	m_fAspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	m_fNearZ = 10.0f;
	m_fFarZ = 10000.0f;

	this->transform->position = g_vEye;
	m_vLook = g_vLook;

	Transform* trs = this->transform;
	XMFLOAT4X4 mtxWorld = MyMath::StoreXMFloat4x4(*trs);

	// 始点と注視点を移動、上方ベクトルを回転
	XMMATRIX world = XMLoadFloat4x4(&mtxWorld);
	radian = 0;
	Vector3 lookpos = Calcgaitrochoid(60, 20, 20, radian);
	m_vLook = g_vLook + lookpos;
	UpdateMatrix();
}

void TitleCamera::Uninit()
{
	CCamera::Uninit();
}

void TitleCamera::Update()
{
	radian += 0.001f;

	Vector3 lookpos = Calcgaitrochoid(60, 20, 20, radian);
	
	m_vLook = g_vLook + lookpos;

	// 行列更新
	CCamera::UpdateMatrix();
}

void TitleCamera::Draw()
{
	if (ImGui::TreeNode("TitleCamera")) {
		Vector3 te2 = transform->position;

		ImGui::SliderFloat("pos x", &te2.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos y", &te2.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("pos z", &te2.z, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look x", &m_vLook.x, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look y", &m_vLook.y, -1000.0f, 500.0f);
		ImGui::SliderFloat("Look z", &m_vLook.z, -1000.0f, 500.0f);	
		Vector3 te = transform->GetUp();
		ImGui::SliderFloat("transLookUp x", &te.x, -1.0f, 1.0f);
		ImGui::SliderFloat("transLookUp y", &te.y, -1.0f, 1.0f);
		ImGui::SliderFloat("transLookUp z", &te.z, -1.0f, 1.0f);
		ImGui::TreePop();
	}
}

// EOF