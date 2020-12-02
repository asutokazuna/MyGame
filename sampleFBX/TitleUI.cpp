/**
 * @file TitleUI
 * @brief タイトルのUIメッシュクラス
 */
#include "TitleUI.h"
#include "UIMesh.h"
#include "TextureData.h"

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
	m_RogoMesh->AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0);// ->SetTexture(TextureData::GetData(TEXTURE_TITLE_ROGO));
	m_StartMesh->AddComponent<UIMesh>()->ChangeSize(180, 100, 1)->ChangePos(0, -200, 0);// ->SetTexture(TextureData::GetData(TEXTURE_PRESSENTER));
}

// EOF