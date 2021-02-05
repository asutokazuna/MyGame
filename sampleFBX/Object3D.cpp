/**
 * @file Object3D.h
 * @brief 3Dオブジェクト用コンポーネント
 */
#include "Object3D.h"
#include "CCamera.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Graphics.h"

/**
 * @breif コンストラクタ
 */
Object3D::Object3D()
{
	XMStoreFloat4x4(&m_world, XMMatrixIdentity());
	m_ModelIndex = 0;
}

/**
 * @brief 初期化
 * @return なし
 */
HRESULT Object3D::Init()
{
	HRESULT hr = S_OK;

	m_light.m_direction = XMFLOAT3(0, 0, 0);
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBXモデル

	return hr;
}

/**
 * @breif 描画
 * @return なし
 */
void Object3D::Draw()
{
	CCamera* pCamera = CCamera::Get();

	//if (m_Parent->GetParent() == nullptr) {
	//	//m_ParentTransform->localPosition = m_ParentTransform->position;
	//	//m_ParentTransform->localRotation = m_ParentTransform->rotation;
	//	//m_ParentTransform->localScale = m_ParentTransform->scale;
	//	//m_ParentTransform->localQuaternion = m_ParentTransform->quaternion;
	//}
	//else {
	//	m_ParentTransform->position = m_Parent->GetParent()->GetTransform().position;
	//	m_ParentTransform->rotation = m_Parent->GetParent()->GetTransform().rotation;
	//	m_ParentTransform->scale = m_Parent->GetParent()->GetTransform().scale;
	//	m_ParentTransform->quaternion = m_Parent->GetParent()->GetTransform().quaternion;
	//}

	m_world = MyMath::StoreXMFloat4x4(*m_ParentTransform);

	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetZWrite(true);
	CGraphics::SetBlendState(BS_NONE);
	// FBXファイル表示
	m_Model->Render(m_world, pCamera->GetView(), pCamera->GetProj(), eOpacityOnly);
}

/**
 * @breif 描画
 * @return なし
 */
void Object3D::DrawAlpha()
{
	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetZWrite(true);
	CGraphics::SetBlendState(BS_NONE);
	CCamera* pCamera = CCamera::Get();
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBXモデル

	m_Model->Render(m_world, pCamera->GetView(), pCamera->GetProj(), eTransparentOnly);
}

/**
 * @brief 表示するモデルの種類を設定
 * @param	kind	表示するモデルの識別子
 * @retrun 実体
 */
Object3D& Object3D::SetModel(int kind) {
	m_ModelIndex = kind;
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBXモデル
	return *this;
}

/**
 * @brief 表示するモデルの種類を設定
 * @param	kind	表示するモデルの識別子
 * @retrun 実体
 */
Object3D& Object3D::SetModel(ModelKind kind) {
	m_ModelIndex = (int)kind;
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBXモデル
	return *this;
}

/**
 * @brief 表示するモデルの色を設定
 * @param	mat	表示する色
 * @retrun 実体
 */
void Object3D::SetMaterial(TFbxMaterial& mat)
{
	m_Model->SetMaterial(&mat);
}

// EOF