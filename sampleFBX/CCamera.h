/**
 * @file CCamera.h
 * @brief カメラクラス
 */
#pragma once
#include "main.h"
#include "Transform.h"
#include "GameObject.h"

/**
 * @class CCamera
 * @brief カメラ
 */
class CCamera:public GameObject
{
protected:
	XMFLOAT3	m_vEye;		//!< 視点座標
	XMFLOAT3	m_vLook;	//!< 注視点座標
	XMFLOAT3	m_vUp;		//!< 上方ベクトル
	XMFLOAT4X4	m_View;		//!< ビュー変換
	XMFLOAT4X4	m_Proj;		//!< 射影変換
	float		m_fFOVY;	//!< 視野角
	float		m_fAspect;	//!< アスペクト比
	float		m_fNearZ;	//!< 前方クリップ距離
	float		m_fFarZ;	//!< 後方クリップ距離
	static XMFLOAT3 m_vNowEye;	//!< 現在の視点
	static XMFLOAT3 m_vNowLook;	//!< 現在の注視点
	static XMFLOAT3 m_vNowUp;	//!< 現在の上方ベクトル
	Transform *m_transform;

private:
	static CCamera* m_pCamera;	//!< 現在有効なカメラ

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

	virtual void SetPos(XMFLOAT3 eye);
	void SetTransform(Transform& trans);

	XMFLOAT4X4& GetView();
	XMFLOAT4X4& GetProj();
	XMFLOAT3& GetEye();
	XMFLOAT3& GetLook();
	void SetLook(XMFLOAT3 vLook);
	static void Set(CCamera* pCamera);
	static CCamera* Get();
};

// EOF