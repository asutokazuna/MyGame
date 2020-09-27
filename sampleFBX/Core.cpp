/**
 * @file Core.h
 * @brief �Q�[���̏��s�����߂�j�I�u�W�F�N�g�N���X
 */
#include "Core.h"
#include "Object3D.h"
#include "CoreCollision.h"
#include "collision.h"
#include "CoreState.h"
#include "SceneGame.h"

HRESULT Core::Init()
{
	AddComponent<Object3D>()->SetModel(MODEL_CORE);
	m_Collision = AddComponent<CoreCollision>();
	m_State = AddComponent<CoreState>();

	return E_NOTIMPL;
}
//
//void Core::Update()
//{
//	GameObject::Update();
//	if (m_State->GetLife() <= 0) {
//		SceneGame::GameOver();
//	}
//}

int Core::GetLife()
{
	return m_State->GetLife();
}



// EOF