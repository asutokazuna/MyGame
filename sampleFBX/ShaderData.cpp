/**
 * @file ShaderData
 * @brief �V�F�[�_�[�f�[�^�N���X
 */
#include "ShaderData.h"
#include "Shader.h"

/**
 * @struct �V�F�[�_�[�f�[�^�̃e�[�u��
 */
struct SHADER_TABLE {
	int type;
	const char* filename;
};

/**
 * @biref �o�[�e�b�N�X�V�F�[�_�[
 */
SHADER_TABLE VS_Table[] = 
{
	{ShaderData::VS_VERTEX, "Vertex"},
};

/**
 * @biref �s�N�Z���V�F�[�_
 */
SHADER_TABLE PS_Table[] = 
{
	{ShaderData::PS_PIXEL, "Pixel"},
};

/**
 * @brief�@�f�[�^�̏�����
 * @return �Ȃ�
 */
void ShaderData::InitInstance()
{
	// �V�F�[�_������
	static const D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,                            D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	ID3D11VertexShader* workVs;
	ID3D11InputLayout* workIl;
	ID3D11PixelShader* workPs;

	for (int i = 0; i < VS_MAX; i++)
	{
		LoadVertexShader(VS_Table[i].filename, &workVs, &workIl, layout, _countof(layout));
		m_VS.Set(VS_Table[i].type,workVs);
		m_IL.Set(VS_Table[i].type,workIl);
	}
	for (int i = 0; i < PS_MAX; i++)
	{
		LoadPixelShader(PS_Table[i].filename, &workPs);
		m_PS.Set(PS_Table[i].type,workPs);
	}
}

/**
 * @biref ����������
 * @return �Ȃ�
 */
void ShaderData::Init()
{
	ShaderData::GetInstance().InitInstance();
}

/**
 * @brief �I������
 * @return �Ȃ�
 */
void ShaderData::Uninit()
{
	// �����Ȃ�
}

/**
 * @brief �o�[�e�b�N�X�V�F�[�_�[�̎擾
 * @param[in] �擾��������ނ�enum
 * @return �����ɑΉ������V�F�[�_�[�f�[�^
 */
ID3D11VertexShader* ShaderData::GetVertexShader(int kind)
{
	return ShaderData::GetInstance().m_VS.Get(kind);
}

/**
 * @brief �s�N�Z���V�F�[�_�[�̎擾
 * @param[in] �擾��������ނ�enum
 * @return �����ɑΉ������V�F�[�_�[�f�[�^
 */
ID3D11PixelShader* ShaderData::GetPixelShader(int kind)
{
	return ShaderData::GetInstance().m_PS.Get(kind);
}

/**
 * @brief �C���v�b�g���C�A�E�g�̎擾
 * @param[in] �擾��������ނ�enum
 * @return �����ɑΉ������C���v�b�g���C�A�E�g
 */
ID3D11InputLayout* ShaderData::GetInputLayout(int kind)
{
	return ShaderData::GetInstance().m_IL.Get(kind);
}

// EOF