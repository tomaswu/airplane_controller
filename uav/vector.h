#ifndef VECTOR
#define VECTOR

template<typename T>
class Node{
    T data;
    Node *next{nullptr};
};


template<typename T>
class vector{

private:
    unsigned int _size;
    Node<T> *_head{nullptr};

public:
    vector();
    ~vector();
    int size();
    void push_back(T value);
    &T operator[](int idx);

};

#endif


