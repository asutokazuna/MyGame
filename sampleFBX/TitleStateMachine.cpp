#include "TitleStateMachine.h"
#include <memory>
#include "ObjectManager.h"
#include "TitleRogo.h"
#include "Rogo.h"
#include "TitleStart.h"

#define START_POS (-SCREEN_CENTER_X - 700 * 2)
#define END_POS (0)

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
		machine.m_startText->SetActive(false);
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
	int time;

	void Init()
	{
		time = 0;
	}

	void Update()
	{
		time++;
		if (machine.m_clothRogo->Move(START_POS, END_POS, time) == true) {
			machine.GoToState(E_TITLE_STATE_WAVE);
		}
	}
};

/**
 * @struct 波が弱くなる
 */
struct TITLE_WAVE : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_WAVE(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_WAVE), machine(_machine) {}

	void Update()
	{
		if (machine.m_clothRogo->MovePower(-0.0005f)) {
			machine.GoToState(E_TITLE_STATE_FADE);
		}
	}
};

/**
 * @struct フェード
 */
struct TITLE_FADE : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_FADE(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_FADE), machine(_machine) {}

	void Init()
	{
		machine.m_rogo->SetActive(true);
		machine.m_startText->SetActive(true);
	}

	void Update()
	{
		if (machine.m_clothRogo->Fade(0.005f)) {
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
	int loopTime;
	const int MAX_LOOP_TIME = 180;

	void Init()
	{
		loopTime = 0;
	}

	void Update()
	{
		loopTime++;
		if (loopTime > MAX_LOOP_TIME) {
			machine.GoToState(E_TITLE_STATE_FADEOUT);
		}
	}
};

/**
 * @struct フェードアウト
 */
struct TITLE_FADEOUT : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_FADEOUT(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_FADEOUT), machine(_machine) {}

	void Init()
	{
		machine.m_rogo->SetActive(true);
		machine.m_startText->SetActive(false);
	}

	void Update()
	{
		if (machine.m_clothRogo->FadeOUT(0.01f)) {
			machine.GoToState(E_TITLE_STATE_LEAVE);
		}
	}
	void Uninit()
	{
		machine.m_rogo->SetActive(false);
	}
};

/**
 * @struct ロゴが飛んでいくところ
 */
struct TITLE_LEAVE : public State<TITLE_STATE>
{
	TitleStateMachine& machine;
	TITLE_LEAVE(TitleStateMachine & _machine) : State<TITLE_STATE>(TITLE_STATE::E_TITLE_STATE_LEAVE), machine(_machine) {}
	int time;

	void Init()
	{
		time = 0;
	}

	void Update()
	{
		time++;
		machine.m_clothRogo->MovePower(0.0005f);

		if (machine.m_clothRogo->Move(END_POS, -START_POS, time) == true) {
			machine.GoToState(E_TITLE_STATE_INIT);
		}
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
	m_startText = ObjectManager::GetInstance().FindObject<TitleStart>("TitleStart");
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
	AddState(std::make_shared<TITLE_FADEOUT>(*this));
	AddState(std::make_shared<TITLE_LEAVE>(*this));
}

// EOF