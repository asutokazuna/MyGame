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
	// �O�ʃJ�����O (FBX�͕\�������]���邽��)
	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetZWrite(false);
	CGraphics::SetBlendState(BS_NONE);			// �A���t�@�������Ȃ�
	// FBX�t�@�C���\��
	XMFLOAT4X4 world;
	CCamera* pCamera = CCamera::Get();
	XMFLOAT3& vEye = pCamera->GetEye();
	XMStoreFloat4x4(&world, XMMatrixTranslation(
		vEye.x, vEye.y, vEye.z));
	m_Model->Render(world, pCamera->GetView(), pCamera->GetProj(), eOpacityOnly);
}

// EOF