/**
 * @file SceneManager
 * @brief シーンマネージャークラス
 */
#pragma once
#include "Singleton.h"
#include "Data.h"

struct ID3D11ShaderResourceView;

enum TEXTURE_KIND 
{
	TEXTURE_FIELD,

	TEXTURE_MAX
};

class TextureData :public Singleton<TextureData>
{
public:
	friend class Singleton<TextureData>;
private:
	Data<ID3D11ShaderResourceView> m_data;

public:
	void InitInstance();

	static void Init();

	static ID3D11ShaderResourceView* GetData(int kind);
};

// EOF