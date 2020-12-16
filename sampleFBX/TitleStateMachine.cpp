#include "TitleStateMachine.h"
#include <memory>
#include "ObjectManager.h"
#include "TitleRogo.h"
#include "Rogo.h"
#include "TitleStart.h"
#include "StarCreater.h"
#include "RogoColor.h"
#include "input.h"

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
		machine.m_rogo->SetActive(true);
		machine.m_rogo->InitParam();
		machine.m_startText->SetActive(false);
		machine.m_clothRogo->SetActive(false);
		machine.m_particle->SetActive(false);
		machine.m_rogoColor->SetActive(false);
	}

	void Update()
	{
		//if(CInput::GetKeyTrigger(VK_0))
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
	const int  value = 180;

	void Init()
	{
		time = 0;
	}

	void Update()
	{
		time++;

		float t = time / (float)value;

		machine.m_rogo->Move(t);

		if (t >= 1) {
			machine.GoToState(E_TITLE_STATE_FADE);
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
	float t = 0;
	int wait;

	void Init()
	{
		machine.m_rogoColor->SetActive(true);
		//machine.m_startText->SetActive(true);
		t = 0;
		wait = 0;
	}

	void Update()
	{
		if (++wait < 15) {
			return;
		}
		machine.m_rogo->Fade(t);
		t  += 1 / (float)120;
		if (t >= 1) {
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
	const int MAX_LOOP_TIME = 300;

	void Init()
	{
		machine.m_clothRogo->SetActive(false);
		machine.m_startText->SetActive(true);
		machine.m_particle->SetActive(true);
		loopTime = 0;
	}

	void Update()
	{
		//loopTime++;
		//if (loopTime > MAX_LOOP_TIME) {
		//	machine.GoToState(E_TITLE_STATE_LEAVE);
		//}
		machine.m_particle->GetComponent<StarCreater>()->Move();
	}

	void Uninit()
	{
		machine.m_startText->SetActive(false);
		machine.m_particle->SetActive(false);
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
	const int  value = 180;
	int ttt = 0;

	void Init()
	{
		time = 0;
		ttt = 0;
	}

	void Update()
	{
		time++;

		float t = time / (float)value;

		machine.m_rogo->Fade(t);

		if (t >= 1) {
			ttt++;
		}
		if (ttt > 2 * 60) {
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
	m_particle = ObjectManager::GetInstance().FindObject<GameObject>("StarManager");
	m_rogoColor = ObjectManager::GetInstance().FindObject<RogoColor>("RogoColor");
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