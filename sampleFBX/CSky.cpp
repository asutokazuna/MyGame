#include "CSky.h"
#include "CCamera.h"
#include "ModelData.h"
#include "FbxModel.h"
#include "Graphics.h"

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
	// FBXファイル表示
	XMFLOAT4X4 world;
	CCamera* pCamera = CCamera::Get();
	XMFLOAT3& vEye = pCamera->GetEye();
	XMStoreFloat4x4(&world, XMMatrixTranslation(
		vEye.x, vEye.y, vEye.z));
	m_Model->Render(world, pCamera->GetView(), pCamera->GetProj(), eOpacityOnly);
}

// EOF