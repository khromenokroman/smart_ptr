#pragma once
#include <fmt/format.h>

#include <memory>

namespace memory::unique_ptr {
template <typename Type, typename Deleter = ::std::default_delete<Type>>
class UniquePtr {
   public:
    explicit UniquePtr(Type* pointer = nullptr, Deleter deleter = Deleter()) : m_data{pointer}, m_deleter{deleter} {};
    ~UniquePtr() { reset(nullptr); }

    UniquePtr(UniquePtr const&) = delete;
    UniquePtr(UniquePtr&&) = default;
    UniquePtr& operator=(UniquePtr const&) = delete;
    UniquePtr& operator=(UniquePtr&&) = default;

    /*
     * старый очищаем, новый забираем
     */
    void reset(Type* pointer) {
        if (m_data) {
            m_deleter(m_data);
            m_data = pointer;
        } else {
            m_data = pointer;
        }
    }
    /*
     * отдаем указатель, мы не владеем
     */
    Type* relese() {
        auto tmp_pointer = m_data;
        m_data = nullptr;
        return tmp_pointer;
    }
    Type* get() { return m_data; }
    /*
     * замена
     */
    void swap(UniquePtr<Type>& other) {
        Type* tmp_other = other.relese();
        other.reset(this->relese());
        reset(tmp_other);
    }
    Type& operator*() { return *m_data; }
    Type* operator->() { return m_data; }
    explicit operator bool() { return get() != nullptr; }

   private:
    static_assert(sizeof(Deleter) == 1);
    Type* m_data = nullptr; // 8
    Deleter m_deleter;      // 1
};
} // namespace memory::unique_ptr
