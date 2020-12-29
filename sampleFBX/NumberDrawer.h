/**
 * @file NumberDrawer
 * @brief 1�����\���R���|�[�l���g
 */
#pragma once
#include "Component.h"

class DefaultShaderInfo;

/**
 * @class 
 * @brief 
 */
class NumberDrawer :public Component
{
private:
	int num;
	DefaultShaderInfo* m_shader;
public:

	/**
	 * @brief �R���X�g���N�^
	 */
	NumberDrawer();

	void Awake();

	/**
	 * @brief ����������
	 * @retrun �Ȃ�
	 */
	//HRESULT Init();

	/**
	 * @brief �����̃Z�b�g
	 * @return �Ȃ�
	 */
	void SetNumber(int num);
};

// EOF