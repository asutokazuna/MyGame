/**
 * @file PlayerLifeDrawer
 * @brief �v���C���[��HP�̕\��
 */
#include "PlayerLifeDrawer.h"
#include "DigitNumber.h"

//def 
#define NUM_MAX_DIGIT (3)

 /**
 * @brief ����������
 * @return �Ȃ�
 */
void PlayerLifeDrawer::Awake()
{	
	for (int i = 0; i < NUM_MAX_DIGIT; i++)
	{
		DigitNumber* LifeEigit = new DigitNumber();
		SetChild(LifeEigit);
	}
}

// EOF