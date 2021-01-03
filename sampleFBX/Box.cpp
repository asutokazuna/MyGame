/**
 * @file Box.cpp
 * @brief 境界ボックスデバッグ表示
 */
#include "Box.h"
#include "Shader.h"
#include "CCamera.h"
#include "FbxModel.h"
#include "Graphics.h"
#include "Light.h"

static CFbxLight	mg_light;		// 光源
// 頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT3 nor;		// 法線ベクトル
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_3D;
// 構造体定義
//----- 頂点座標
struct VERTEX {
	XMFLOAT3	position;
	XMFLOAT3	normal;
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
};
//----- シェーダに渡す値
struct SHADER_GLOBAL {
	XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
	XMMATRIX	mW;			// ワールド行列(転置行列)
	XMMATRIX	mTex;		// テクスチャ行列(転置行列)
};
struct SHADER_GLOBAL2 {
	XMVECTOR	vEye;		// 視点座標
	// 光源
	XMVECTOR	vLightDir;	// 光源方向
	XMVECTOR	vLa;		// 光源色(アンビエント)
	XMVECTOR	vLd;		// 光源色(ディフューズ)
	XMVECTOR	vLs;		// 光源色(スペキュラ)
	// マテリアル
	XMVECTOR	vAmbient;	// アンビエント色
	XMVECTOR	vDiffuse;	// ディフューズ色
	XMVECTOR	vSpecular;	// スペキュラ色(+スペキュラ強度)
	XMVECTOR	vEmissive;	// エミッシブ色
};

ID3D11Buffer* CBox::m_pConstantBuffer[2];		// 定数バッファ
ID3D11VertexShader* CBox::m_pVertexShader;		// 頂点シェーダ
ID3D11InputLayout* CBox::m_pInputLayout;		// 頂点フォーマット
ID3D11PixelShader* CBox::m_pPixelShader;		// ピクセルシェーダ
ID3D11Buffer*	CBox::m_pIndexBuffer;
int CBox::m_nRef = 0;	//!< 参照カウンタ

/**
 * @brief コンストラクタ
 */
CBox::CBox() :m_pVertexBuffer(nullptr), m_color(1.0f, 1.0f, 1.0f, 0.5f)
{
	XMStoreFloat4x4(&m_world, XMMatrixIdentity());
}

/**
 * @breif デストラクタ
 */
CBox::~CBox()
{
	SAFE_RELEASE(m_pVertexBuffer);
}

/**
 * @brief 初期化
 * @return 初期化成功でS_OK
 */
HRESULT CBox::Init(XMFLOAT3* pHalfSize)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = CGraphics::GetDevice();

	if (m_nRef == 0) {

		// シェーダ初期化
		static const D3D11_INPUT_ELEMENT_DESC layout[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		hr = LoadShader("Vertex", "Pixel",
			&m_pVertexShader, &m_pInputLayout, &m_pPixelShader, layout, _countof(layout));
		if (FAILED(hr)) {
			return hr;
		}

		// 定数バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SHADER_GLOBAL);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		hr = pDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer[0]);
		if (FAILED(hr)) return hr;
		bd.ByteWidth = sizeof(SHADER_GLOBAL2);
		hr = pDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer[1]);
		if (FAILED(hr)) return hr;

		int index[36] = { 0,1,2,2,1,3,
						  4,5,6,6,5,7,
						  8,9,10,10,9,11,
						  12,13,14,14,13,15,
						  16,17,18,18,17,19,
						  20,21,22,22,21,23,
		};

		CD3D11_BUFFER_DESC ibd(sizeof(index), D3D11_BIND_INDEX_BUFFER);
		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(initData));
		initData.pSysMem = index;
		hr = pDevice->CreateBuffer(&ibd, &initData, &m_pIndexBuffer);
		if (FAILED(hr)) return hr;
	}
	++m_nRef;
	// 頂点バッファ作成
	static XMFLOAT3 pos[24] = {
		{-1,1,-1},{1,1,-1},{-1,-1,-1},{1,-1,-1},
		{1, 1, -1},{1,1,1},{1,-1,-1},{1,-1,1},
		{1,1,1},{-1,1,1},{1,-1,1},{-1,-1,1},
		{-1,1,1},{-1,1,-1},{-1,-1,1},{-1,-1,-1},
		{-1,1,1},{1,1,1},{-1,1,-1},{1,1,-1},
		{-1,-1,-1},{1,-1,-1},{-1,-1,1},{1,-1,1},
	};
	static XMFLOAT3 dir[6] = {
		{0,0,-1},
		{1,0,0},
		{0,0,1},
		{-1,0,0},
		{0,1,0},
		{0,-1,0},
	};
	VERTEX vertex[24];
	// 前面
	for (int i = 0; i < 24; ++i) {
		vertex[i].position.x = pHalfSize->x * pos[i].x;
		vertex[i].position.y = pHalfSize->y * pos[i].y;
		vertex[i].position.z = pHalfSize->z * pos[i].z;
		vertex[i].normal = dir[i / 4];
		vertex[i].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i].tex = XMFLOAT2(0.0f, 0.0f);
	}
	// 頂点バッファ生成
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(vertex);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertex;
	hr = pDevice->CreateBuffer(&vbd, &initData, &m_pVertexBuffer);
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

