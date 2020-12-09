/**
 * @file TextureData.cpp
 * @brief テクスチャデータ管理クラス
 */
#pragma once
#include "Singleton.h"
#include "Data.h"

// 前方宣言
struct ID3D11ShaderResourceView;

/**
 * @enum TEXTURE_KIND
 * @brief テクスチャの識別番号
 */
enum TEXTURE_KIND 
{
	TEXTURE_FIELD,
	TEXTURE_PRESSENTER,
	TEXTURE_TITLE_ROGO,
	TEXTURE_ROGO,
	TEXTURE_WIN,
	TEXTURE_LOSE,
	TEXTURE_STAR,
	TEXTURE_EFFECT,
	
	TEXTURE_MAX
};

/**
 * @class TextureData
 * @brief テクスチャデータ管理クラス
 */
class TextureData :public Singleton<TextureData>
{
public:
	friend class Singleton<TextureData>;	//!< シングルトン

private:
	DXData<ID3D11ShaderResourceView> m_data;	//!< データ

public:
	/**
	 * @brief 初期化
	 * @return なし
	 */
	void InitInstance();

	/**
	 * @brief 初期化
	 * @return なし
	 */
	static void Init();

	/**
	 * @brief テクスチャデータの取得
	 * @param[in] kind 取得したいテクスチャのID
	 * @return 引数に合わせたテクスチャデータ
	 */
	static ID3D11ShaderResourceView* GetData(int kind);
};

// EOF