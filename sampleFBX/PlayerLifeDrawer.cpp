/**
 * @file PlayerLifeDrawer
 * @brief プレイヤーのHPの表示
 */
#include "PlayerLifeDrawer.h"
#include "DigitNumber.h"

//def 
#define NUM_MAX_DIGIT (3)

 /**
 * @brief 初期化処理
 * @return なし
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