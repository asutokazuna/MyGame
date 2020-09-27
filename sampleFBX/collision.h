/**
 * @file Collision
 * @brief “–‚½‚è”»’èƒNƒ‰ƒX
 */
#pragma once
#include "Component.h"
#include <unordered_map>
#include "MyMath.h"
#include "Box.h"

class Collision :public Component
{
private:
	static std::unordered_map<int, Collision*> m_List;
#ifdef _DEBUG
	CBox m_box;
#endif
protected:
	Vector3 pos;
	Vector3 size;
	int id;
	int m_tag;

public:
	enum COL_TAG
	{
		COL_PLAYER,
		COL_ENEMY,
		COL_MISSILE,
		COL_MISSILE_ENEMY,
		COL_TOWER,
		COL_CORE_PLAYER,
		COL_CORE_ENEMY,
		COL_MAX
	};
public:
	Collision();
	~Collision();
	HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	virtual void DrawAlpha();
	virtual void SetTag(int tag);
	virtual void Check(Collision* othor);
	Collision* SetPos(Vector3);
	Collision* SetSize(Vector3);
	int GetTag();

public :
	static void Check();
	static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);
	static void Clear();
};

// EOF