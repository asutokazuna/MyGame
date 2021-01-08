/**
 * @file Collision
 * @brief 当たり判定クラス
 */
#pragma once
#include "Component.h"
#include <unordered_map>
#include "MyMath.h"
#include "Box.h"
#include "LinerOctreeManager.h"

/**
 * 当たり判定用オブジェクト識別タグ
 */
enum GameObjectTag
{
	OBJ_TAG_NONE,
	OBJ_TAG_PLAYER,
	OBJ_TAG_PLAYERMISSILE,
	OBJ_TAG_ENEMY,
	OBJ_TAG_ENEMYMISSILE,
	OBJ_TAG_TOWER,
	OBJ_TAG_CORE_PLAYER,
	OBJ_TAG_CORE_ENEMY,
	OBJ_TAG_FIELD,

	OBJ_TAG_MAX
};

// 前方宣言
class Transform;

/**
 * @class Collision
 * @brief コライダー
 */
class Collision :public Component
{
#ifdef _DEBUG
	CBox m_box;	//!< 当たり判定のサイズデバッグ用
#endif

protected:
	Transform* m_transform;	//!< 親のトランスフォーム
	Vector3 m_offsetPos;		//!< 親からのオフセット
	Vector3 m_offsetSize;		//!< モデルの半分の大きさ
	int id;			//!< ユニークID
	int m_tag;		//!< 識別タグ

public:
	/**
	 * @breif コンストラクタ
	 */
	Collision();

	/**
	 * @brief デストラクタ
	 */
	virtual ~Collision();

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
	 * @breif モデルの種類設定
	 * @param[in] kind モデルの種類
	 * @return 実体
	 */
	Collision* SetModelKind(int);

	/**
	 * @breif タグの取得
	 * @return タグの数値
	 */
	int GetTag();

	Vector3 GetoffsetSize() {
		return m_offsetSize;
	}

	void SetID(int num) {
		id = num;
	}

	int GetID() {
		return id;
	}

public :

	/**
	 * @breif バウンディングボックスでの当たり判定の比較
	 * @return 当たっていればtrue
	 */
	static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);


	static Vector3 GetSize(const Transform& trans);
};

// EOF