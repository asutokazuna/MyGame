/**
 * @file Default3DShaderInfo 
 * @brief 3Dモデル用デフォルトシェーダー
 */
#pragma once
#include "ShaderInfo.h"

#define MAX_BONE_MATRIX	256

class TFbxMaterial;

/**
 * @class Default3DShaderInfo 
 * @brief 3Dモデル用デフォルトシェーダー
 */
class Default3DShaderInfo :	public ShaderInfo
{
private:
	struct SHADER_GLOBAL {
		XMMATRIX	mWVP;		// ワールド×ビュー×射影行列(転置行列)
		XMMATRIX	mW;			// ワールド行列(転置行列)
		XMVECTOR	vEye;		// 視点座標
		XMVECTOR	vLightDir;	// 光源方向
		XMVECTOR	vLa;		// 光源色(アンビエント)
		XMVECTOR	vLd;		// 光源色(ディフューズ)
		XMVECTOR	vLs;		// 光源色(スペキュラ)
	};

	// マテリアル (シェーダ用)
	struct SHADER_MATERIAL {
		XMVECTOR	vAmbient;	// アンビエント色
		XMVECTOR	vDiffuse;	// ディフューズ色
		XMVECTOR	vSpecular;	// スペキュラ色
		XMVECTOR	vEmissive;	// エミッシブ色
	};

	// シェーダに渡すボーン行列配列
	struct SHADER_BONE {
		XMMATRIX mBone[MAX_BONE_MATRIX];
		SHADER_BONE()
		{
			for (int i = 0; i < MAX_BONE_MATRIX; i++) {
				mBone[i] = XMMatrixIdentity();
			}
		}
	};

private:
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_world;

public:
	Default3DShaderInfo();
	~Default3DShaderInfo();
	void Awake();
	//void UpdateConstant();

	//void UpdateMatCBuffer(TFbxMaterial* pMaterial);

	//void UpdateBoneCBuffer();

	void SetFloat(std::string key, XMFLOAT4X4 value);
};

// EOF