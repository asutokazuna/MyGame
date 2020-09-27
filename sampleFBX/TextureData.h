/**
 * @file TextureData.cpp
 * @brief �e�N�X�`���f�[�^�Ǘ��N���X
 */
#pragma once
#include "Singleton.h"
#include "Data.h"

// �O���錾
struct ID3D11ShaderResourceView;

/**
 * @enum TEXTURE_KIND
 * @brief �e�N�X�`���̎��ʔԍ�
 */
enum TEXTURE_KIND 
{
	TEXTURE_FIELD,

	TEXTURE_MAX
};

/**
 * @class TextureData
 * @brief �e�N�X�`���f�[�^�Ǘ��N���X
 */
class TextureData :public Singleton<TextureData>
{
public:
	friend class Singleton<TextureData>;	//!< �V���O���g��

private:
	Data<ID3D11ShaderResourceView> m_data;	//!< �f�[�^

public:
	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	void InitInstance();

	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	static void Init();

	/**
	 * @brief �e�N�X�`���f�[�^�̎擾
	 * @param[in] kind �擾�������e�N�X�`����ID
	 * @return �����ɍ��킹���e�N�X�`���f�[�^
	 */
	static ID3D11ShaderResourceView* GetData(int kind);
};

// EOF