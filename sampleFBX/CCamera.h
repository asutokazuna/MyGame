/**
 * @file CCamera.h
 * @brief �J�����N���X
 */
#pragma once
#include "main.h"
#include "Transform.h"

class CCamera
{
protected:
	XMFLOAT3	m_vEye;		//!< ���_���W
	XMFLOAT3	m_vLook;	//!< �����_���W
	XMFLOAT3	m_vUp;		//!< ����x�N�g��
	XMFLOAT4X4	m_View;		//!< �r���[�ϊ�
	XMFLOAT4X4	m_Proj;		//!< �ˉe�ϊ�
	float		m_fFOVY;	//!< ����p
	float		m_fAspect;	//!< �A�X�y�N�g��
	float		m_fNearZ;	//!< �O���N���b�v����
	float		m_fFarZ;	//!< ����N���b�v����
	static XMFLOAT3 m_vNowEye;	//!< ���݂̎��_
	static XMFLOAT3 m_vNowLook;	//!< ���݂̒����_
	static XMFLOAT3 m_vNowUp;	//!< ���݂̏���x�N�g��
	Transform *m_transform;

private:
	static CCamera* m_pCamera;	//!< ���ݗL���ȃJ����

public:
	CCamera();
	~CCamera();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void SetPos(XMFLOAT3 eye);
	void SetTransform(Transform& trans);

	XMFLOAT4X4& GetView();
	XMFLOAT4X4& GetProj();
	XMFLOAT3& GetEye();
	XMFLOAT3& GetLook();
	void SetLook(XMFLOAT3 vLook);
	static void Set(CCamera* pCamera);
	static CCamera* Get();
};

// EOF