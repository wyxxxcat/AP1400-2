#ifndef SHARED_PTR
#define SHARED_PTR
#include<iostream>
#include<memory>
template<typename T>
class SharedPtr
{
    
public:
    SharedPtr():p(nullptr) {
        cnt = new size_t(0);
    }
    SharedPtr(T* p_) {
        cnt = new size_t(1);
        p = p_;
    }
    SharedPtr(SharedPtr<T>& ptr) {
        ++ (*ptr.cnt);
        cnt = ptr.cnt;
        p = ptr.p;
    }
    SharedPtr(std::shared_ptr<T> ptr) {
        cnt = new size_t(1);
        p = new T{*ptr.get()};
    }
    ~SharedPtr()
    {
        p = nullptr;
        *cnt = std::max(*cnt-1,size_t(0));
    }
    operator bool()
    {
        return p != nullptr && *p != 0;
    }
    T& operator*()
    {
        return *p;
    }
    T* operator->()
    {
        return p;
    }
    size_t length()
    {
        return sizeof(*p);
    }
    bool empty()
    {
        return p == nullptr;
    }
    void reset()
    {
        *cnt = 0;
        p = nullptr;
    }
    void reset(T* p_)
    {
        p = p_;
    }
    T* get()
    {
        return p;
    }
    size_t use_count()
    {
        if(cnt)
        {
            return *cnt;
        }else
        {
            return 0;
        }
    }
    SharedPtr& operator=(SharedPtr& ptr)
    {
        if(this != &ptr) ++(*ptr.cnt);
        cnt = ptr.cnt;
        p = ptr.p;
        return ptr;
    }
    T* p;
    size_t* cnt = nullptr;
};
#endif //SHARED_PTR