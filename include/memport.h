#pragma once

#include <mutex>

namespace tinymemport
{
	template <typename T>
	class TDataPort
	{
	public:
		static_assert(std::is_default_constructible<T>::value, "DataType must be default-constructible");
		static_assert(std::is_assignable<T, T>::value, "DataType must be a assignable");

		TDataPort() : m_guard(), m_data_p()
		{
			std::lock_guard<std::mutex> lock(m_guard);
			m_data_p = new (std::nothrow) T;
		}
		~TDataPort()
		{
			std::lock_guard<std::mutex> lock(m_guard);
			delete m_data_p;
		}

		void setData(const T f_outputData)
		{
			std::lock_guard<std::mutex> lock(m_guard);
			if (m_data_p != nullptr)
			{
				*m_data_p = f_outputData;
			}
		}

		bool hasData()
		{
			std::lock_guard<std::mutex> lock(m_guard);
			return (m_data_p != nullptr);
		}

		T *getData()
		{
			std::lock_guard<std::mutex> lock(m_guard);
			return m_data_p;
		}

	private:
		std::mutex m_guard;
		T *m_data_p;
	};
} // namespace tinymemport