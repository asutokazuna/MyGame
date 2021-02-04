/**
 * @file TowerCtrl
 * @brief TowerCtrlクラス
 */
#pragma once
#include "Component.h"

// 前方宣言
struct TFbxMaterial;
class LifeGauge;
class ShaderInfo;
class TowerEnergy;

/**
 * @class TowerCtrl
 * @brief タワーのパラメーター管理クラス
 */
class TowerCtrl: public Component
{
private:
	TFbxMaterial* material;
	float m_percent;
	GameObject* m_gauge;
	ShaderInfo* m_shader;
	TowerEnergy* m_energy;
	int m_state;

public:
	enum TOWERSTATE
	{
		NONE,
		PLAYER,
		ENEMY,
		MAX,
	};

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	void Uninit();

	void Update();

	void Draw();

	int GetState();

	void ChangeColor();

};

// EOF