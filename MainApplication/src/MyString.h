
#include <iostream>

class MyString
{
private:
	char* m_ptr;
	size_t m_size;
	size_t m_capacity;


	size_t calculateLength(char* ptr)
	{
		if (!ptr)
			return 0;

		size_t size = 0;
		int i = 0;
		while (ptr[i++] != '\0')
			++size;

		return size;
	}

public:
	//Default constructor
	MyString() : m_ptr(nullptr), m_size(0), m_capacity(0) {}

	//parameterized constructor
	MyString(char* ptr)
	{
		if (ptr)
		{
			m_size = calculateLength(ptr);

			m_capacity = m_size * 2;

			m_ptr = new char[m_capacity];

			int i = 0;
			while (ptr[i] != '\0')
				m_ptr[i] = ptr[i++];

			m_ptr[m_size] = '\0';

		}
	}

	//copy constructor
	MyString(const MyString& other) : m_size(other.m_size), m_capacity(other.m_capacity)
	{
		if (other.m_ptr)
		{
			m_ptr = new char[m_capacity];

			int i = 0;
			while (other.m_ptr[i] != '\0')
				m_ptr[i] = other.m_ptr[i++];

			m_ptr[i] = '\0';
		}

	}

	//Copy assignment operator
	MyString& operator=(const MyString& other)
	{
		if (this == &other)
			return *this;

		if (m_ptr)
			delete m_ptr;

		m_size = other.m_size;
		m_capacity = other.m_capacity;

		if (other.m_ptr)
		{
			m_ptr = new char[m_capacity];

			int i = 0;
			while (other.m_ptr[i] != '\0')
				m_ptr[i] = other.m_ptr[i++];

			m_ptr[i] = '\0';
		}
		return *this;
	}

	//Destructor
	~MyString()
	{
		if (m_ptr)
			delete[] m_ptr;
	}
};
