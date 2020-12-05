#pragma once
#include "ShaderInfo.h"


class ClothShaderInfo :public ShaderInfo
{
private:
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_world;
	XMFLOAT4X4 m_TexWorld;
	ID3D11ShaderResourceView* m_pTexture;
public:
	ClothShaderInfo();
	~ClothShaderInfo();
	void Awake();
	//HRESULT Init();
	void Uninit();
	void Draw();
	void SetTexture(int kind);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetFloat(std::string key, XMFLOAT4X4 value);
};

