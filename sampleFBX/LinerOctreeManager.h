/**
 * @file LinerOctreeManager
 * @brief 八分木の管理をする
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
 * @brief 分木に登録する双方向リストオブジェクト
 */
template <class T>
class TreeRegisterObject
{
public:
	OctreeCell<T> *m_cell;		//!< 登録されている空間
	T* m_object;				//!< 登録しているオブジェクト
	TreeRegisterObject<T> *m_pre;	//!< 前のオブジェクト
	TreeRegisterObject<T> *m_next;	//!< 次のオブジェクト
public:
	/**
	 * @brief コンストラクタ
	 */
	TreeRegisterObject()
	{
		m_cell = NULL;
		m_object = NULL;
		m_pre = NULL;
		m_next = NULL;
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~TreeRegisterObject() 
	{
	}

	/**
	 * @brief 登録しているリストから削除
	 * @return 削除すればtrue,既に削除されていればfalse
	 */
	bool Remove()
	{
		if (m_cell == NULL) {
			return false;
		}

		if (m_cell->OnRemove(this) == NULL) {
			return false;
		}

		// 削除処理
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
	 * @brief 空間を登録
	 * @param[in] cell 登録する空間
	 * @return なし
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
 * @brief 線形8分木管理クラス
 */
template <class T>
class LinerOctreeManager
{
protected:
	OctreeCell<T> **m_ppCellList;		//!< 線形空間ポインタリスト
	unsigned int m_pow[OCTREE_MAX_LEVEL + 1];		//!< べき乗数値配列
	Vector3 m_size;		//!< 幅
	Vector3 m_minSize;	//!< 領域の最小の位置
	Vector3 m_maxSize;	//!< 領域の最大の位置
	Vector3 m_unitSize;	//!< 最小空間の大きさ
	DWORD m_cellNum;	//!< 空間の数
	unsigned int m_level;	//!< レベル
public:
	/**
	 * @brief コンストラクタ
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
	 * @brief デストラクタ
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
	 * @brief 初期化処理
	 * @param[in] level	空間レベル
	 * @param[in] min	空間の最小値(最小端)
	 * @param[in] man	空間の最大値(最大端)
	 * @return 作成に成功すればtrue(空間レベルが設定最大を超えたときfalse)
	 */
	bool Init(unsigned int level, Vector3& min, Vector3& max)
	{
		// 設定レベルより大きければ作成しない
		if (level >= OCTREE_MAX_LEVEL) {
			return false;
		}

		int i;
		m_pow[0] = 1;
		for (i = 1; i < OCTREE_MAX_LEVEL + 1; i++) {
			m_pow[i] = m_pow[i - 1] * 8;
		}

		// Levelの配列作成(線形)
		m_cellNum = (m_pow[level + 1] - 1) / 7;
		m_ppCellList = new OctreeCell<T>*[m_cellNum];
		for (i = 0; i < m_cellNum; i++)
		{
			m_ppCellList[i] = NULL;
		}
		//ZeroMemory(m_ppCellList, sizeof(OctreeCell<T>*) * m_cellNum);

		// 領域登録
		m_minSize = min;
		m_maxSize = max;
		m_size = m_maxSize - m_minSize;
		m_unitSize = m_size / ((float)(1 << level));

		m_level = level;

		return true;
	}

	/**
	 * @brief オブジェクトを登録する
	 * @param[in] min オブジェクトの最小位置
	 * @param[in] max オブジェクトの最大位置
	 * @param[in] obj 登録するオブジェクト
	 */
	bool Regist(Vector3 min, Vector3 max, TreeRegisterObject<T>* obj)
	{
		// 登録モートン番号を算出
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

		// 空間が生成されているかチェック
		if (m_ppCellList[0] == NULL) {
			return 0;	
		}

		std::list<T*> colStac;
		GetCollisionList(0, colVect, colStac);

		return (DWORD)colVect.size();
	}

protected:
	/**
	 * @brief 空間内での衝突リストを作成する
	 */
	bool GetCollisionList(DWORD elem, std::vector<T*> &colVect, std::list<T*> &colstac)
	{
		typename std::list<T*>::iterator it;

		// 空間内のオブジェクト同士の衝突リスト作成
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
			// 衝突スタック(親オブジェクト)との衝突リストを作成
			for (it = colstac.begin(); it != colstac.end(); it++)
			{
				colVect.push_back(objList->m_object);
				colVect.push_back(*it);
			}
			objList = objList->m_next;
		}

		bool childFlg = false;
		// 子空間へ移動
		DWORD objNum = 0;
		DWORD i, nextElem;
		for (i = 0; i < 8; i++)
		{
			nextElem = elem * 4 + 1 + i;
			if (nextElem < m_cellNum && m_ppCellList[elem * 8 + 1 + i])
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
				GetCollisionList(elem * 8 + 1 + i, colVect, colstac);
			}
		}

		// スタックからオブジェクトを外す
		if (childFlg == true)
		{
			for (i = 0; i < objNum; i++) {
				colstac.pop_back();
			}
		}
		return true;
	}

	/**
	 * @brief 空間を生成
	 * @return true,失敗で無限ループ
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
	 * @brief 座標から空間番号(モートン番号)を算出
	 * @param[in] min 座標の最小値 
	 * @param[in] max 座標の最大値 
	 * @return 算出した空間番号(モートン番号)
	 */
	DWORD GetMortonNumber(Vector3& min, Vector3& max)
	{
		// 最小レベルにおける各軸位置を算出
		DWORD LT = GetPointElem(min);
		DWORD RB = GetPointElem(max);

		// 空間番号を引き算して最上位区切りから所属レベルを算出
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
	 * @brief ビット分割関数
	 * @details モートン番号にするために数値をビットシフトする
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
	 * @brief 3Dモートン空間番号算出関数
	 */
	DWORD Get3DMortonNumber(BYTE x, BYTE y, BYTE z)
	{
		return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
	}

	/**
	 * @brief 座標から線形八分木要素番号変換関数
	 * @param[in] pos 座標
	 * @return 変換したモートン番号
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
 * @brief 分木の1つの空間クラス
 */
template <class T>
class OctreeCell
{
protected:
	TreeRegisterObject<T> *m_objList;	//!< オブジェクトのリスト

public:
	/**
	 * @brief コンストラクタ
	 */
	OctreeCell()
	{
		m_objList = NULL;
	}

	/**
	 * @brief デストラクタ
	 */
	virtual ~OctreeCell()
	{
		if (m_objList != NULL) {
			ResetLink(m_objList);
		}
	}

	/**
	 * @brief リンクを全て消す
	 * @return なし
	 */
	void ResetLink(TreeRegisterObject<T> *objList)
	{
		if (objList->m_next != NULL) {
			ResetLink(objList->m_next);
		}
		objList = NULL;
	}

	/**
	 * @brief オブジェクトを空間のリストにセット
	 * @param[in] obj 登録するオブジェクト
	 * @return なし
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