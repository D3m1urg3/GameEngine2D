#ifndef __GLOBALS__
#define __GLOBALS__

#include <algorithm>

#define DELETE(_ptr) delete _ptr, _ptr = nullptr

typedef unsigned int uint;

// Smart pointer with reference counting. Didn't want to use shared_ptr
template <class T>
class SharedPtr
{
public:
    // Constructor, destructor, and copy constructor
    explicit SharedPtr(T* p)
        try
        :_p(p),
        _pRefs(new uint(1))
    {}
    catch (...)
    {
        DELETE(p);
        DELETE(_pRefs);
        throw;
    }

    ~SharedPtr()
    {
        if (--*_pRefs == 0)
        {
            DELETE(_p);
            DELETE(_pRefs);
        }
    }

    SharedPtr(const SharedPtr& other)
        :_p(other._p),
        _pRefs(other._pRefs)
    {
        ++*_pRefs;
    }

    // Operators
    int& operator *  () const { return *_p; }

    int* operator -> () const { return _p; }

    SharedPtr& operator =  (SharedPtr& other)
    {
        other.swap(*this);
        return *this;
    }

    SharedPtr& operator = (T* otherPtr)
    {
        SharedPtr tmp(otherPtr);
        tmp.swap(*this);
        return *this;
    }

    // Other
    T* get() const { return _p; }
    bool isUnique() const { return *_pRefs == 1; }

    void swap(SharedPtr& other) noexcept
    {
        std::swap(_p, other._p);
        std::swap(_pRefs, other._pRefs);
    }

private:
    uint* _pRefs;
    T* _p;
};
// See: https://www.geeksforgeeks.org/smart-pointers-cpp/ 
// and http://lokiastari.com/blog/2015/01/15/c-plus-plus-by-example-smart-pointer-part-ii/

#endif
