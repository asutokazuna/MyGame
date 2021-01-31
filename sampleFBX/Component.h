/**
 * @file Component.h
 * @brief コンポーネントオブジェクト
 */
#pragma once
#include "Object.h"

class GameObject;
class Transform;

/**
 *@class Component
 * コンポーネントクラス
 */
class Component : public Object
{
public:
	GameObject *m_Parent;	//!< 親オブジェクト
	int m_tagParent;				//!< ゲームオブジェクトのタグ
	Transform* m_ParentTransform;	//!< ゲームオブジェクトについているtransform

public:
	/**
	 * @brief コンストラクタ
	 */
	Component():m_Parent(nullptr), m_tagParent(-1), m_ParentTransform(nullptr){}

	/**
	 * @brief デストラクタ
	 */
	virtual ~Component(){}
	
	/**
	 * @brief 当たり判定処理
	 * @return なし
	 */
	virtual void OnCollisionEnter(GameObject* gameObbj){}

};

// EOF