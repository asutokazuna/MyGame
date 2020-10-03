/**
 * @file TowerEnergy
 * @brief TowerEnergyクラス
 */
#pragma once
#include "Component.h"

// def
#define ENERGY_MAX (40)

// 前方宣言
class GameObject;

/**
 * @class TowerEnergy
 * @brief タワーのパラメーター
 */
class TowerEnergy :public Component
{
private:
	int m_Energy;
	int id;

public:
	/**
	 * @brief コンストラクタ
	 */
	TowerEnergy();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	void Draw();

	/**
	 * @brief エネルギーの増加
	 * @param num 増加させる値
	 * @return なし
	 */
	void AddEnergy(int num);

	/**
	 * @brief エネルギーの取得
	 * @return 現在のエネルギー
	 */
	int& GetEnergy();

	/**
	 * @brief 当たり判定
	 * @param[in] 当たったオブジェクト
	 * @return なし
	 */
	void OnCollisionEnter(GameObject* othor);
};

// EOF