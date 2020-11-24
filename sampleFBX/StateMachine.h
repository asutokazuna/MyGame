/**
 * @file StateMachine.h
 * @brief ステートマシン
 */
#pragma once
#include <memory>
#include <unordered_map>
#include "Component.h"

/**
 * @class State
 * @brief ステート
 */
template<typename T>
class State 
{
private:
	T m_id;
public:
	/**
	 * @brief コンストラクタ
	 */
	explicit State(T id) :m_id(id) {}

	/**
	 * @brief デストラクタ
	 */
	virtual ~State() = default;

	/**
	 * @brief 状態IDの取得
	 * @return 状態ID
	 */
	const T& GetID() { return m_id; }

	/**
	 * @brief 状態に入った時に呼ばれる
	 * @return なし
	 */
	virtual void Init(){}

	/**
	 * @brief 終了処理
	 * @return なし
	 */
	virtual void Uninit(){}

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	virtual void Update(){}

	/**
	 * @biref 描画処理
	 * @return なし
	 */
	virtual void Draw() const {}
};

/**
 * @class StateMachine
 * @brief 状態管理クラス
 */
template<typename T>
class StateMachine : public Component
{
private:
	std::unordered_map<T, std::shared_ptr<State<T>>> m_stateList;	//!< 状態管理リスト

	std::shared_ptr<State<T>> m_state;		//!< 現在の状態
public:
	/**
	 * @brief コンストラクタ
	 */
	StateMachine() = default;

	/**
	 * @brief デストラクタ
	 */
	virtual ~StateMachine() = default;

	/**
	 * @brief 現在の状態の取得
	 * @return 現在の状態
	 */
	const T& GetState() const 
	{
		if (m_state == nullptr) {
			return nullptr;
		}
		return m_state->GetID();
	}

	/**
	 * @brief 状態の移行
	 * @return なし
	 */
	void GoToState(T nextID)
	{
		if (m_stateList[nextID] == nullptr) {
			return;
		}

		if (m_state != nullptr) {
			m_state->Uninit();
		}

		m_state = m_stateList[nextID];
		m_state->Init();
	}

	/**
	 * @brief ステートマシンの初期化
	 * @return なし
	 */
	virtual void SetState() = 0;

	/**
	 * @brief 状態の追加
	 * @return なし
	 */
	void AddState(const std::shared_ptr<State<T>>& state)
	{
		if (state == nullptr) {
			return;
		}

		if (m_stateList[state->GetID()] != nullptr) {
			return;
		}
		m_stateList[state->GetID()] = state;
	}

	/**
	 * @brief 更新処理
	 * @return なし
	 */
	void Update()
	{
		if (m_state == nullptr) {
			return;
		}
		m_state->Update();
	}

	/**
	 * brief 描画処理
	 * @return なし
	 */
	void Draw()
	{
		if (m_state == nullptr) {
			return;
		}
		m_state->Draw();
	}
};

// EOF