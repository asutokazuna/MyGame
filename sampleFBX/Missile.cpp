/**
 * @file Missile
 * @brief ミサイルクラス
 * @date 2020/06/19
 */
#include "Missile.h"
#include "ModelData.h"
#include "Object3D.h"
#include "collision.h"
#include "MissileMove.h"
#include "MissileCtrl.h"

 /**
  * @brief コンストラクタ
  */
Missile::Missile() 
{
	m_col = nullptr;
}

/**
 * @brief 初期化処理
 * @return なし
 */
void Missile::Awake()
{
	HRESULT hr = S_OK;
	tag = parent->GetTag();
	AddComponent<Object3D>()->SetModel(MODEL_MISSILE);
	m_Move = AddComponent<MissileMove>();
	m_col = AddComponent<Collision>()->SetModelKind(MODEL_MISSILE);
	AddComponent<MissileCtrl>();
	m_isActive = false;
}

// EOF