/**
 * @brief 終了
 * @return なし
 */
void CBox::Uninit()
{
	// 頂点バッファ解放
	SAFE_RELEASE(m_pVertexBuffer);
	// 参照カウンタ減算
	--m_nRef;
	if (m_nRef == 0) {
		// インデックスバッファ解放
		SAFE_RELEASE(m_pIndexBuffer);
		// 定数バッファの解放
		for (int i = 0; i < _countof(m_pConstantBuffer); ++i) {
			SAFE_RELEASE(m_pConstantBuffer[i]);
		}
		// ピクセルシェーダ解放
		SAFE_RELEASE(m_pPixelShader);
		// 頂点フォーマット解放
		SAFE_RELEASE(m_pInputLayout);
		// 頂点シェーダ解放
		SAFE_RELEASE(m_pVertexShader);
	}
}

/**
 * @brief 更新
 * @return なし
 */
void CBox::Update()
{

}

/**
 * @brief 描画
 * @return なし
 */
void CBox::Draw()
{
	CGraphics::SetCullMode(CULLMODE_CCW);	
	CGraphics::SetZWrite(false);
	CGraphics::SetBlendState(BS_ALPHABLEND);	// 半透明描画
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	// シェーダ設定
	pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
	pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
	pDeviceContext->IASetInputLayout(m_pInputLayout);

	// プリミティブ形状をセット
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	// インデックスバッファをセット
	pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	// 定数バッファ設定
	SHADER_GLOBAL cb;
	XMMATRIX mtxWorld = XMLoadFloat4x4(&m_world);
	XMMATRIX mtxTexWorld = XMMatrixIdentity();;
	cb.mWVP = XMMatrixTranspose(mtxWorld *
		XMLoadFloat4x4(&CCamera::Get()->GetView()) * XMLoadFloat4x4(&CCamera::Get()->GetProj()));
	cb.mW = XMMatrixTranspose(mtxWorld);
	cb.mTex = XMMatrixTranspose(mtxTexWorld);
	// 頂点シェーダ
	pDeviceContext->UpdateSubresource(m_pConstantBuffer[0], 0, nullptr, &cb, 0, 0);
	pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer[0]);
	SHADER_GLOBAL2 cb2;
	XMFLOAT3 eye = CCamera::Get()->GetEye();
	cb2.vEye = XMLoadFloat3(&eye);
	CFbxLight& light = *Light::Get();
	cb2.vLightDir = XMVectorSet(light.m_direction.x, light.m_direction.y, light.m_direction.z, 0.f);
	cb2.vLa = XMLoadFloat4(&light.m_ambient);
	cb2.vLd = XMLoadFloat4(&light.m_diffuse);
	cb2.vLs = XMLoadFloat4(&light.m_specular);
	cb2.vDiffuse = XMLoadFloat4(&m_color);
	cb2.vAmbient = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	cb2.vSpecular = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	cb2.vEmissive = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);		
	pDeviceContext->UpdateSubresource(m_pConstantBuffer[1], 0, nullptr, &cb2, 0, 0);
	pDeviceContext->PSSetConstantBuffers(1, 1, &m_pConstantBuffer[1]);
	// ポリゴンの描画
	pDeviceContext->DrawIndexed(36, 0, 0);
}

// EOF