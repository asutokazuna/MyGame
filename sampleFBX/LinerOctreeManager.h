/**
 * @file LinerOctreeManager
 * @brief �����؂̊Ǘ�������
 */
#pragma once
#include "MyMath.h"
#include <Windows.h>
#include <vector>
#include <list>

#define OCTREE_MAX_LEVEL (7)

template <class T>
class OctreeCell;

/**
 * @class TreeRegisterObject
 * @brief ���؂ɓo�^����o�������X�g�I�u�W�F�N�g
 */
template <class T>
class TreeRegisterObject
{
public:
	OctreeCell<T> *m_cell;		//!< �o�^����Ă�����
	T* m_object;				//!< �o�^���Ă���I�u�W�F�N�g
	TreeRegisterObject<T> *m_pre;	//!< �O�̃I�u�W�F�N�g
	TreeRegisterObject<T> *m_next;	//!< ���̃I�u�W�F�N�g
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	TreeRegisterObject()
	{
		m_cell = NULL;
		m_object = NULL;
		m_pre = NULL;
		m_next = NULL;
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~TreeRegisterObject() 
	{
	}

	/**
	 * @brief �o�^���Ă��郊�X�g����폜
	 * @return �폜�����true,���ɍ폜����Ă����false
	 */
	bool Remove()
	{
		if (m_cell == NULL) {
			return false;
		}

		if (m_cell->OnRemove(this) == NULL) {
			return false;
		}

		// �폜����
		if (m_pre != NULL)
		{
			m_pre->m_next = m_next;
			m_pre = NULL;
		}
		if (m_next != NULL)
		{
			m_next->m_pre = m_pre;
			m_next = NULL;
		}
		m_cell = NULL;
		return true;
	}

	/**
	 * @brief ��Ԃ�o�^
	 * @param[in] cell �o�^������
	 * @return �Ȃ�
	 */
	void RegistCell(OctreeCell<T>* cell)
	{
		m_cell = cell;
	}

	TreeRegisterObject<T>* GetNextObj()
	{
		return m_next;
	}
};

/**
 * @class LinerOctreeManager
 * @brief ���`8���؊Ǘ��N���X
 */
template <class T>
class LinerOctreeManager
{
protected:
	OctreeCell<T> **m_ppCellList;		//!< ���`��ԃ|�C���^���X�g
	unsigned int m_pow[OCTREE_MAX_LEVEL + 1];		//!< �ׂ��搔�l�z��
	Vector3 m_size;		//!< ��
	Vector3 m_minSize;	//!< �̈�̍ŏ��̈ʒu
	Vector3 m_maxSize;	//!< �̈�̍ő�̈ʒu
	Vector3 m_unitSize;	//!< �ŏ���Ԃ̑傫��
	DWORD m_cellNum;	//!< ��Ԃ̐�
	unsigned int m_level;	//!< ���x��
public:
	/**
	 * @brief �R���X�g���N�^
	 */
	LinerOctreeManager()
	{
		m_size.x = m_size.y = m_size.z = 1.0f;
		m_minSize.x = m_minSize.y = m_minSize.z = 1.0f;
		m_maxSize.x = m_maxSize.y = m_maxSize.z = 1.0f;
		m_unitSize.x = m_unitSize.y = m_unitSize.z = 1.0f;
		m_cellNum = 0;
		m_level = 0;
		m_ppCellList = NULL;
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~LinerOctreeManager()
	{
		DWORD i;
		for (i = 0; i < m_cellNum; i++)
		{
			if (m_ppCellList[i] != NULL) {
				delete m_ppCellList[i];
			}
		}
		delete[] m_ppCellList;
	}

	/**
	 * @brief ����������
	 * @param[in] level	��ԃ��x��
	 * @param[in] min	��Ԃ̍ŏ��l(�ŏ��[)
	 * @param[in] man	��Ԃ̍ő�l(�ő�[)
	 * @return �쐬�ɐ��������true(��ԃ��x�����ݒ�ő�𒴂����Ƃ�false)
	 */
	bool Init(unsigned int level, Vector3& min, Vector3& max)
	{
		// �ݒ背�x�����傫����΍쐬���Ȃ�
		if (level >= OCTREE_MAX_LEVEL) {
			return false;
		}

		int i;
		m_pow[0] = 1;
		for (i = 1; i < OCTREE_MAX_LEVEL + 1; i++) {
			m_pow[i] = m_pow[i - 1] * 8;
		}

		// Level�̔z��쐬(���`)
		m_cellNum = (m_pow[level + 1] - 1) / 7;
		m_ppCellList = new OctreeCell<T>*[m_cellNum];
		for (i = 0; i < m_cellNum; i++)
		{
			m_ppCellList[i] = NULL;
		}
		//ZeroMemory(m_ppCellList, sizeof(OctreeCell<T>*) * m_cellNum);

		// �̈�o�^
		m_minSize = min;
		m_maxSize = max;
		m_size = m_maxSize - m_minSize;
		m_unitSize = m_size / ((float)(1 << level));

		m_level = level;

		return true;
	}

	/**
	 * @brief �I�u�W�F�N�g��o�^����
	 * @param[in] min �I�u�W�F�N�g�̍ŏ��ʒu
	 * @param[in] max �I�u�W�F�N�g�̍ő�ʒu
	 * @param[in] obj �o�^����I�u�W�F�N�g
	 */
	bool Regist(Vector3 min, Vector3 max, TreeRegisterObject<T>* obj)
	{
		// �o�^���[�g���ԍ����Z�o
		DWORD elem = GetMortonNumber(min, max);
		if (elem < m_cellNum)
		{
			if (m_ppCellList[elem] == NULL) {
				CreateNewCell(elem);
			}
			return m_ppCellList[elem]->Push(obj);
		}
		return false;
	}

	DWORD GetAllCollisionList(std::vector<T*> &colVect)
	{
		colVect.clear();

		// ��Ԃ���������Ă��邩�`�F�b�N
		if (m_ppCellList[0] == NULL) {
			return 0;	
		}

		std::list<T*> colStac;
		GetCollisionList(0, colVect, colStac);

		return (DWORD)colVect.size();
	}

protected:
	/**
	 * @brief ��ԓ��ł̏Փ˃��X�g���쐬����
	 */
	bool GetCollisionList(DWORD elem, std::vector<T*> &colVect, std::list<T*> &colstac)
	{
		typename std::list<T*>::iterator it;

		// ��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
		TreeRegisterObject<T> *objList = m_ppCellList[elem]->GetFirstObj();
		while (objList != NULL)
		{
			TreeRegisterObject<T> *othorObjList = objList->m_next;
			while (othorObjList != NULL)
			{
				colVect.push_back(objList->m_object);
				colVect.push_back(othorObjList->m_object);
				othorObjList = othorObjList->m_next;
			}
			// �Փ˃X�^�b�N(�e�I�u�W�F�N�g)�Ƃ̏Փ˃��X�g���쐬
			for (it = colstac.begin(); it != colstac.end(); it++)
			{
				colVect.push_back(objList->m_object);
				colVect.push_back(*it);
			}
			objList = objList->m_next;
		}

		bool childFlg = false;
		// �q��Ԃֈړ�
		DWORD objNum = 0;
		DWORD i, nextElem;
		for (i = 0; i < 4; i++)
		{
			nextElem = elem * 4 + 1 + i;
			if (nextElem < m_cellNum && m_ppCellList[elem * 4 + 1 + i])
			{
				if (childFlg == false)
				{
					objList = m_ppCellList[elem]->GetFirstObj();
					while (objList != NULL)
					{
						colstac.push_back(objList->m_object);
						objNum++;
						objList = objList->m_next;
					}
				}
				childFlg = true;
				GetCollisionList(elem * 4 + 1 + i, colVect, colstac);
			}
		}

		// �X�^�b�N����I�u�W�F�N�g���O��
		if (childFlg == true)
		{
			for (i = 0; i < objNum; i++) {
				colstac.pop_back();
			}
		}
		return true;
	}

	/**
	 * @brief ��Ԃ𐶐�
	 * @return true,���s�Ŗ������[�v
	 */
	bool CreateNewCell(DWORD elem)
	{
		while (m_ppCellList[elem] == NULL)
		{
			m_ppCellList[elem] = new OctreeCell<T>;

			elem = (elem - 1) >> 3;
			if (elem >= m_cellNum) {
				break;
			}
		}

		return true;
	}

	/**
	 * @brief ���W�����Ԕԍ�(���[�g���ԍ�)���Z�o
	 * @param[in] min ���W�̍ŏ��l 
	 * @param[in] max ���W�̍ő�l 
	 * @return �Z�o������Ԕԍ�(���[�g���ԍ�)
	 */
	DWORD GetMortonNumber(Vector3& min, Vector3& max)
	{
		// �ŏ����x���ɂ�����e���ʒu���Z�o
		DWORD LT = GetPointElem(min);
		DWORD RB = GetPointElem(max);

		// ��Ԕԍ��������Z���čŏ�ʋ�؂肩�珊�����x�����Z�o
		DWORD def = RB ^ LT;
		unsigned int HiLevel = 1;
		unsigned int i;
		for (i = 0; i < m_level; i++)
		{
			DWORD check = (def >> (i * 3)) & 0x7;
			if (check != 0) {
				HiLevel = i + 1;
			}
		}
		DWORD spaceNum = RB >> (HiLevel * 3);
		DWORD addNum = (m_pow[m_level - HiLevel] - 1) / 7;
		spaceNum += addNum;

		if (spaceNum > m_cellNum) {
			return 0xffffffff;
		}

		return spaceNum;
	}

	/**
	 * @brief �r�b�g�����֐�
	 * @details ���[�g���ԍ��ɂ��邽�߂ɐ��l���r�b�g�V�t�g����
	 */
	DWORD BitSeparateFor3D(BYTE n)
	{
		DWORD s = n;
		s = (s | s << 8) & 0x0000f00f;
		s = (s | s << 4) & 0x000c30c3;
		s = (s | s << 2) & 0x00249249;
		return s;
	}

	/**
	 * @brief 3D���[�g����Ԕԍ��Z�o�֐�
	 */
	DWORD Get3DMortonNumber(BYTE x, BYTE y, BYTE z)
	{
		return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
	}

	/**
	 * @brief ���W������`�����ؗv�f�ԍ��ϊ��֐�
	 * @param[in] pos ���W
	 * @return �ϊ��������[�g���ԍ�
	 */
	DWORD GetPointElem(Vector3& pos)
	{
		return Get3DMortonNumber(
			(BYTE)((pos.x - m_minSize.x) / m_unitSize.x),
			(BYTE)((pos.y - m_minSize.y) / m_unitSize.y),
			(BYTE)((pos.z - m_minSize.z) / m_unitSize.z)
			);
	}
};

/**
 * @class OctreeCell
 * @brief ���؂�1�̋�ԃN���X
 */
template <class T>
class OctreeCell
{
protected:
	TreeRegisterObject<T> *m_objList;	//!< �I�u�W�F�N�g�̃��X�g

public:
	/**
	 * @brief �R���X�g���N�^
	 */
	OctreeCell()
	{
		m_objList = NULL;
	}

