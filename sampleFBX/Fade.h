/**
 * @file Fade
 * @brief フェードクラス
 */
#pragma once

class GameObject;

class Fade
{
private:
	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};
private:
	static Fade* m_instance;

	GameObject* m_Mesh;
	bool m_isFade;
	float m_Alpha;
	int m_State;
private:
	void InitInst();
	void UninitInst();
	void UpdateInst();
	void DrawInst();
	bool IsFadeInst();
	void SetState(FADE_STATE state);

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static bool IsFade();
	static void FadeIn();
	static void FadeOut();
private:
	static Fade* Get();
};

// EOF