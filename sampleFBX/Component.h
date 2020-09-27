/**
 * @file Component.h
 * @brief コンポーネントオブジェクト
 */
#pragma once
#include "Object.h"

class GameObject;

/**
 *@class Component
 * コンポーネントクラス
 */
class Component : public Object
{
public:
	GameObject *m_Parent;	//!< 親オブジェクト

	/**
	 * @brief コンストラクタ
	 */
	Component(){}

	/**
	 * @brief デストラクタ
	 */
	virtual ~Component(){}

};

// EOF