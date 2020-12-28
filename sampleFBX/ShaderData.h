/**
 * @file ShaderData
 * @brief シェーダーデータクラス
 */
#pragma once
#include <d3d11.h>
#include <vector>
#include "Singleton.h"
#include "Data.h"

/**
 * @class シェーダーデータを格納するクラス
 */
class ShaderData: public Singleton<ShaderData>
{
public:
	friend class Singleton<ShaderData>;		//!< シングルトンでのインスタンスの生成用

private:
	DXData<ID3D11VertexShader>		m_VS;		//!< バーテックスシェーダー
	DXData<ID3D11PixelShader>		m_PS;		//!< ピクセルシェーダー
	DXData<ID3D11HullShader>		m_HS;		//!< ハルシェーダー
	DXData<ID3D11DomainShader>		m_DS;		//!< ドメインシェーダー
	DXData<ID3D11GeometryShader>	m_GS;		//!< ドメインシェーダー
	DXData<ID3D11InputLayout>		m_IL;		//!< インプットレイアウト

private:

	/**
	 * @brief　データの初期化
	 * @return なし
	 */
	void InitInstance();
	
public:
	/**
	 * @enum バーテックスシェーダーの種類
	 */
	enum VS_KIND
	{
		VS_VERTEX,
		VS_CLOTH,
		VS_DEFAULT,
		VS_MAX
	};

	/**
	 * @enum ピクセルシェーダーの種類
	 */
	enum PS_KIND
	{
		PS_PIXEL,
		PS_CLOTH,
		PS_EXPLOSION,
		PS_LIFEGAUGE,
		PS_MAX
	};

	/**
	 * @enum ハルシェーダーの種類
	 */
	enum HS_KIND
	{
		HS_CLOTH,
		HS_DEFAULT,
		HS_MAX
	};

	/**
	 * @enum ドメインシェーダーの種類
	 */
	enum DS_KIND
	{
		DS_CLOTH,
		DS_DEFAULT,
		DS_MAX
	};
	
	/**
	 * @enum ジオメトリシェーダーの種類
	 */
	enum GS_KIND
	{
		GS_EXPLOSION,
		GS_MAX
	};

	/**
	 * @biref 初期化処理
	 * @return なし
	 */
	static void Init();

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	static void Uninit();

	/**
	 * @brief バーテックスシェーダーの取得
	 * @param[in] 取得したい種類のenum
	 * @return 引数に対応したシェーダーデータ
	 */
	static ID3D11VertexShader* GetVertexShader(int kind);

	/**
	 * @brief ピクセルシェーダーの取得
	 * @param[in] 取得したい種類のenum
	 * @return 引数に対応したシェーダーデータ
	 */
	static ID3D11PixelShader* GetPixelShader(int kind);

	/**
	 * @brief ハルシェーダーの取得
	 * @param[in] 取得したい種類のenum
	 * @return 引数に対応したシェーダーデータ
	 */
	static ID3D11HullShader* GetHullShader(int kind);

	/**
	 * @brief ドメインシェーダーの取得
	 * @param[in] 取得したい種類のenum
	 * @return 引数に対応したシェーダーデータ
	 */
	static ID3D11DomainShader* GetDomainShader(int kind);

	/**
	 * @brief ジオメトリシェーダーの取得
	 * @param[in] 取得したい種類のenum
	 * @return 引数に対応したシェーダーデータ
	 */
	static ID3D11GeometryShader* GetGeometryShader(int kind);

	/**
	 * @brief インプットレイアウトの取得
	 * @param[in] 取得したい種類のenum
	 * @return 引数に対応したインプットレイアウト
	 */
	static ID3D11InputLayout* GetInputLayout(int kind);
};

// EOF