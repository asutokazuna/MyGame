/**
 * @file Object3D.h
 * @brief 3Dオブジェクトの表示用
 */
#pragma once
#include "Component.h"
#include "main.h"
#include "FbxModel.h"
#include "Box.h"
#include "Transform.h"
#include "ModelData.h"

class Object3D:public Component
{
private:
	Transform*	m_Transform;	// 座標
	CFbxLight	m_light;	//!< 光源情報
	XMFLOAT4X4 m_world;		//!< ワールドマトリックス

	int m_ModelIndex;
	CFbxModel* m_Model;
	TFbxMaterial material;
public:
	/**
	 * @breif コンストラクタ
	 */
	Object3D();

	/**
	 * @breif 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @breif 終了
	 * @return なし
	 */
	void Uninit();

	/**
	 * @breif 更新
	 * @return なし
	 */
	void Update();

	/**
	 * @breif 描画
	 * @return なし
	 */
	void Draw();

	/**
	 * @breif 描画
	 * @return なし
	 */
	void DrawAlpha();

	/**
	 * @brief 表示するモデルの種類を設定
	 * @param	kind	表示するモデルの識別子
	 * @retrun 実体
	 */
	Object3D& SetModel(int kind);

	/**
	 * @brief 表示するモデルの種類を設定
	 * @param	kind	表示するモデルの識別子
	 * @retrun 実体
	 */
	Object3D& SetModel(ModelKind kind);

	/**
	 * @brief 表示するモデルの色を設定
	 * @param	mat	表示する色
	 * @retrun 実体
	 */
	void SetMaterial(TFbxMaterial& color);
};

// EOF