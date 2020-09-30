/**
 * @file TitleUI
 * @brief タイトルのUIメッシュクラス
 */
#include "TitleUI.h"
#include "UIMesh.h"

#define	TEXTURE_PressSpace	L"data/texture/Press_Space.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_shooting	L"data/texture/shooting.png"	// 読み込むテクスチャファイル名

/**
 * @breif 初期化処理
 * @return なし
 */
void TitleUI::Awake()
{
	m_RogoMesh = new GameObject();
	SetChild(m_RogoMesh);
	m_StartMesh = new GameObject();
	SetChild(m_StartMesh);
	m_RogoMesh->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TEXTURE_shooting);
	m_StartMesh->AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0)->SetTexture(TEXTURE_PressSpace);
}

// EOF