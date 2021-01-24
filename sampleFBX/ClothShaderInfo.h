#pragma once
#include "ShaderInfo.h"

/** 
 * @class ClothShaderInfo
 * @biref 布のように揺らめくシェーダー
 */
class ClothShaderInfo :public ShaderInfo
{
private:
	struct SHADER_GLOBAL {
		XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
		XMMATRIX	mW;			// ワールド行列(転置行列)
		XMMATRIX	mTex;		// テクスチャ行列(転置行列)
		XMFLOAT4	value;
	};
	struct SHADER_GLOBAL2 {
		XMVECTOR	vEye;		// 視点座標
								// 光源
		XMVECTOR	vLightDir;	// 光源方向
		XMVECTOR	vLa;		// 光源色(アンビエント)
		XMVECTOR	vLd;		// 光源色(ディフューズ)
		XMVECTOR	vLs;		// 光源色(スペキュラ)
								// マテリアル
		XMVECTOR	vAmbient;	// アンビエント色(+テクスチャ有無)
		XMVECTOR	vDiffuse;	// ディフューズ色
		XMVECTOR	vSpecular;	// スペキュラ色(+スペキュラ強度)
		XMVECTOR	vEmissive;	// エミッシブ色
		XMFLOAT4	value;
	};

private:
	XMFLOAT4X4 m_View;		//!< ビュー行列
	XMFLOAT4X4 m_Proj;		//!< プロジェクション行列
	XMFLOAT4X4 m_world;		//!< ワールド行列
	float m_power;			//!< 揺れる強さ(振幅)
	float m_fadethrosh;		//!< 消える速度
	ID3D11ShaderResourceView* m_pNoizeTexture;	//!< テクスチャ
public:
	/**
	 * @brief コンストラクタ
	 */
	ClothShaderInfo();
	
	/**
	 * @brief デストラクタ
	 */
	~ClothShaderInfo();
	
	/**
	 * @brief 初期化
	 * @retrun なし
	 */
	void Awake();
	//HRESULT Init();
		
	/**
	 * @brief 終了
	 * @retrun なし
	 */
	void Uninit();
		
	/**
	 * @brief コンスタントバッファの更新
	 * @retrun なし
	 */
	void UpdateConstant();
		

	void SetNoizeTexture(int kind);
		
	/**
	 * @brief テクスチャのセット
	 * @param[in] texture テクスチャデータ
	 * @retrun なし
	 */
	void SetTexture(ID3D11ShaderResourceView* texture);
			
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