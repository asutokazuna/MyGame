/**
 * @file Core.h
 * @brief ゲームの勝敗を決める核オブジェクトクラス
 */
#include "Core.h"
#include "Object3D.h"
#include "CoreCollision.h"
#include "collision.h"
#include "CoreState.h"

 /**
  * @brief 初期化処理
  * @return なし
  */
void Core::Awake()
{
	AddComponent<Object3D>()->SetModel(MODEL_CORE);
	m_Collision = AddComponent<CoreCollision>();
	m_State = AddComponent<CoreState>();
}

/**
 * @brief 現在HPの取得
 * @return 現在のHP
 */
int Core::GetLife()
{
	return m_State->GetLife();
}



// EOF