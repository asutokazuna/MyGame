/**
 * @file CCamera.h
 * @brief カメラクラス
 */
#pragma once
#include "main.h"
#include "Transform.h"
#include "GameObject.h"
#include "MyMath.h"

/**
 * @class CCamera
 * @brief カメラ
 */
class CCamera:public GameObject
{
protected:
	Vector3	m_vLook;	//!< 注視点座標
	Vector3	m_vUp;	//!< 注視点座標
	XMFLOAT4X4	m_View;		//!< ビュー変換
	XMFLOAT4X4	m_Proj;		//!< 射影変換
	float		m_fFOVY;	//!< 視野角
	float		m_fAspect;	//!< アスペクト比
	float		m_width;
	float		m_height;
	float		m_fNearZ;	//!< 前方クリップ距離
	float		m_fFarZ;	//!< 後方クリップ距離
	Transform* m_transform;	//!< ターゲット

private:
	static CCamera* m_pCamera;	//!< 現在有効なカメラ
	static CCamera* m_pPreCamera;	//!< 前に有効なカメラ

public:
	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Awake();

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	virtual void Uninit();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	virtual void Update();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	virtual void Draw();

	void UpdateMatrix();

	void UpdateMatrixOrthograph();

	virtual void SetPos(XMFLOAT3 eye);
	void SetTransform(Transform& trans);

	XMFLOAT4X4& GetView();
	XMFLOAT4X4& GetProj();
	XMFLOAT3 GetEye();
	//XMFLOAT3& GetLook();
	//void SetLook(XMFLOAT3 vLook);
	static void Set(CCamera* pCamera);
	static void SetPreCamera() {
		if (m_pCamera != NULL) {
			m_pCamera->m_isActive = false;
		}
		m_pCamera = m_pPreCamera;
		m_pCamera->m_isActive = true;
	}
	static CCamera* Get();
	Vector3 GetLook() {
		return m_vLook;
	}
};

// EOF