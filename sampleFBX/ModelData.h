/**
 * @file CPlayer
 * @brief プレイヤークラス
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

class ModelData:public Singleton<ModelData>
{
public:
	friend class Singleton<ModelData>;

private:
	Data<CFbxModel> m_data;

private:
	CFbxLight	m_light;	//!< 光源情報

public:
	void Initinstance();
	void UninitInstance();

	static void Init();
	static void Uninit();
	static CFbxModel* GetData(ModelKind kind);
};

// EOF