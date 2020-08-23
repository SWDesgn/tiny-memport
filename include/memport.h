#pragma once

#include <cstdint>
#include <mutex>

namespace tinymemport {
template <typename T>
class TDataPort {
 public:
  static_assert(std::is_default_constructible<T>::value,
                "DataType must be default-constructible");
  static_assert(std::is_assignable<T, T>::value,
                "DataType must be a assignable");

  TDataPort(uint16_t f_bufferBytes) : m_guard(), m_data_p() {
    std::lock_guard<std::mutex> lock(m_guard);
    m_rawMem_p = new (std::nothrow) char[sizeof(T) + f_bufferBytes];
    m_data_p = reinterpret_cast<T *>(m_rawMem_p);
    if (m_data_p != nullptr) {
      T t;
      *m_data_p = t;
    }
  }
  ~TDataPort() {
    std::lock_guard<std::mutex> lock(m_guard);
    delete[] m_rawMem_p;
    m_data_p = nullptr;
  }

  void setData(const T f_outputData) {
    std::lock_guard<std::mutex> lock(m_guard);
    if (m_data_p != nullptr) {
      *m_data_p = f_outputData;
    }
  }

  bool hasAlloc() {
    std::lock_guard<std::mutex> lock(m_guard);
    return (m_data_p != nullptr);
  }

  T *getData() {
    std::lock_guard<std::mutex> lock(m_guard);
    return m_data_p;
  }

 private:
  std::mutex m_guard;
  char *m_rawMem_p;
  T *m_data_p;
};
}  // namespace tinymemport