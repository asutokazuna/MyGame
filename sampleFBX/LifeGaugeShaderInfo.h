#pragma once
#include "ShaderInfo.h"

class LifeGaugeShaderInfo :	public ShaderInfo
{
private:
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	XMFLOAT4X4 m_world;
	XMFLOAT4X4 m_TexWorld;
	float m_SizePer;
	ID3D11ShaderResourceView* m_pTexture;
public:
	LifeGaugeShaderInfo();
	~LifeGaugeShaderInfo();
	void Awake();
	//HRESULT Init();
	void Uninit();
	void UpdateConstant();
	LifeGaugeShaderInfo* SetTexture(int kind);
	void SetTexture(ID3D11ShaderResourceView* texture);
	void SetView(XMFLOAT4X4 view);
	void SetProj(XMFLOAT4X4 proj);
	void SetFloat(std::string key, XMFLOAT4X4 value);
	void SetFloat(std::string key, float value);
	void SetUV(Vector3 uv, Vector3 scale = Vector3(1, 1, 1));
};

// EOF