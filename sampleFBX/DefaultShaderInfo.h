#pragma once
#include "ShaderInfo.h"

class Transform;

class DefaultShaderInfo :public ShaderInfo
{
private:
	struct SHADER_GLOBAL {
		XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
		XMMATRIX	mW;			// ワールド行列(転置行列)
		XMMATRIX	mTex;		// テクスチャ行列(転置行列)
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
	};
private:
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_world;

public:
	DefaultShaderInfo();
	~DefaultShaderInfo();
	void Awake();
	//HRESULT Init();
	void Uninit();
	void UpdateConstant();
	void SetView(XMFLOAT4X4 view);
	void SetProj(XMFLOAT4X4 proj);
	void SetFloat(std::string key, XMFLOAT4X4 value);
	void SetUV(Vector3 uv, Vector3 scale = Vector3(1,1,1));
};

// EOF