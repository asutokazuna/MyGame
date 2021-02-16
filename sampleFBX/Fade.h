/**
 * @file Fade
 * @brief フェードクラス
 * @author Ariga
 */
#pragma once
#include "Singleton.h"

// 前方宣言
class GameObject;
class ShaderInfo;

/**
 * @class Fade
 * @brief フェード
 */
class Fade: public Singleton<Fade>
{
private:
	/**
	 * @enm FADE_STATE
	 * @brief フェードの状態
	 */
	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};
private:
	GameObject* m_Mesh;	//!< フェード用メッシュ
	ShaderInfo* m_shader;	//!< シェーダー
	bool m_isFade;		//!< フェード中かどうか
	float m_Alpha;		//!< フェードのα
	int m_State;		//!< 今の状態

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