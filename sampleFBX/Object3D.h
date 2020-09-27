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
	/**
	 * @breif �R���X�g���N�^
	 */
	Object3D();

	/**
	 * @breif ����������
	 * @return �Ȃ�
	 */
	HRESULT Init();

	/**
	 * @breif �I��
	 * @return �Ȃ�
	 */
	void Uninit();

	/**
	 * @breif �X�V
	 * @return �Ȃ�
	 */
	void Update();

	/**
	 * @breif �`��
	 * @return �Ȃ�
	 */
	void Draw();

	/**
	 * @breif �`��
	 * @return �Ȃ�
	 */
	void DrawAlpha();

	/**
	 * @brief �\�����郂�f���̎�ނ�ݒ�
	 * @param	kind	�\�����郂�f���̎��ʎq
	 * @retrun ����
	 */
	Object3D& SetModel(int kind);

	/**
	 * @brief �\�����郂�f���̎�ނ�ݒ�
	 * @param	kind	�\�����郂�f���̎��ʎq
	 * @retrun ����
	 */
	Object3D& SetModel(ModelKind kind);

	/**
	 * @brief �\�����郂�f���̐F��ݒ�
	 * @param	mat	�\������F
	 * @retrun ����
	 */
	void SetMaterial(TFbxMaterial& color);
};

// EOF