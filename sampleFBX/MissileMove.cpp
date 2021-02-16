/**
 * @file MissileMove
 * @brief ミサイルの動きクラス
 * @author Ariga
 */
#include "MissileMove.h"
#include "GameObject.h"

/**
 * @def
 */
#define SPEED			(5.0f)

/**
 * @brief 初期化処理
 * @return なし
 */
HRESULT MissileMove::Init()
{
	m_Speed = SPEED;

	return E_NOTIMPL;
}

/**
 * @brief 更新処理
 * @return なし
 */
void MissileMove::Update()
{
	m_ParentTransform->position += m_ParentTransform->GetForward() * m_Speed;
}

// EOF