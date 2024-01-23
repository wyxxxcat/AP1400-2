#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include<bits/stdc++.h>
#include<memory>

template<typename T>
class UniquePtr
{
private:
    T* p;
public:
    UniquePtr() :p(nullptr) {}
    UniquePtr(T* p_) :p(p_) {}
    UniquePtr(std::unique_ptr<T> p_) :p(p_.release()) {}
    operator bool()
    {
        return p != nullptr && *p != 0;
    }
    T& operator*() const
    {
        return *p;
    }
    T* get() const
    {
        return p;
    }
    T* operator->()
    {
        return p;
    }
    void reset()
    {
        this->p = nullptr;
    }
    void reset(T* p_)
    {
        this->p = p_;
        p_ = nullptr;
    }
    T* release()
    {
        T* ptr = p;
        p = nullptr;
        return ptr;
    }
};
#endif //UNIQUE_PTR