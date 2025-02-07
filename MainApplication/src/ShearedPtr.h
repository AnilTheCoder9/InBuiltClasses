#include <iostream>                                                                         

template<typename T>
class MySharedPtr                      //Standard include library
{
private:
    T* m_ptr;                          // Raw pointer to the managed object
    int* m_ref;                        // Reference count pointer


    void release()                      // Helper function to release ownership and manage deletion
    {
        if (m_ptr && --(*m_ref) == 0)
        {
            delete m_ptr;              // Delete the managed object
            delete m_ref;              // Delete the reference count
        }
    }

public:
    MySharedPtr() : m_ptr(nullptr), m_ref(new int(0)) {}                                   // Default constructor

    explicit MySharedPtr(T* ptr) : m_ptr(ptr), m_ref(new int(1)) {}                        // Parameterized constructor

    MySharedPtr(const MySharedPtr& other)                                                  // Copy constructor
    {
        m_ptr = other.m_ptr;
        m_ref = other.m_ref;
        if (m_ptr)
        {
            ++(*m_ref);                // Increment reference count
        }
    }

    MySharedPtr(MySharedPtr&& other) noexcept : m_ptr(other.m_ptr), m_ref(other.m_ref)     // Move constructor
    {
        other.m_ptr = nullptr;
        other.m_ref = nullptr;
    }

    MySharedPtr& operator=(const MySharedPtr& other)                                       // Copy assignment operator
    {
        if (this != &other)
        {
            release();                 // Release the current resource

            m_ptr = other.m_ptr;
            m_ref = other.m_ref;

            if (m_ptr)
            {
                ++(*m_ref);            // Increment reference count
            }
        }
        return *this;
    }

    MySharedPtr& operator=(MySharedPtr&& other) noexcept                                   // Move assignment operator
    {
        if (this != &other)
        {
            release();                 // Release the current resource

            m_ptr = other.m_ptr;
            m_ref = other.m_ref;

            other.m_ptr = nullptr;
            other.m_ref = nullptr;
        }
        return *this;
    }

    T* Get() const { return m_ptr; }                                                       // Get the raw pointer

    void Reset(T* ptr = nullptr)                                                           // Reset the raw pointer
    {
        release();                     // Release the current resource
        m_ptr = ptr;
        m_ref = ptr ? new int(1) : new int(0);  // Reset reference count
    }

    T& operator*() const                                                                   // Dereference operator
    {
        if (!m_ptr)
        {
            throw std::runtime_error("Dereferencing a null pointer");
        }
        return *m_ptr;
    }

    T* operator->() const                                                                  // Arrow operator
    {
        return m_ptr;
    }

    int use_count() const                                                                  // Return reference count
    {
        return *m_ref;
    }

    ~MySharedPtr()                                                                         // Destructor
    {
        release();
    }
};
#pragma once
