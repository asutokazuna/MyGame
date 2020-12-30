/**
 * @file GaugeUI
 * @brief UI�p�Q�[�W�\���I�u�W�F�N�g
 */
#include "GaugeUI.h"
#include "UIMesh.h"
#include "LifeGaugeShaderInfo.h"

/**
 * @breif ����������
 * @return �Ȃ�
 */
void GaugeUI::Awake()
{
	Mesh* mesh = AddComponent<UIMesh>();
	ShaderInfo* shader = AddComponent<LifeGaugeShaderInfo>();
	mesh->SetShader(*shader);
}

// EOF