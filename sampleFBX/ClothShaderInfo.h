#pragma once
#include "ShaderInfo.h"


class ClothShaderInfo :public ShaderInfo
{
private:
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_world;
	XMFLOAT4X4 m_TexWorld;
	float m_power;
	ID3D11ShaderResourceView* m_pTexture;
public:
	ClothShaderInfo();
	~ClothShaderInfo();
	void Awake();
	//HRESULT Init();
	void Uninit();
	void UpdateConstant();
	void SetTexture(int kind);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetFloat(std::string key, float value);
	void SetFloat(std::string key, XMFLOAT4X4 value);
};

