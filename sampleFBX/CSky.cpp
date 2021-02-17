#include "CSky.h"
#include "CCamera.h"
#include "ModelData.h"
#include "FbxModel.h"
#include "Graphics.h"
#include "ShaderData.h"

static CFbxLight light = CFbxLight();

HRESULT CSky::Init()
{
	m_Model = ModelData::GetData(MODEL_SKY);

	light.m_direction = { 0,0,0 };
	m_Model->SetLight(light);

	return E_NOTIMPL;
}

void CSky::Draw()
{
	// 前面カリング (FBXは表裏が反転するため)
	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetZWrite(false);
	CGraphics::SetBlendState(BS_NONE);			// アルファ処理しない
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(ShaderData::PS_KIND::PS_PIXEL3D_UNSHADOW);
	
	pDeviceContext->VSSetShader(vs, nullptr, 0);
	pDeviceContext->PSSetShader(ps, nullptr, 0);
	// 頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(il);
	// FBXファイル表示
	XMFLOAT4X4 world;
	CCamera* pCamera = CCamera::Get();
	XMFLOAT3 vEye = pCamera->GetEye();
	XMStoreFloat4x4(&world, XMMatrixTranslation(
		vEye.x, vEye.y, vEye.z));
	m_Model->Render(world, pCamera->GetView(), pCamera->GetProj(), eOpacityOnly);
#ifdef _DEBUG
	if (ImGui::TreeNode("Sky")) {
		ImGui::SliderFloat("Pos x", &world._41, -1000.0f, 500.0f);
		ImGui::SliderFloat("Pos y", &world._42, -1000.0f, 500.0f);
		ImGui::SliderFloat("Pos z", &world._43, -1000.0f, 500.0f);
		ImGui::TreePop();
	}
#endif
}

// EOF