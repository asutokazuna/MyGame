/**
 * @class CameraInfo 
 * @brief カメラの制御コンポーネント
 */
#pragma once
#include "Component.h"
#include "MyMath.h"

/**
 * @class CameraInfo 
 * @brief カメラの制御
 */
class CameraInfo :public Component
{
protected:
	Vector3	m_vLook;	//!< 注視点座標
	Vector3	m_vUp;	//!< 注視点座標
	XMFLOAT4X4	m_View;		//!< ビュー変換
	XMFLOAT4X4	m_Proj;		//!< 射影変換
	float		m_fFOVY;	//!< 視野角
	float		m_fAspect;	//!< アスペクト比
	float		m_fNearZ;	//!< 前方クリップ距離
	float		m_fFarZ;	//!< 後方クリップ距離

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

	void SetTarget(Transform& trans);

	XMFLOAT4X4& GetView();
	XMFLOAT4X4& GetProj();
	XMFLOAT3 GetEye();
};

// EOF