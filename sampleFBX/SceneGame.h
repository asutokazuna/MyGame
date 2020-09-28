/**
 * @file SceneGame
 * @brief ゲームシーンクラス
 */
#pragma once
#include "Scene.h"

// 前方宣言
class CPlayer;
class Enemy;
class CTPCamera;
class CBulletTime;
class Field;
class TowerManager;
class CorePlayer;
class CoreEnemy;

/**
 * @class SceneGame
 * @brief ゲームシーン
 */
class SceneGame: public CScene
{
private:
	static bool m_isGameOver;
private:
	CPlayer*		m_pPlayer;
	Enemy*			m_pEnemy;
	CTPCamera*		m_pCTPCamera;
	CBulletTime*	m_BCamera;
	Field*			m_Field;
	TowerManager*	m_Tower;
	CorePlayer*		m_Core;
	CoreEnemy*		m_CoreEnemy;

public:
	static bool m_isVictory;


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

	/**
	 * @brief 更新処理
	 * @return  なし
	 */
	void Update();

	static void GameOver();
};

// EOF