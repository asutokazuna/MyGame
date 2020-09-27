/**
 * @file Mesh
 * @brief メッシュクラス
 */
#pragma once
#include "Component.h"
#include <d3d11.h>

class Transform;

// 頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 反射光 / テクスチャ座標 )
typedef struct {
	XMFLOAT3 vtx;		// 頂点座標
	XMFLOAT3 nor;		// 法線ベクトル
	XMFLOAT4 diffuse;	// 拡散反射光
	XMFLOAT2 tex;		// テクスチャ座標
} VERTEX_3D;

class Mesh: public Component
{
protected:
	enum ePrimitiveType {
		PT_UNDEFINED = 0,
		PT_POINT,
		PT_LINE,
		PT_LINESTRIP,
		PT_TRIANGLE,
		PT_TRIANGLESTRIP,

		MAX_PRIMITIVETYPE
	};

	typedef struct {
		XMFLOAT4	Diffuse;		// Diffuse color RGBA
		XMFLOAT4	Ambient;		// Ambient color RGB
		XMFLOAT4	Specular;		// Specular 'shininess'
		XMFLOAT4	Emissive;		// Emissive color RGB
		float		Power;			// Sharpness if specular highlight
	} MATERIAL;

	Transform* m_transform;
	XMFLOAT4X4 m_View;
	XMFLOAT4X4 m_Proj;
	MATERIAL* m_material;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	int m_nNumVertex;
	int m_nNumIndex;

	ePrimitiveType m_primitiveType;

	Transform* m_TexTransform;
	ID3D11ShaderResourceView* m_pTexture;

	ID3D11Buffer*			m_pConstantBuffer[2];	// 定数バッファ
public:
	Mesh();
	~Mesh();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

public:
	HRESULT MakeMeshVertex(VERTEX_3D vertexWk[], int indexWk[]);
	Mesh* ChangeColor(XMFLOAT3 color);
	Mesh* ChangeColor(float r,float g, float b);
	Mesh* ChangeColor(XMFLOAT4 color);
	Mesh* ChangeColor(float r, float g, float b, float a);
	Mesh* ChangeSize(XMFLOAT3 size);
	Mesh* ChangeSize(float x, float y, float z);
	Mesh* ChangePos(XMFLOAT3 pos);
	Mesh* ChangePos(float x, float y, float z);
	Mesh* ChangeUV(XMFLOAT2 uv);
	Mesh* ChangeUV(float u, float v);
	Mesh* SetTexture(const char* filename);
	Mesh* SetTexture(const wchar_t* filename);
};

// EOF