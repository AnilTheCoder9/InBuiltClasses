#include <iostream>
#include <utility> // For std::swap
#include <cstddef> // For std::nullptr_t

template<typename T>
class MyUniquePtr
{
private:
    T* m_ptr;                                                                  //Member variable
public:
    MyUniquePtr() noexcept : m_ptr(nullptr) {}                                 // Default constructor

    explicit MyUniquePtr(T* ptr) noexcept : m_ptr(ptr) {}                      // Parameterized constructor            

    // Delete copy constructor and copy assignment operator
    MyUniquePtr(const MyUniquePtr& other) = delete;
    MyUniquePtr& operator=(const MyUniquePtr& other) = delete;

    MyUniquePtr(MyUniquePtr&& other) noexcept : m_ptr(other.m_ptr)               // Move constructor
    {
        other.m_ptr = nullptr;
    }

    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept                          // Move assignment operator
    {
        if (this == &other)
            return *this;

        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
        return *this;
    }

    T* get() const noexcept { return m_ptr; }                                      // Get the raw pointer

    T* release() noexcept                                                          // Release ownership of the pointer
    {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    T& operator*() const { return *m_ptr; }                                        // Dereference operator

    T* operator->() const { return m_ptr; }                                        // Arrow operator

    void reset(T* ptr = nullptr) noexcept                                          // Reset the pointer
    {
        if (m_ptr != ptr)
        {
            delete m_ptr;
            m_ptr = ptr;
        }
    }

    void swap(MyUniquePtr& other) noexcept                                         // Swap with another MyUniquePtr
    {
        std::swap(m_ptr, other.m_ptr);
    }

    explicit operator bool() const noexcept { return m_ptr != nullptr; }           // Conversion to bool

    ~MyUniquePtr() noexcept                                                        // Destructor
    {
        delete m_ptr;
    }
};
