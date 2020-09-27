/**
 * @file SceneGame
 * @brief ゲームシーンクラス
 */
#pragma once
#include "Scene.h"

class CPlayer;
class Enemy;
class CTPCamera;
class CBulletTime;
class Field;
class TowerManager;
class CorePlayer;
class CoreEnemy;

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
	HRESULT Init();
	void Uninit();
	void Update();

	static void GameOver();
};

// EOF