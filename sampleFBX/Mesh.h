/**
 * @file Mesh
 * @brief ���b�V���N���X
 */
#pragma once
#include "Component.h"
#include <d3d11.h>

class Transform;

// ���_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���ˌ� / �e�N�X�`�����W )
typedef struct {
	XMFLOAT3 vtx;		// ���_���W
	XMFLOAT3 nor;		// �@���x�N�g��
	XMFLOAT4 diffuse;	// �g�U���ˌ�
	XMFLOAT2 tex;		// �e�N�X�`�����W
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

	ID3D11Buffer*			m_pConstantBuffer[2];	// �萔�o�b�t�@
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