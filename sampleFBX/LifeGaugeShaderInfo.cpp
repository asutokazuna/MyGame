#include "LifeGaugeShaderInfo.h"
#include "ShaderData.h"
#include "Graphics.h"
#include "MyMath.h"
#include "Transform.h"
#include "Mesh.h"
#include "FbxModel.h"
#include "Light.h"
#include "CCamera.h"
#include "GameObject.h"
#include "TextureData.h"

#define NUM_VSCONSTANT (1)
#define NUM_PSCONSTANT (1)

//*****************************************************************************
// �V�F�[�_�ɓn���l
struct SHADER_GLOBAL {
	XMMATRIX	mWVP;		// ���[���h�~�r���[�~�ˉe�s��(�]�u�s��)
	XMMATRIX	mW;			// ���[���h�s��(�]�u�s��)
	XMMATRIX	mTex;		// �e�N�X�`���s��(�]�u�s��)
};
struct SHADER_GLOBAL2 {
	XMVECTOR	vEye;		// ���_���W
							// ����
	XMVECTOR	vLightDir;	// ��������
	XMVECTOR	vLa;		// �����F(�A���r�G���g)
	XMVECTOR	vLd;		// �����F(�f�B�t���[�Y)
	XMVECTOR	vLs;		// �����F(�X�y�L����)
							// �}�e���A��
	XMVECTOR	vAmbient;	// �A���r�G���g�F(+�e�N�X�`���L��)
	XMVECTOR	vDiffuse;	// �f�B�t���[�Y�F
	XMVECTOR	vSpecular;	// �X�y�L�����F(+�X�y�L�������x)
	XMVECTOR	vEmissive;	// �G�~�b�V�u�F
	XMFLOAT4	value;		// x:臒l�@y.z.w:���g�p
};

/**
 * @brief �R���X�g���N�^
 */
LifeGaugeShaderInfo::LifeGaugeShaderInfo() :m_TexWorld(XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)), m_pTexture(nullptr)
{
	m_VertexConstant = new ID3D11Buffer*();
	m_PixelConstant = new ID3D11Buffer*();
	m_VSKind = ShaderData::VS_VERTEX;
	m_PSKind = ShaderData::PS_LIFEGAUGE;
}

/**
 * @brief �f�X�g���N�^
 */
LifeGaugeShaderInfo::~LifeGaugeShaderInfo()
{
	delete m_VertexConstant;
	delete m_PixelConstant;
}

/**
 * @brief ������
 * @retrun �Ȃ�
 */
void LifeGaugeShaderInfo::Awake()
{
	CreateConstantBuffer<SHADER_GLOBAL>(m_VertexConstant);
	CreateConstantBuffer<SHADER_GLOBAL2>(&m_PixelConstant[0]);
	m_View = CCamera::Get()->GetView();
	m_Proj = CCamera::Get()->GetProj();
	m_world = XMFLOAT4X4();
}

/**
 * @brief �I��
 * @retrun �Ȃ�
 */
void LifeGaugeShaderInfo::Uninit()
{
	for (int i = 0; i < NUM_VSCONSTANT; ++i) {
		SAFE_RELEASE(m_VertexConstant[i]);
	}
	for (int i = 0; i < NUM_PSCONSTANT; ++i) {
		SAFE_RELEASE(m_PixelConstant[i]);
	}
}

/**
 * @brief �R���X�^���g�o�b�t�@�̍X�V
 * @retrun �Ȃ�
 */
void LifeGaugeShaderInfo::UpdateConstant()
{

	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11SamplerState* pSamplerState = CGraphics::GetSamplerState();

	SetShader();

	pDeviceContext->PSSetSamplers(0, 1, &pSamplerState);
	pDeviceContext->PSSetShaderResources(0, 1, &m_pTexture);

	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&m_View) * XMLoadFloat4x4(&m_Proj));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(XMLoadFloat4x4(&m_TexWorld));
	pDeviceContext->UpdateSubresource(m_VertexConstant[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_VertexConstant[0]);
	SHADER_GLOBAL2 cb2;
	cb2.vEye = XMLoadFloat3(&CCamera::Get()->GetEye());
	CFbxLight* light = Light::Get();
	// �Ƃ肠�������C�g����
	cb2.vLightDir = XMVectorSet(0, 0, 0, 0.f);
	cb2.vLa = XMLoadFloat4(&light->m_ambient);
	cb2.vLd = XMLoadFloat4(&light->m_diffuse);
	cb2.vLs = XMLoadFloat4(&light->m_specular);
	MATERIAL* pMaterial = m_material;
	if (!pMaterial) pMaterial = m_material;
	cb2.vDiffuse = XMLoadFloat4(&pMaterial->Diffuse);
	cb2.vAmbient = XMVectorSet(pMaterial->Ambient.x, pMaterial->Ambient.y, pMaterial->Ambient.z,
		(m_pTexture != nullptr) ? 1.f : 0.f);
	cb2.vSpecular = XMVectorSet(pMaterial->Specular.x, pMaterial->Specular.y, pMaterial->Specular.z, pMaterial->Power);
	cb2.vEmissive = XMLoadFloat4(&pMaterial->Emissive);
	cb2.value.x = m_SizePer;
	pDeviceContext->UpdateSubresource(m_PixelConstant[0], 0, nullptr, &cb2, 0, 0);
	pDeviceContext->PSSetConstantBuffers(1, 1, &m_PixelConstant[0]);
}

/**
 * @brief �e�N�X�`���̃Z�b�g
 * @param[in] kind �e�N�X�`���̎�ނ�enum�ԍ�
 * @retrun �Ȃ�
 */
LifeGaugeShaderInfo* LifeGaugeShaderInfo::SetTexture(int kind)
{
	m_pTexture = TextureData::GetInstance().GetData(kind);

	return this;
}

/**
 * @brief �e�N�X�`���̃Z�b�g
 * @param[in] texture �e�N�X�`���f�[�^
 * @retrun �Ȃ�
 */
void LifeGaugeShaderInfo::SetTexture(ID3D11ShaderResourceView* texture)
{
	m_pTexture = texture;
}

void LifeGaugeShaderInfo::SetView(XMFLOAT4X4 view)
{
	m_View = view;
}

void LifeGaugeShaderInfo::SetProj(XMFLOAT4X4 proj)
{
	m_Proj = proj;
}

/**
 * @brief �R���X�^���g�o�b�t�@�̃f�[�^���Z�b�g
 * @param[in] key �ϐ��̔��ʂ���L�[
 * @param[in] value �Z�b�g����l
 * @retrun �Ȃ�
 */
void LifeGaugeShaderInfo::SetFloat(std::string key, XMFLOAT4X4 value)
{
	if (key == "Proj") {
		m_Proj = value;
	}
	else if (key == "View") {
		m_View = value;
	}
	else if (key == "World") {
		m_world = value;
	}
	else if ("TexWorld")
	{
		m_TexWorld = value;
	}
}

void LifeGaugeShaderInfo::SetFloat(std::string key, float value)
{
	if (key == "Life") {
		m_SizePer = value;
	}
}

/**
 * @brief UV�̐ݒ�
 * @param[in] uv UV�ʒu
 * @param[in] scale UV�T�C�Y
 * @return �Ȃ�
 */
void LifeGaugeShaderInfo::SetUV(Vector3 uv, Vector3 scale)
{
	XMMATRIX mtx = XMMatrixIdentity();

	mtx = XMMatrixScaling(scale.x, scale.y, scale.z);

	mtx *= XMMatrixTranslation(uv.x, uv.y, uv.z);

	XMStoreFloat4x4(&m_TexWorld, mtx);
}

// EOF