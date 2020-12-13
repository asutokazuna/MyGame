#pragma once
#include "ShaderInfo.h"

class ExplosionShaderInfo :public ShaderInfo
{
private:
	XMFLOAT4X4 m_View;		//!< ビュー行列
	XMFLOAT4X4 m_Proj;		//!< プロジェクション行列
	XMFLOAT4X4 m_world;		//!< ワールド行列
	XMFLOAT4X4 m_TexWorld;	//!< テクスチャ行列
	float m_power;			//!< 揺れる強さ(振幅)
	float m_fadethrosh;		//!< 消える速度
	float m_time;
	ID3D11ShaderResourceView* m_pTexture;	//!< テクスチャ
	ID3D11ShaderResourceView* m_pNoizeTexture;	//!< テクスチャ
public:
	ExplosionShaderInfo();
	~ExplosionShaderInfo();
		
	/**
	 * @brief 初期化
	 * @retrun なし
	 */
	void Awake();
		
	/**
	 * @brief 終了
	 * @retrun なし
	 */
	void Uninit();

	void Draw();
		
	/**
	 * @brief コンスタントバッファの更新
	 * @retrun なし
	 */
	void UpdateConstant();
		
	/**
	 * @brief テクスチャのセット
	 * @param[in] kind テクスチャの種類のenum番号
	 * @retrun なし
	 */
	void SetTexture(int kind);

	/**
	 * @brief テクスチャのセット
	 * @param[in] texture テクスチャデータ
	 * @retrun なし
	 */
	void SetTexture(ID3D11ShaderResourceView* texture);

	void SetNoizeTexture(int kind);
			
	/**
	 * @brief コンスタントバッファのデータをセット
	 * @param[in] key 変数の判別するキー
	 * @param[in] value セットする値
	 * @retrun なし
	 */
	void SetFloat(std::string key, float value);
				
	/**
	 * @brief コンスタントバッファのデータをセット
	 * @param[in] key 変数の判別するキー
	 * @param[in] value セットする値
	 * @retrun なし
	 */
	void SetFloat(std::string key, XMFLOAT4X4 value);
};

// EOF