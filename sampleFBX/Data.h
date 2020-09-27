/**
 * @file Data.h
 * @brief �f�[�^�̕ۑ��̃x�[�X
 */
#pragma once
#include <unordered_map>
#include <memory>
#include <wrl/client.h>

/**
 * @class �f�[�^�Ǘ��N���X
 */
template <typename T>
class Data
{
protected:
	std::unordered_map<int, std::unique_ptr<T>> m_data;	//!< �i�[��
	int m_GUID;								//!< �n�b�V���ƂȂ郆�j�[�NID

public:
	/**
	 * @brief �f�[�^�̃Z�b�g
	 * @param[in] num	���ʎq�܂��̓��j�[�NID
	 * @param[in] data	�ۑ����Ă��������f�[�^
	 * @return �Ȃ�
	 */
	void Set(int num, T* data) {
		m_GUID = num;
		std::unique_ptr<T> buf(data);
		m_data[m_GUID] = std::move(buf);
	}

public:
	/**
	 * @brief �f�[�^�̎擾
	 * @param[in] id �f�[�^���Z�b�g�����Ƃ��̎��ʎq�܂��̓��j�[�NID
	 * @return �f�[�^
	 */
	T* Get(int id) {
		return m_data[id].get();
	}
};

/**
 * @class �f�[�^�Ǘ��N���X�iDirectX��p�j
 */
template <typename T>
class DXData
{
protected:
	std::unordered_map<int, Microsoft::WRL::ComPtr<T>> m_data;	//!< �i�[��
	int m_GUID;								//!< �n�b�V���ƂȂ郆�j�[�NID

public:
	/**
	 * @brief �f�[�^�̃Z�b�g
	 * @param[in] num	���ʎq�܂��̓��j�[�NID
	 * @param[in] data	�ۑ����Ă��������f�[�^
	 * @return �Ȃ�
	 */
	void Set(int num, T* data) {
		m_GUID = num;
		Microsoft::WRL::ComPtr<T> buf;
		buf.Attach(data);
		m_data[m_GUID] = buf;
	}

public:
	/**
	 * @brief �f�[�^�̎擾
	 * @param[in] id �f�[�^���Z�b�g�����Ƃ��̎��ʎq�܂��̓��j�[�NID
	 * @return �f�[�^
	 */
	T* Get(int id) {
		return m_data[id].Get();
	}
};

// EOF