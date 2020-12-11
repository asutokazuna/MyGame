/**
 * @file Mesh
 * @brief メッシュクラス
 */
#pragma once
#include "Component.h"
#include <d3d11.h>
#include "MyMath.h"
#include "ShaderInfo.h"

class Transform;
class ShaderInfo;
class DefaultShaderInfo;

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
		PT_4CTRL,

		MAX_PRIMITIVETYPE
	};

	Transform* m_transform;
	ShaderInfo::MATERIAL* m_material;
	ShaderInfo* m_shader;	// シェーダー（マテリアルみたいなもの）
	DefaultShaderInfo* m_default;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	int m_nNumVertex;
	int m_nNumIndex;

	ePrimitiveType m_primitiveType;
	int m_BSKind;
	bool m_isZwerite;

public:
	Mesh();
	~Mesh();

	void Awake();

	/**
	 * @brief 初期化処理
	 * @return なし
	 */
	virtual void Uninit();
	virtual void Update();

	/**
	 * @brief 描画処理
	 * @return なし
	 */
	virtual void Draw();

public:
	HRESULT MakeMeshVertex(VERTEX_3D vertexWk[], int indexWk[]);
	Mesh* ChangeColor(XMFLOAT3 color);
	Mesh * ChangeColor(Vector3 color);
	Mesh* ChangeColor(float r,float g, float b);
	Mesh* ChangeColor(XMFLOAT4 color);
	Mesh* ChangeColor(float r, float g, float b, float a);
	Mesh* ChangeSize(XMFLOAT3 size);
	Mesh* ChangeSize(float x, float y, float z);
	Mesh* ChangePos(XMFLOAT3 pos);
	Mesh* ChangePos(float x, float y, float z);
	void SetShader(ShaderInfo& shader);
	void SetPrimitive(int kind) {
		m_primitiveType = (ePrimitiveType)kind;
	}
	void SetBlendState(int kind) {
		m_BSKind = kind;
	}

	ShaderInfo* GetShader() {
		return m_shader;
	}

	void SetZwrite(bool flg) {
		m_isZwerite = flg;
	}
};

// EOF