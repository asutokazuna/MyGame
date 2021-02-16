/**
 * @file Mesh
 * @brief メッシュクラス
 * @author Ariga
 */
#pragma once
#include "Component.h"
#include <d3d11.h>
#include "MyMath.h"
#include "ShaderInfo.h"

// 前方宣言
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

/**
 * @class Mesh
 * @brief メッシュクラス
 */
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
	/**
	 * @brief メッシュの頂点データの生成
	 * @return なし
	 */
	HRESULT MakeMeshVertex(VERTEX_3D vertexWk[], int indexWk[]);

	/**
	 * @brief 大きさの変更
	 * @param[in] size 大きさ
	 * @return インスタンス
	 */
	Mesh* ChangeSize(XMFLOAT3 size);

	/**
	 * @brief 大きさの変更
	 * @param[in] x x方向の大きさ
	 * @param[in] y y方向の大きさ
	 * @param[in] z z方向の大きさ
	 * @return インスタンス
	 */
	Mesh* ChangeSize(float x, float y, float z);

	/**
	 * @brief 座標の変更
	 * @param[in]
	 * @return インスタンス
	 */
	Mesh* ChangePos(XMFLOAT3 pos);

	/**
	 * @brief 座標の変更
	 * @param[in]
	 * @return インスタンス
	 */
	Mesh* ChangePos(float x, float y, float z);

	/**
	 * @brief シェーダーの設定
	 * @param[in]
	 * @return なし
	 */
	void SetShader(ShaderInfo& shader);

	/**
	 * @brief 描画するプリミティブタイプの設定
	 * @return なし
	 */
	void SetPrimitive(int kind) {
		m_primitiveType = (ePrimitiveType)kind;
	}

	/**
	 * @brief ブレンドステートの設定
	 * @return なし
	 */
	void SetBlendState(int kind) {
		m_BSKind = kind;
	}

	/**
	 * @brief シェーダーの取得
	 * @return なし
	 */
	ShaderInfo* GetShader() {
		return m_shader;
	}

	/**
	 * @brief Zbuffer書き込み設定
	 * @return なし
	 */
	void SetZwrite(bool flg) {
		m_isZwerite = flg;
	}
};

// EOF