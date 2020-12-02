/**
 * @file TitleRogo
 * @brief タイトルロゴ
 */
#include "TitleRogo.h"
#include "UIMesh.h"
#include "TextureData.h"

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleRogo::Awake()
{
	AddComponent<UIMesh>()->ChangeSize(700, 400, 1)->ChangePos(0, 100, 0)->SetTexture(TextureData::GetData(TEXTURE_TITLE_ROGO));
}

// EOF