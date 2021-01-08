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
#include <list>
#include <memory>

/**
 * @class CollisionManager
 * @brief �����蔻��Ǘ��N���X
 */
class CollisionManager:public Singleton<CollisionManager>
{
private:
	LinerOctreeManager<Collision> m_CollisionTree;
	std::list<std::unique_ptr<TreeRegisterObject<Collision>>> m_registList;
public:
	friend class Singleton<CollisionManager>;		//!< �V���O���g���N���X�ł̐������\��

	void Init();

	void Uninit();

	/**
	 * @breif ���X�g�ɂ���S�ẴI�u�W�F�N�g���������Ă��邩���肷��
	 * @return �Ȃ�
	 */
	void Check();

	void Set(Collision* col);

	bool CheckOBB(const Transform & myObj, const Transform & othorObj, Collision * myCol, Collision * othorCol);
	
	/**
	 * @breif �o�E���f�B���O�{�b�N�X�ł̓����蔻��̔�r
	 * @return �������Ă����true
	 */
	//static bool CheckBox(Vector3 mypos, Vector3 halfsize, Vector3 othorPos, Vector3 othorhalsize);

	bool CheckOBB(const Transform& myObj, const Transform& othorObj);

	static Vector3 GetSize(const Transform& trans);
};

// EOF