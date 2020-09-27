/**
 * @file Object3D.h
 * @brief 3D�I�u�W�F�N�g�̕\���p
 */
#pragma once
#include "Component.h"
#include "main.h"
#include "FbxModel.h"
#include "Box.h"
#include "Transform.h"
#include "ModelData.h"

class Object3D:public Component
{
private:
	Transform*	m_Transform;	// ���W
	CFbxLight	m_light;	//!< �������
	XMFLOAT4X4 m_world;		//!< ���[���h�}�g���b�N�X

	int m_ModelIndex;
	CFbxModel* m_Model;
	TFbxMaterial material;
public:
	Object3D();
	~Object3D();

	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();
	void DrawAlpha();

	Object3D& SetModel(int kind);

	Object3D& SetModel(ModelKind kind);

	void SetMaterial(TFbxMaterial& color);
};

// EOF