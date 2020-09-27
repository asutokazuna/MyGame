/**
 * @file Collision
 * @brief �����蔻��N���X
 */
#pragma once
#include "Component.h"
#include <unordered_map>
#include "MyMath.h"
#include "Box.h"

/**
 * @class Collision
 * @brief �R���C�_�[
 */
class Collision :public Component
{
private:
	static std::unordered_map<int, Collision*> m_List;	//!< �R���C�_�[���X�g

#ifdef _DEBUG
	CBox m_box;	//!< �����蔻��̃T�C�Y�f�o�b�O�p
#endif

protected:
	Vector3 pos;	//!< ���W
	Vector3 size;	//!< �傫��
	int id;			//!< ���j�[�NID
	int m_tag;		//!< ���ʃ^�O

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
	/**
	 * @breif �R���X�g���N�^
	 */
	Collision();

	/**
	 * @brief �f�X�g���N�^
	 */
	~Collision();

	/**
	 * @breif ����������
	 * @return �Ȃ�
	 */
	HRESULT Init();

	/**
	 * @breif �I��
	 * @return �Ȃ�
	 */
	virtual void Uninit();

	/**
	 * @breif �X�V
	 * @return �Ȃ�
	 */
	virtual void Update();

	/**
	 * @breif �`��
	 * @return �Ȃ�
	 */
	virtual void Draw();

	/**
	 * @breif �`��
	 * @return �Ȃ�
	 */
	virtual void DrawAlpha();

	/**
	 * @breif �^�O�̐ݒ�
	 * @return �Ȃ�
	 */
	virtual void SetTag(int tag);
	
	/**
	 * @breif ���W�̐ݒ�
	 * @return ����
	 */
	Collision* SetPos(Vector3);

	/**
	 * @breif �傫���̐ݒ�
	 * @return ����
	 */
	Collision* SetSize(Vector3);

	/**
	 * @breif �^�O�̎擾
	 * @return �^�O�̐��l
	 */
	int GetTag();

public :
	/**
	 * @breif ���X�g�ɂ���S�ẴI�u�W�F�N�g���������Ă��邩���肷��
	 * @return �Ȃ�
	 */
	static void Check();

	/**
	 * @breif �o�E���f�B���O�{�b�N�X�ł̓����蔻��̔�r
	 * @return �������Ă����true
	 */
	static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);

	/**
	 * @breif �����蔻��̃��X�g�̏�����
	 * @return �Ȃ�
	 */
	static void Clear();
};

// EOF