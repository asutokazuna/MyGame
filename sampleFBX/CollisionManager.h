/**
 * @file CollisionManager
 * @brief �����蔻��Ǘ��N���X
 */
#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "LinerOctreeManager.h"
#include "collision.h"
#include "MyMath.h"

/**
 * @class CollisionManager
 * @brief �����蔻��Ǘ��N���X
 */
class CollisionManager:public Singleton<CollisionManager>
{
private:
	static std::unordered_map<int, Collision*> m_List;	//!< �R���C�_�[���X�g
	static LinerOctreeManager<Collision> m_CollisionTree;
public:
	friend class Singleton<CollisionManager>;		//!< �V���O���g���N���X�ł̐������\��

	void Init();

	/**
	 * @breif ���X�g�ɂ���S�ẴI�u�W�F�N�g���������Ă��邩���肷��
	 * @return �Ȃ�
	 */
	void Check();

	void Set(Collision* col);

	void Delete(Collision* col);

	/**
	 * @breif �o�E���f�B���O�{�b�N�X�ł̓����蔻��̔�r
	 * @return �������Ă����true
	 */
	//static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);

	static bool CheckOBB(const Transform& myObj, const Transform& othorObj);

	static Vector3 GetSize(const Transform& trans);

	/**
	 * @breif �����蔻��̃��X�g�̏�����
	 * @return �Ȃ�
	 */
	static void Clear();
};

// EOF