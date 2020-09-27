/**
 * @file ShaderData
 * @brief �V�F�[�_�[�f�[�^�N���X
 */
#pragma once
#include <d3d11.h>
#include <vector>
#include "Singleton.h"
#include "Data.h"

/**
 * @class �V�F�[�_�[�f�[�^���i�[����N���X
 */
class ShaderData: public Singleton<ShaderData>
{
public:
	friend class Singleton<ShaderData>;		//!< �V���O���g���ł̃C���X�^���X�̐����p

private:
	DXData<ID3D11VertexShader> m_VS;		//!< �o�[�e�b�N�X�V�F�[�_�[
	DXData<ID3D11PixelShader> m_PS;		//!< �s�N�Z���V�F�[�_�[
	DXData<ID3D11InputLayout> m_IL;		//!< �C���v�b�g���C�A�E�g

private:

	/**
	 * @brief�@�f�[�^�̏�����
	 * @return �Ȃ�
	 */
	void InitInstance();
	
public:
	/**
	 * @enum �o�[�e�b�N�X�V�F�[�_�[�̎��
	 */
	enum VS_KIND
	{
		VS_VERTEX,
		VS_MAX
	};

	/**
	 * @enum �s�N�Z���V�F�[�_�[�̎��
	 */
	enum PS_KIND
	{
		PS_PIXEL,
		PS_MAX
	};

	/**
	 * @biref ����������
	 * @return �Ȃ�
	 */
	static void Init();

	/**
	 * @brief �I������
	 * @return �Ȃ�
	 */
	static void Uninit();

	/**
	 * @brief �o�[�e�b�N�X�V�F�[�_�[�̎擾
	 * @param[in] �擾��������ނ�enum
	 * @return �����ɑΉ������V�F�[�_�[�f�[�^
	 */
	static ID3D11VertexShader* GetVertexShader(int kind);

	/**
	 * @brief �s�N�Z���V�F�[�_�[�̎擾
	 * @param[in] �擾��������ނ�enum
	 * @return �����ɑΉ������V�F�[�_�[�f�[�^
	 */
	static ID3D11PixelShader* GetPixelShader(int kind);

	/**
	 * @brief �C���v�b�g���C�A�E�g�̎擾
	 * @param[in] �擾��������ނ�enum
	 * @return �����ɑΉ������C���v�b�g���C�A�E�g
	 */
	static ID3D11InputLayout* GetInputLayout(int kind);
};

// EOF