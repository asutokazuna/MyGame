#include "TitleStateMachine.h"
#include <memory>

/**
* @struct 待機
*/
struct TITLE_IDOL : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_IDOL(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_IDOL), machine(_machine) {}

	void Update()
	{

	}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleStateMachine::Awake()
{
	SetState();
}

/**
 * @brief ステートをリストにセット
 *@return なし
 */
void TitleStateMachine::SetState()
{
	AddState(std::make_shared<TITLE_IDOL>(*this));
}

// EOF