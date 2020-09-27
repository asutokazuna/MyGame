/**
 * @file Fade
 * @brief �t�F�[�h�N���X
 */
#pragma once
#include "Singleton.h"

// �O���錾
class GameObject;

/**
 * @class Fade
 * @brief �t�F�[�h
 */
class Fade: public Singleton<Fade>
{
private:
	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT

	};
private:
	GameObject* m_Mesh;
	bool m_isFade;
	float m_Alpha;
	int m_State;

private:
	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	void InitInst();

	/**
	 * @brief �I��
	 * @return �Ȃ�
	 */
	void UninitInst();

	/**
	 * @brief �X�V
	 * @return �Ȃ�
	 */
	void UpdateInst();

	/**
	 * @brief �`��
	 * @return �Ȃ�
	 */
	void DrawInst();

	/**
	 * @brief �t�F�[�h�������肷��
	 * @return �t�F�[�h���Ȃ�true
	 */
	bool IsFadeInst();

	/**
	 * @brief �t�F�[�h����
	 * @return �Ȃ�
	 */
	void SetState(FADE_STATE state);

public:

	/**
	 * @brief ������
	 * @return �Ȃ�
	 */
	static void Init();

	/**
	 * @brief �I��
	 * @return �Ȃ�
	 */
	static void Uninit();

	/**
	 * @brief �X�V
	 * @return �Ȃ�
	 */
	static void Update();

	/**
	 * @brief �`��
	 * @return �Ȃ�
	 */
	static void Draw();

	/**
	 * @brief �t�F�[�h�������肷��
	 * @return �t�F�[�h���Ȃ�true
	 */
	static bool IsFade();

	/**
	 * @brief �t�F�[�h�C��
	 * @return �Ȃ�
	 */
	static void FadeIn();

	/**
	 * @brief �t�F�[�h�A�E�g
	 * @return �Ȃ�
	 */
	static void FadeOut();
};

// EOF