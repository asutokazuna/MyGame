/**
 * @file Fade
 * @brief フェードクラス
 */
#pragma once
#include "Singleton.h"

// 前方宣言
class GameObject;

/**
 * @class Fade
 * @brief フェード
 */
class Fade: public Singleton<Fade>
{
private:
	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT

	};
private:
	GameObject* m_Mesh;
	bool m_isFade;
	float m_Alpha;
	int m_State;

private:
	/**
	 * @brief 初期化
	 * @return なし
	 */
	void InitInst();

	/**
	 * @brief 終了
	 * @return なし
	 */
	void UninitInst();

	/**
	 * @brief 更新
	 * @return なし
	 */
	void UpdateInst();

	/**
	 * @brief 描画
	 * @return なし
	 */
	void DrawInst();

	/**
	 * @brief フェード中か判定する
	 * @return フェード中ならtrue
	 */
	bool IsFadeInst();

	/**
	 * @brief フェード処理
	 * @return なし
	 */
	void SetState(FADE_STATE state);

public:

	/**
	 * @brief 初期化
	 * @return なし
	 */
	static void Init();

	/**
	 * @brief 終了
	 * @return なし
	 */
	static void Uninit();

	/**
	 * @brief 更新
	 * @return なし
	 */
	static void Update();

	/**
	 * @brief 描画
	 * @return なし
	 */
	static void Draw();

	/**
	 * @brief フェード中か判定する
	 * @return フェード中ならtrue
	 */
	static bool IsFade();

	/**
	 * @brief フェードイン
	 * @return なし
	 */
	static void FadeIn();

	/**
	 * @brief フェードアウト
	 * @return なし
	 */
	static void FadeOut();
};

// EOF