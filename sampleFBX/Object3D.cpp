/**
 * @file Object3D.h
 * @brief 3D�I�u�W�F�N�g�p�R���|�[�l���g
 */
#include "Object3D.h"
#include "CCamera.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Graphics.h"

/**
 * @breif �R���X�g���N�^
 */
Object3D::Object3D()
{
	XMStoreFloat4x4(&m_world, XMMatrixIdentity());
	m_ModelIndex = 0;
}

/**
 * @brief ������
 * @return �Ȃ�
 */
HRESULT Object3D::Init()
{
	Transform& Transform = m_Parent->GetTransform();
	m_Transform = &Transform;
	HRESULT hr = S_OK;

	m_light.m_direction = XMFLOAT3(0, 0, 0);
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBX���f��

	return hr;
}

/**
 * @breif �I��
 * @return �Ȃ�
 */
void Object3D::Uninit()
{
}

/**
 * @breif �X�V
 * @return �Ȃ�
 */
void Object3D::Update()
{
}

/**
 * @breif �`��
 * @return �Ȃ�
 */
void Object3D::Draw()
{
	CCamera* pCamera = CCamera::Get();

	m_world = MyMath::StoreXMFloat4x4(*m_Transform);

	// FBX�t�@�C���\��
	m_Model->Render(m_world, pCamera->GetView(), pCamera->GetProj(), eOpacityOnly);
}

/**
 * @breif �`��
 * @return �Ȃ�
 */
void Object3D::DrawAlpha()
{

	CGraphics::SetCullMode(CULLMODE_CW);
	CGraphics::SetZWrite(true);
	CGraphics::SetBlendState(BS_NONE);
	CCamera* pCamera = CCamera::Get();
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBX���f��

	m_Model->Render(m_world, pCamera->GetView(), pCamera->GetProj(), eTransparentOnly);
}

/**
 * @brief �\�����郂�f���̎�ނ�ݒ�
 * @param	kind	�\�����郂�f���̎��ʎq
 * @retrun ����
 */
Object3D& Object3D::SetModel(int kind) {
	m_ModelIndex = kind;
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBX���f��
	return *this;
}

/**
 * @brief �\�����郂�f���̎�ނ�ݒ�
 * @param	kind	�\�����郂�f���̎��ʎq
 * @retrun ����
 */
Object3D& Object3D::SetModel(ModelKind kind) {
	m_ModelIndex = (int)kind;
	m_Model = ModelData::GetData((ModelKind)m_ModelIndex);	//!< FBX���f��
	return *this;
}

/**
 * @brief �\�����郂�f���̐F��ݒ�
 * @param	mat	�\������F
 * @retrun ����
 */
void Object3D::SetMaterial(TFbxMaterial& mat)
{
	m_Model->SetMaterial(&mat);
}

// EOF