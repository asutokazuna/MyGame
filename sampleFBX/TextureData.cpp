#include "TextureData.h"
#include "Texture.h"
#include "Graphics.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

struct TEXTURE_TABLE
{
	const wchar_t* fileName;
	int kind;
};

static TEXTURE_TABLE m_table[TEXTURE_MAX] = {
	{TEXTURE_FILENAME, TEXTURE_FIELD},
};

void TextureData::InitInstance()
{
	ID3D11Device* pDevice = CGraphics::GetDevice();
	ID3D11ShaderResourceView* worktexture;

	for (int i = 0; i < sizeof(m_table); i++)
	{
		CreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			m_table[i].fileName,		// �t�@�C���̖��O
			&worktexture);	// �ǂݍ��ރ������[

		m_data.Set(m_table[i].kind, worktexture);
	}
}

void TextureData::Init()
{
	TextureData::GetInstance().InitInstance();
}

ID3D11ShaderResourceView* TextureData::GetData(int kind)
{
	return TextureData::GetInstance().m_data.Get(kind);
}

// EOF