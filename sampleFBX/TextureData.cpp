/**
 * @file TextureData.cpp
 * @brief テクスチャデータ管理クラス
 */
#include "TextureData.h"
#include "Texture.h"
#include "Graphics.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// 読み込むテクスチャファイル名

/**
 * @brief テクスチャテーブル構造体
 */
struct TEXTURE_TABLE
{
	const wchar_t* fileName;
	int kind;
};

/**
 * @brief テクスチャのテーブル
 */
static TEXTURE_TABLE m_table[TEXTURE_MAX] = {
	{TEXTURE_FILENAME, TEXTURE_FIELD},
};

/**
 * @brief 初期化
 * @return なし
 */
void TextureData::InitInstance()
{
	ID3D11Device* pDevice = CGraphics::GetDevice();
	ID3D11ShaderResourceView* worktexture;

	for (int i = 0; i < sizeof(m_table); i++)
	{
		CreateTextureFromFile(pDevice,					// デバイスへのポインタ
			m_table[i].fileName,		// ファイルの名前
			&worktexture);	// 読み込むメモリー

		m_data.Set(m_table[i].kind, worktexture);
	}
}

/**
 * @brief 初期化
 * @return なし
 */
void TextureData::Init()
{
	TextureData::GetInstance().InitInstance();
}

/**
 * @brief テクスチャデータの取得
 * @param[in] kind 取得したいテクスチャのID
 * @return 引数に合わせたテクスチャデータ
 */
ID3D11ShaderResourceView* TextureData::GetData(int kind)
{
	return TextureData::GetInstance().m_data.Get(kind);
}

// EOF