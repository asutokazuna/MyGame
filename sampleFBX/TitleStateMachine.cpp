#include "TitleStateMachine.h"
#include <memory>
#include "ObjectManager.h"
#include "TitleRogo.h"

/**
 * @struct 初期化
 */
struct TITLE_INIT : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_INIT(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_INIT), machine(_machine) {}

	void Init()
	{
		machine.m_rogo->InitParam();
		machine.GoToState(E_TITLE_STATE_FLY);
	}
};

/**
 * @struct ロゴが飛んでくるところ
 */
struct TITLE_FLY : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_FLY(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_FLY), machine(_machine) {}

	void Init()
	{

	}

	void Update()
	{
		machine.m_rogo->Move();

		if (machine.m_rogo->IsArrive() == true) {
			machine.GoToState(E_TITLE_STATE_IDOL);
		}
	}
};

/**
 * @struct 待機
 */
struct TITLE_IDOL : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_IDOL(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_IDOL), machine(_machine) {}

	void Update()
	{
		machine.m_rogo->MovePower();
	}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleStateMachine::Awake()
{
	m_rogo = ObjectManager::GetInstance().FindObject<TitleRogo>("TitleRogo");
	SetState();
	GoToState(E_TITLE_STATE_INIT);
}

/**
 * @brief ステートをリストにセット
 *@return なし
 */
void TitleStateMachine::SetState()
{
	AddState(std::make_shared<TITLE_INIT>(*this));
	AddState(std::make_shared<TITLE_FLY>(*this));
	AddState(std::make_shared<TITLE_IDOL>(*this));
}

// EOF