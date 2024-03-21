#include "vector.h"

template <typename T>
inline vector<T>::vector()
{
    list.next=nullptr;
    
}

template <typename T>
vector<T>::~vector()
{
}

template <typename T>
int vector<T>::size()
{
    return _size;
}

template <typename T>
void vector<T>::push_back(T value)
{
    
}

template <typename T>
T *vector<T>::operator[](int idx)
{
    list * it;
    for(int i=0;i<=idx;i++){

    }
}
