template <class T>
class my_unique_ptr
{
    private:
    T* ptr;
    public:
    T* get()
    {
        return ptr;
    }
};