/**
 * @file Collision
 * @brief �����蔻��N���X
 */
#pragma once
#include "Component.h"
#include <unordered_map>
#include "MyMath.h"
#include "Box.h"

// �O���錾
class Transform;

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
	Transform* m_transform;	//!< �e�̃g�����X�t�H�[��
	Vector3 m_offsetPos;		//!< �e����̃I�t�Z�b�g
	Vector3 m_offsetSize;		//!< �e����̃I�t�Z�b�g
	int id;			//!< ���j�[�NID
	int m_tag;		//!< ���ʃ^�O

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
	 * @breif ���f���̎�ސݒ�
	 * @param[in] kind ���f���̎��
	 * @return ����
	 */
	Collision* SetModelKind(int);

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