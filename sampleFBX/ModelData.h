/**
 * @file ModelData
 * @brief モデルデータ
 */
#pragma once
#include <Windows.h>
#include "FbxModel.h"
#include <memory>
#include "Data.h"
#include "Singleton.h"
#include "MyMath.h"

/**
 * @enum モデルの種類
 */
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
 * @brief モデルデータ
 */
class ModelData:public Singleton<ModelData>
{
public:
	friend class Singleton<ModelData>;

private:
	Data<CFbxModel> m_data;

private:
	CFbxLight	m_light;	//!< 光源情報

public:

	/**
	 * @brief 初期化
	 * @return なし
	 */
	void Initinstance();
	void UninitInstance();

	/**
	 * @brief 初期化
	 * @return なし
	 */
	static void Init();
	static void Uninit();

	/**
	 * @brief モデルデータの取得
	 * @param[in] kind 取得したいテクスチャのID
	 * @return 引数に合わせたモデルデータ
	 */
	static CFbxModel* GetData(ModelKind kind);

	/**
	 * @brief モデルの大きさの取得
	 * @param[in] kind モデルの種類
	 * @return モデルサイズ
	 */
	static Vector3 GetSize(int kind);
};

// EOF