/**
 * @file Data.h
 * @brief データの保存のベース
 */
#pragma once
#include <unordered_map>
#include <memory>
#include <wrl/client.h>

/**
 * @class データ管理クラス
 */
template <typename T>
class Data
{
protected:
	std::unordered_map<int, std::unique_ptr<T>> m_data;	//!< 格納先
	int m_GUID;								//!< ハッシュとなるユニークID

public:

	void Set(int num, T* data) {
		m_GUID = num;
		std::unique_ptr<T> buf(data);
		m_data[m_GUID] = std::move(buf);
	}

public:
	T* Get(int id) {
		return m_data[id].get();
	}
};

/**
 * @class データ管理クラス（DirectX専用）
 */
template <typename T>
class DXData
{
protected:
	std::unordered_map<int, Microsoft::WRL::ComPtr<T>> m_data;	//!< 格納先
	int m_GUID;								//!< ハッシュとなるユニークID

public:

	void Set(int num, T* data) {
		m_GUID = num;
		Microsoft::WRL::ComPtr<T> buf;
		buf.Attach(data);
		m_data[m_GUID] = buf;
	}

public:
	T* Get(int id) {
		return m_data[id].Get();
	}
};


// EOF