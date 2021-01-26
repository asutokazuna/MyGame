#include "Default3DShaderInfo.h"
#include "ShaderData.h"
#include "CCamera.h"
#include "Light.h"
#include "FbxModel.h"

/**
 * @brief コンストラクタ
 */
Default3DShaderInfo::Default3DShaderInfo()
{
	m_VSKind = ShaderData::VS_VERTEX3D;
	m_PSKind = ShaderData::PS_PIXEL3D;

//	m_cbufferManager.Create< SHADER_GLOBAL>("SHADER_GLOBAL");
//	m_cbufferManager.Create< SHADER_MATERIAL>("SHADER_MATERIAL");
//	m_cbufferManager.Create< SHADER_BONE>("SHADER_BONE");
}


Default3DShaderInfo::~Default3DShaderInfo()
{
}

void Default3DShaderInfo::Awake()
{
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
}


/**
 * @brief 更新とバインド
 * @return なし
 */
void Default3DShaderInfo::UpdateConstant()
{

}
//
///**
// * @brief 更新とバインド
// * @return なし
// */
//void Default3DShaderInfo::UpdateConstant()
//{
//	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
//	XMMATRIX mtxView = XMLoadFloat4x4(&m_View);
//	XMMATRIX mtxProj = XMLoadFloat4x4(&m_Proj);
//	m_SG->mW = XMMatrixTranspose(mtxWorld);
//	m_SG->mWVP = mtxWorld * mtxView * mtxProj;
//	m_SG->mWVP = XMMatrixTranspose(m_SG->mWVP);
//	XMFLOAT3 camera = CCamera::Get()->GetEye();
//	m_SG->vEye = XMLoadFloat3(&camera);
//
//	CFbxLight* light = Light::Get();
//	m_SG->vLightDir = XMLoadFloat3(&light->m_direction);
//	m_SG->vLd = XMLoadFloat4(&light->m_diffuse);
//	m_SG->vLa = XMLoadFloat4(&light->m_ambient);
//	m_SG->vLs = XMLoadFloat4(&light->m_specular);
//	m_SG.BindVS(0);
//	m_SG.BindPS(0);
//}
//
///**
// * @brief 更新とバインド
// * @return なし
// */
//void Default3DShaderInfo::UpdateMatCBuffer(TFbxMaterial* pMaterial)
//{
//	m_SM->vAmbient = XMLoadFloat4(&pMaterial->Ka);
//	m_SM->vDiffuse = XMLoadFloat4(&pMaterial->Kd);
//	m_SM->vSpecular = XMLoadFloat4(&pMaterial->Ks);
//	m_SM->vEmissive = XMLoadFloat4(&pMaterial->Ke);
//	m_SM.BindVS(1);
//	m_SM.BindPS(1);
//}
//
///**
// * @brief 更新とバインド
// * @return なし
// */
//void Default3DShaderInfo::UpdateBoneCBuffer()
//{		// ボーンをシェーダに渡す
//	m_SB.BindVS(2);
//	m_SB.BindPS(2);
//}

void Default3DShaderInfo::SetFloat(std::string key, XMFLOAT4X4 value)
{
	if (key == "m_Proj") {
		m_Proj = value;
	}
	else if (key == "m_View") {
		m_View = value;
	}
	else if (key == "m_world") {
		m_world = value;
	}
	else if ("m_TexWorld")
	{
		m_TexWorld = value;
	}
}

// EOF