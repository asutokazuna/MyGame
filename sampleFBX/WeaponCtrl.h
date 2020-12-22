/**
 * @file WeaponCtrl
 * @brief 武器の制御クラス
 */
#pragma once
#include "Component.h"
#include "MyMath.h"
#include <list>

// 前方宣言
class Missile;
class Transform;

/**
 * @class WeaponCtrl
 * @brief 武器の制御
 */
class WeaponCtrl :public Component
{
private:
	std::list<Missile*> m_BulletList;	//!< ミサイルリスト
	Transform* m_ParentTrans;			//!< 親の座標
	int m_BulletCount;
	int m_DelayTime;

public:

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update();

	/**
	 * @brief 玉の発射
	 * @return なし
	 */
	void Shot();
	
	/**
	 * @brief 玉の発射
	 * @return なし
	 */
	void Shot(Quaternion quat);

	/**
	 * @brief 残弾数の取得
	 * @return 弾の残り数
	 */
	const int& GetBulletCnt() {
		return m_BulletCount;
	}

	/**
	 * @brief 玉の発射
	 * @return なし
	 */
	//void Shot(Transform* target);
};

// EOF