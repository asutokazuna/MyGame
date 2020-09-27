/**
 * @file TextureData.cpp
 * @brief �e�N�X�`���f�[�^�Ǘ��N���X
 */
#include "TextureData.h"
#include "Texture.h"
#include "Graphics.h"

#define	TEXTURE_FILENAME	L"data/texture/field000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

/**
 * @brief �e�N�X�`���e�[�u���\����
 */
struct TEXTURE_TABLE
{
	const wchar_t* fileName;
	int kind;
};

/**
 * @brief �e�N�X�`���̃e�[�u��
 */
static TEXTURE_TABLE m_table[TEXTURE_MAX] = {
	{TEXTURE_FILENAME, TEXTURE_FIELD},
};

/**
 * @brief ������
 * @return �Ȃ�
 */
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

/**
 * @brief ������
 * @return �Ȃ�
 */
void TextureData::Init()
{
	TextureData::GetInstance().InitInstance();
}

/**
 * @brief �e�N�X�`���f�[�^�̎擾
 * @param[in] kind �擾�������e�N�X�`����ID
 * @return �����ɍ��킹���e�N�X�`���f�[�^
 */
ID3D11ShaderResourceView* TextureData::GetData(int kind)
{
	return TextureData::GetInstance().m_data.Get(kind);
}

// EOF