	/**
	 * @brief �f�X�g���N�^
	 */
	virtual ~OctreeCell()
	{
		if (m_objList != NULL) {
			ResetLink(m_objList);
		}
	}

	/**
	 * @brief �����N��S�ď���
	 * @return �Ȃ�
	 */
	void ResetLink(TreeRegisterObject<T> *objList)
	{
		if (objList->m_next != NULL) {
			ResetLink(objList->m_next);
		}
		objList = NULL;
	}

	/**
	 * @brief �I�u�W�F�N�g����Ԃ̃��X�g�ɃZ�b�g
	 * @param[in] obj �o�^����I�u�W�F�N�g
	 * @return �Ȃ�
	 */
	bool Push(TreeRegisterObject<T> *obj)
	{
		if (obj == NULL) {
			return false;
		}
		if (obj->m_cell == this) {
			return false;
		}

		if (m_objList == NULL) {
			m_objList = obj;
		}
		else
		{
			obj->m_next = m_objList;
			m_objList->m_pre = obj;
			m_objList = obj;
		}
		obj->RegistCell(this);

		return true;
	}

	TreeRegisterObject<T> *GetFirstObj()
	{
		return m_objList;
	}

	bool OnRemove(TreeRegisterObject<T> *RemoveObj)
	{
		if (m_objList == RemoveObj)
		{
			if (m_objList != NULL) {
				m_objList = m_objList->GetNextObj();
			}
		}
		return true;
	}
};

// EOF