#include <utility>

template <class T>
class my_unique_ptr
{
    private:
    T* mPtr;
    public:
    T* get()
    {
        return mPtr;
    }
    void reset()
    {
        T *tmp = mPtr;
        mPtr = nullptr;
        delete tmp;
    }
    ~my_unique_ptr()
    {
        delete [] mPtr;
    }
    T operator*()
    {
        return *mPtr;
    }
    T* operator->()
    {
        return mPtr;
    }
    my_unique_ptr(T*&& ptr): mPtr(nullptr)
    {
        mPtr = std::move(ptr);
    }
    my_unique_ptr(): mPtr(nullptr)
    {
    }
    my_unique_ptr operator=(T*&& ptr)
    {
        mPtr = std::move(ptr);
    }
    my_unique_ptr(my_unique_ptr<T>&& uniPtr): mPtr(nullptr)
    {
        mPtr = uniPtr.mPtr;
        uniPtr.mPtr = nullptr;
    }
    my_unique_ptr operator=(my_unique_ptr<T>&& uniPtr)
    {
        mPtr = std::move(uniPtr.mPtr());
    }


    my_unique_ptr(const T ptr) = delete;
    my_unique_ptr(const T* ptr) = delete;
    my_unique_ptr(const T& ptr) = delete;
    my_unique_ptr(const my_unique_ptr<T>& uniPtr) = delete;
    my_unique_ptr operator=(const my_unique_ptr<T>& uniPtr) = delete;
};

template <class T>
my_unique_ptr<T> make_unique(T*&& data)
{
    return my_unique_ptr<T>( std::move(data) );
}
template <class T>
my_unique_ptr<T> make_unique(T& data)
{
    return my_unique_ptr<T>( std::move(data) );
}
