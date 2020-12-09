#include "TitleStateMachine.h"
#include <memory>
#include "ObjectManager.h"
#include "TitleRogo.h"
#include "Rogo.h"

/**
 * @struct 初期化
 */
struct TITLE_INIT : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_INIT(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_INIT), machine(_machine) {}

	void Init()
	{
		machine.m_clothRogo->InitParam();
		machine.m_rogo->SetActive(false);
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

	void Update()
	{
		machine.m_clothRogo->Move();

		if (machine.m_clothRogo->IsArrive() == true) {
			machine.GoToState(E_TITLE_STATE_WAVE);
		}
	}
};

/**
 * @struct ロゴが飛んでくるところ
 */
struct TITLE_WAVE : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_WAVE(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_WAVE), machine(_machine) {}

	void Update()
	{
		if (machine.m_clothRogo->MovePower()) {
			machine.GoToState(E_TITLE_STATE_FADE);
		}
	}
};

/**
 * @struct 待機
 */
struct TITLE_FADE : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_FADE(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_FADE), machine(_machine) {}

	void Init()
	{
		machine.m_rogo->SetActive(true);
	}

	void Update()
	{
		if (machine.m_clothRogo->Fade()) {
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
		
	}
};

/**
 * @brief 初期化処理
 * @return なし
 */
void TitleStateMachine::Awake()
{
	m_clothRogo = ObjectManager::GetInstance().FindObject<TitleRogo>("TitleRogo");
	m_rogo = ObjectManager::GetInstance().FindObject<Rogo>("Rogo");
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
	AddState(std::make_shared<TITLE_WAVE>(*this));
	AddState(std::make_shared<TITLE_FADE>(*this));
	AddState(std::make_shared<TITLE_IDOL>(*this));
}

// EOF