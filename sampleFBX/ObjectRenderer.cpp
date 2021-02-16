﻿/**
 * @file ObjectRenderer
 * @brief オブジェクトの描画管理クラス
 */
#include "ObjectRenderer.h"
#include "ObjectManager.h"
#include "Graphics.h"
#include "ShaderData.h"
#include "Object3D.h"
#include "ShaderInfo.h"
#include "Light.h"
#include "FbxModel.h"
#include "ShadowCamera.h"
#include "UIMesh.h"

static ShadowCamera* g_shadowCamera;

struct LightPos
{
	DirectX::XMFLOAT4 pos;
};

/**
 * @brief 初期化処理
 * @return なし
 */
void ObjectRenderer::Init()
{
	CBufferManager::GetInstance().Create("LightPos", sizeof(DirectX::XMFLOAT4X4));
	g_shadowCamera = ObjectManager::Create<ShadowCamera>("ShadowCamera");
}
static int cnt = 0;

/**
 * @brief 描画用オブジェクトリスト作成する再帰関数
 * @param[in] 描画リスト作成するヒエラルキーのデータ
 * @return なし
 */
void ObjectRenderer::CreteData(std::vector<ObjectManager::HierarchyData>& data)
{
	for (auto& obj : data)
	{
		if (obj.gameObject->GetComponent<UIMesh>() != nullptr) {
			m_2dObjVector.push_back(obj.gameObject);
		}
		else {
			m_3dObjVector.push_back(obj.gameObject);
		}
		CreteData(obj.m_childList);
		cnt++;
	}
}

/**
 * @brief 描画オブジェクトリスト作成
 * @return なし
 */
void ObjectRenderer::CreateDrawBuffer()
{
	std::vector<ObjectManager::HierarchyData>& hierarcy = ObjectManager::GetInstance().GetHierarchy();
	int temp = ObjectManager::GetInstance().GetHierarchyCnt();
	
	// ヒエラルキーの数が変わっているか判定
	if (cnt != temp) {
		m_2dObjVector.clear();
		m_3dObjVector.clear();
		cnt = 0;
		CreteData(hierarcy);
	}
}

/**
 * @brief 深度バッファシャドウの描画
 * @return なし
 */
void ObjectRenderer::DrawShadow()
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	/*ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(-1);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX3D);
*/

	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(-1);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX3D);
	UINT viewW = SCREEN_WIDTH;
	UINT viewH = SCREEN_HEIGHT;
	float viewD = 10.0f;

	// 光源から見える景色を表示するためのカメラを作成
	CCamera::Set(g_shadowCamera);

	auto& buff = ObjectManager::GetInstance().GetObjList();
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		GameObject* gameObj;
		gameObj = dynamic_cast<GameObject*>(obj.second.get());
		if (gameObj->GetComponent<Object3D>() != nullptr || 
			obj.first == "TowerManager")
		{
			pDeviceContext->VSSetShader(vs, nullptr, 0);
			pDeviceContext->PSSetShader(ps, nullptr, 0);
			// 頂点インプットレイアウトをセット
			pDeviceContext->IASetInputLayout(il);
			obj.second.get()->Draw();
		}
	}
	CCamera::SetPreCamera();
}

/**
 * @brief 描画処理
 * @return なし
 */
void ObjectRenderer::Draw()
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(ShaderData::PS_KIND::PS_PIXEL3D);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX3D);

	DirectX::XMMATRIX vView = DirectX::XMLoadFloat4x4(&g_shadowCamera->GetView());
	DirectX::XMMATRIX vProj = DirectX::XMLoadFloat4x4((&g_shadowCamera->GetProj()));
	DirectX::XMMATRIX vScreen = DirectX::XMMatrixScaling(0.5f, -0.5f, 1.0f) * DirectX::XMMatrixTranslation(0.5f, 0.5f, 0.0f);

	XMMATRIX 
	m_lightView = DirectX::XMMatrixTranspose(vView * vProj);

	XMFLOAT4X4 view4;

	XMStoreFloat4x4(&view4, m_lightView);

	CBufferManager::GetInstance().SetData("LightPos", &view4);
	ID3D11Buffer* buf = CBufferManager::GetInstance().GetCBuffer("LightPos");
	pDeviceContext->VSSetConstantBuffers(3,1, &buf);
	pDeviceContext->VSSetShader(vs, nullptr, 0);
	pDeviceContext->PSSetShader(ps, nullptr, 0);
	// 頂点インプットレイアウトをセット
	pDeviceContext->IASetInputLayout(il);

	// 3D描画
	for (auto obj : m_3dObjVector)
	{
		obj->Draw();
	}

	// 2D描画
	for (auto obj : m_2dObjVector)
	{
		obj->Draw();
	}
}

// EOF