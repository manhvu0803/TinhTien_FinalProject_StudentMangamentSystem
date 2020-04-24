#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

namespace tt
{
    template <typename T> class vector
    {
        public:
            size_t initCapacity = 50;
            size_t capToIncrease = 50;
            // Constructor and destructor
            vector();
            ~vector();
            // Assignment
            vector<T>* operator=(vector<T>& vecToCopy);
            // Pointers
            T* begin();
            T* end();
            // Capacity
            size_t size() const;
            size_t capacity() const;
            // Access
            T operator[](size_t pos);
            T at(size_t pos);
            T front(size_t pos);
            T back(size_t pos);
            // Modifier
            void push_back(T value);
            void pop_back();

        private:
            T* ptr;
            size_t _capacity;
            size_t _size;
    };

    // Constructor
    template <typename T> vector<T>::vector()
    {
        _capacity = initCapacity;
        ptr = new T[_capacity];
        _size = 0;
    }

    // Destructor
    template <typename T> vector<T>::~vector()
    {
        delete [] ptr;
    }

    // Assignment
    template <typename T> vector<T>* vector<T>::operator=(vector<T>& vecToCopy)
    {
        delete [] ptr;

        _capacity = vecToCopy.capacity();
        _size = vecToCopy.size();
        ptr = new T[_size];
        memcpy(ptr, vecToCopy.ptr, sizeof(T) * _size);

        return this;
    }

    // Pointer
    template <typename T> inline T* vector<T>::begin()
    {
        return ptr;
    }

    template <typename T> inline T* vector<T>::end()
    {
        return ptr + _size;
    }

    // Capacity
    template <typename T> inline size_t vector<T>::size() const
    {
        return _size;
    }

    template <typename T> size_t vector<T>::capacity() const
    {
        return _capacity;
    }

    // Access
    template <typename T> inline T vector<T>::operator[](size_t pos)
    {
        return ptr[pos];
    }

    template <typename T> inline T vector<T>::at(size_t pos)
    {
        return ptr[pos];
    }

    // Modifier
    template <typename T> inline void vector<T>::push_back(T value)
    {
        ptr[_size] = value;
        ++_size;
    }

    template <typename T> inline void vector<T>::pop_back()
    {
        --_size;
    }
}

#endif // UTILITY_H_INCLUDED
