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

/**
 * @brief 更新処理
 * @return なし
 */
void Missile::Update()
{
	if (m_Move->m_nLife <= 0) {

		m_isActive = false;
		//return;
	}
	GameObject::Update();
}

// Offsetがモデル座標でのミサイルの位置らしいよ
bool Missile::Fire(Vector3* pos)
{
	m_isActive = true;
	transform->position = *pos;
	//m_col->SetPos(*pos);
	m_Move->m_nLife = 3 * 60;		// 5秒
	m_Move->m_nStat = 1;			// 追尾中
	return true;
}

bool Missile::Fire(Vector3 * pos, Quaternion quat)
{
	m_isActive = true;
	transform->position = *pos;
	transform->quaternion = quat;
	//m_col->SetPos(*pos);
	m_Move->m_nLife = 3 * 60;		// 5秒
	m_Move->m_nStat = 1;			// 追尾中
	return true;
}

// EOF