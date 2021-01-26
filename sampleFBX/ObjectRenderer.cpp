/**
 * @file ObjectRenderer
 * @brief オブジェクトの描画管理クラス
 */
#include "ObjectRenderer.h"
#include "ObjectManager.h"
#include "Graphics.h"
#include "ShaderData.h"
#include "Object3D.h"

void ObjectRenderer::DrawShadow()
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(-1);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX3D);


	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		GameObject* gameObj;
		gameObj = dynamic_cast<GameObject*>(obj.second.get());
		if (gameObj->GetComponent<Object3D>() == nullptr)
		{
			continue;
		}
		pDeviceContext->VSSetShader(vs, nullptr, 0);
		pDeviceContext->PSSetShader(ps, nullptr, 0);
		// 頂点インプットレイアウトをセット
		pDeviceContext->IASetInputLayout(il);
		obj.second.get()->Draw();

	}

}

void ObjectRenderer::Draw()
{
	ID3D11DeviceContext* pDeviceContext = CGraphics::GetDeviceContext();
	ID3D11VertexShader* vs = ShaderData::GetVertexShader(ShaderData::VS_KIND::VS_VERTEX3D);
	ID3D11PixelShader*	ps = ShaderData::GetPixelShader(ShaderData::PS_KIND::PS_PIXEL3D);
	ID3D11InputLayout*	il = ShaderData::GetInputLayout(ShaderData::VS_KIND::VS_VERTEX3D);


	auto& buff = ObjectManager::GetInstance().m_ObjList;
	for (auto& obj : buff) {
		if (obj.second.get()->GetActive() == false) {
			continue;
		}
		GameObject* gameObj;
		gameObj = dynamic_cast<GameObject*>(obj.second.get());
		if (gameObj->GetComponent<Object3D>() != nullptr)
		{

			pDeviceContext->VSSetShader(vs, nullptr, 0);
			pDeviceContext->PSSetShader(ps, nullptr, 0);
			// 頂点インプットレイアウトをセット
			pDeviceContext->IASetInputLayout(il);
		}
		obj.second.get()->Draw();

	}

}

// EOF