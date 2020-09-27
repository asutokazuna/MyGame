/**
 * @file Collision
 * @brief 当たり判定クラス
 */
#pragma once
#include "Component.h"
#include <unordered_map>
#include "MyMath.h"
#include "Box.h"

/**
 * @class Collision
 * @brief コライダー
 */
class Collision :public Component
{
private:
	static std::unordered_map<int, Collision*> m_List;	//!< コライダーリスト

#ifdef _DEBUG
	CBox m_box;	//!< 当たり判定のサイズデバッグ用
#endif

protected:
	Vector3 pos;	//!< 座標
	Vector3 size;	//!< 大きさ
	int id;			//!< ユニークID
	int m_tag;		//!< 識別タグ

public:
	enum COL_TAG
	{
		COL_PLAYER,
		COL_ENEMY,
		COL_MISSILE,
		COL_MISSILE_ENEMY,
		COL_TOWER,
		COL_CORE_PLAYER,
		COL_CORE_ENEMY,
		COL_MAX
	};

public:
	/**
	 * @breif コンストラクタ
	 */
	Collision();

	/**
	 * @brief デストラクタ
	 */
	~Collision();

	/**
	 * @breif 初期化処理
	 * @return なし
	 */
	HRESULT Init();

	/**
	 * @breif 終了
	 * @return なし
	 */
	virtual void Uninit();

	/**
	 * @breif 更新
	 * @return なし
	 */
	virtual void Update();

	/**
	 * @breif 描画
	 * @return なし
	 */
	virtual void Draw();

	/**
	 * @breif 描画
	 * @return なし
	 */
	virtual void DrawAlpha();

	/**
	 * @breif タグの設定
	 * @return なし
	 */
	virtual void SetTag(int tag);
	
	/**
	 * @breif 座標の設定
	 * @return 実体
	 */
	Collision* SetPos(Vector3);

	/**
	 * @breif 大きさの設定
	 * @return 実体
	 */
	Collision* SetSize(Vector3);

	/**
	 * @breif タグの取得
	 * @return タグの数値
	 */
	int GetTag();

public :
	/**
	 * @breif リストにある全てのオブジェクトが当たっているか判定する
	 * @return なし
	 */
	static void Check();

	/**
	 * @breif バウンディングボックスでの当たり判定の比較
	 * @return 当たっていればtrue
	 */
	static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);

	/**
	 * @breif 当たり判定のリストの初期化
	 * @return なし
	 */
	static void Clear();
};

// EOF