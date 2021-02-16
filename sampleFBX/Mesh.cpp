/**
 * @file Mesh
 * @brief メッシュクラス
 * @author Ariga
 */
#include "Mesh.h"
#include "Graphics.h"
#include "Transform.h"
#include "ShaderInfo.h"
#include "DefaultShaderInfo.h"

/**
 * @brief コンストラクタ
 */
Mesh::Mesh()
{
	m_transform = nullptr;
	m_material = nullptr;
	m_shader = nullptr;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_nNumVertex = 0;
	m_nNumIndex = 0;
	m_primitiveType = PT_UNDEFINED;
	m_default = new DefaultShaderInfo();
	m_material = &m_default->GetMaterial();
	m_BSKind = BS_ALPHABLEND;
	m_isZwerite = true;
}

/**
 * @brief デストラクタ
 */
Mesh::~Mesh()
{
	delete m_default;
}

/**
 * @brief 初期化処理
 * @return なし
 */
void Mesh::Awake()
{
	m_default->m_Parent = this->m_Parent;
	m_default->Awake();
	m_default->Init();
	m_default->SetFloat("World", MyMath::StoreXMFloat4x4(*m_transform));
}

/**
 * @brief 終了処理
 * @return なし
 */
void Mesh::Uninit()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

/**
 * @brief 更新処理
 * @return なし
 */
void Mesh::Update()
{
}

/**
 * @brief 描画処理
 * @return なし
 */
void Mesh::Draw()
{	
	CGraphics::SetCullMode(CULLMODE_NONE);
	CGraphics::SetZWrite(m_isZwerite);
	CGraphics::SetBlendState(m_BSKind);
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();

	// 頂点バッファをセット
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	// インデックスバッファをセット
	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	if (m_shader == nullptr) {
		m_default->UpdateConstant();
	}
	else {
		m_shader->UpdateConstant();
	}
	// プリミティブ形状をセット
	static const D3D11_PRIMITIVE_TOPOLOGY pt[] = {
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,	// 0なら三角形ストリップ
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
	};
	pDeviceContext->IASetPrimitiveTopology(pt[m_primitiveType]);

	// ポリゴンの描画
	pDeviceContext->DrawIndexed(m_nNumIndex, 0, 0);
}

/**
 * @brief メッシュの頂点データの生成
 * @return なし
 */
HRESULT Mesh::MakeMeshVertex(VERTEX_3D vertexWk[], int indexWk[])
{
	ID3D11Device* pDevice = CGraphics::GetDevice();

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(VERTEX_3D) * m_nNumVertex;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertexWk;
	HRESULT hr = pDevice->CreateBuffer(&vbd, &initData, &m_pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	CD3D11_BUFFER_DESC ibd(m_nNumIndex * sizeof(int), D3D11_BIND_INDEX_BUFFER);
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = indexWk;
	hr = pDevice->CreateBuffer(&ibd, &initData, &m_pIndexBuffer);

	return hr;
}

/**
 * @brief 大きさの変更
 * @param[in] size 大きさ
 * @return インスタンス
 */
Mesh* Mesh::ChangeSize(XMFLOAT3 size)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->scale.x = size.x;
	m_transform->scale.y = size.y;
	m_transform->scale.z = size.z;

	return this;
}

/**
 * @brief 大きさの変更
 * @param[in] x x方向の大きさ
 * @param[in] y y方向の大きさ
 * @param[in] z z方向の大きさ
 * @return インスタンス
 */
Mesh * Mesh::ChangeSize(float x, float y, float z)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->scale.x = x;
	m_transform->scale.y = y;
	m_transform->scale.z = z;
	return this;
}

/**
 * @brief 座標の変更
 * @param[in]
 * @return インスタンス
 */
Mesh* Mesh::ChangePos(XMFLOAT3 pos)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->position.x = pos.x;
	m_transform->position.y = pos.y;
	m_transform->position.z = pos.z;

	return this;
}

/**
 * @brief 座標の変更
 * @param[in]
 * @return インスタンス
 */
Mesh* Mesh::ChangePos(float x, float y, float z)
{
	if (m_transform == nullptr) {
		return this;
	}

	m_transform->position.x = x;
	m_transform->position.y = y;
	m_transform->position.z = z;

	return this;
}

/**
 * @brief シェーダーの設定
 * @param[in]
 * @return なし
 */
void Mesh::SetShader(ShaderInfo& shader)
{
	m_shader = &shader;
}

// EOF