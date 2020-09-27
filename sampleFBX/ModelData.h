/**
 * @file ModelData
 * @brief ���f���f�[�^
 */
#pragma once
#include <Windows.h>
#include "FbxModel.h"
#include <memory>
#include "Data.h"
#include "Singleton.h"

enum ModelKind
{
	MODEL_SKY,
	MODEL_PLAYER,
	MODEL_ENEMY,
	MODEL_MISSILE,
	MODEL_TOWER,
	MODEL_CORE,
	MODEL_MAX
};

/**
 * @class ModelData
 * @brief ���f���f�[�^
 */
class ModelData:public Singleton<ModelData>
{
public:
	friend class Singleton<ModelData>;

private:
	Data<CFbxModel> m_data;

private:
	CFbxLight	m_light;	//!< �������

public:

	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	void Initinstance();
	void UninitInstance();

	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	static void Init();
	static void Uninit();

	/**
	 * @brief ���f���f�[�^�̎擾
	 * @param[in] kind �擾�������e�N�X�`����ID
	 * @return �����ɍ��킹�����f���f�[�^
	 */
	static CFbxModel* GetData(ModelKind kind);
};

// EOF