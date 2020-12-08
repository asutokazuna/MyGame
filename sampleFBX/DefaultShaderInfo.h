#pragma once
#include "ShaderInfo.h"

class Transform;

class DefaultShaderInfo :public ShaderInfo
{
public:
private:
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_world;
	XMFLOAT4X4 m_TexWorld;
	ID3D11ShaderResourceView* m_pTexture;
public:
	DefaultShaderInfo();
	~DefaultShaderInfo();
	void Awake();
	//HRESULT Init();
	void Uninit();
	void UpdateConstant();
	DefaultShaderInfo* SetTexture(int kind);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetView(XMFLOAT4X4 view);
	void SetProj(XMFLOAT4X4 proj);
	void SetFloat(std::string key, XMFLOAT4X4 value);
};

// EOF