#include <iostream>
using namespace std;
#include <memory>
// RAII
//像指针一样使用
//还要写拷贝构造不然的话，就会浅拷贝，析构两次
namespace xzw
{
    template <class T>
    class auto_ptr
    {
    private:
        T *_ptr;

    public:
        //在构造函数
        auto_ptr(T *ptr)
            : _ptr(ptr) //原生指针支持拷贝
        {
        }
        ~auto_ptr()
        {
            if (_ptr)
            {
                cout << "delete" << endl;
                delete _ptr; //析构函数把他清理
            }
        }

        //如何解决拷贝问题,管理权转移，只有一个人析构它
        auto_ptr(auto_ptr<T> &sp)
            : _ptr(sp._ptr)
        {
            //资源转给你，
            //把管理权转移
            sp._ptr = nullptr; //自己置成空,自己没了，
        }

        T &operator*()
        {
            return *_ptr;
        }
        T *operator->() //返回原生指针即可
        {
            return _ptr;
        }
    };
};
void demo1()
{
    int *p1 = new int;
    xzw::auto_ptr<int> sp1(p1); //拷贝构造,出了作用域就调用他们的析构函数,抛异常的话也会出作用域，也就自动调用析构函数，
    int *p2 = new int;
    xzw::auto_ptr<int> sp2(sp1);     //拷贝构造
    xzw::auto_ptr<int> sp3(new int); //直接用new出来的资源给它
    *sp3 = 10;
    cout << __LINE__ << *sp3 << endl;
    cout << *sp1 << endl; //出现空指针问题
    //希望能够像指针一样使用，重载以下operator*

    //结论就是auto_ptr是一个失败的设计.很多公司明确要求不能使用auto_ptr
}

// c++11才更新智能指针的实现
// boost->scoped_ptr  shared_ptr   weak_ptr
// c++11->unique_ptr  shared_ptr   weak_ptr

namespace Uni_Ptr
{
    //原理简单粗暴，——防拷贝，直接不让你拷贝
    template <class T>
    class unique_ptr
    {
    private:
        T *_ptr;
        unique_ptr(const unique_ptr<T> &sp) = delete; //直接把它拷贝给弄掉
    public:
        //在构造函数
        unique_ptr(T *ptr)
            : _ptr(ptr) //原生指针支持拷贝
        {
        }
        ~unique_ptr()
        {
            if (_ptr)
            {
                cout << "delete" << endl;
                delete _ptr; //析构函数把他清理
            }
        }

        T &operator*()
        {
            return *_ptr;
        }
        T *operator->() //返回原生指针即可
        {
            return _ptr;
        }
    };
};
void demo2()
{
    Uni_Ptr::unique_ptr<int> sp1(new int);
    // Uni_Ptr::unique_ptr<int> sp2(sp1);
    // std::unique_ptr<int> sp(sp1);//不支持拷贝构造
}

//如果我需要拷贝怎么办呢
// shared_ptr就可以

//我们可以弄一个引用技术，最后一个管理的人把这个指针给析构掉
//只能有一个引用计数
//每次调用构造函数的时候引用计数就+1
//调用析构函数的时候，引用计数就-1，直到为0的时候就delete
//原理：记录有都少个对象管理这个资源，每个对象析构的时候--，最后一个管理的对象负责释放资源

namespace Shared_Ptr
{
    template <class T>
    class shared_ptr
    {
    private:
        T *_ptr;
        // static int _refcout; //这样就只有一个了,属于所有对象共享,但是要在类外面初始化，所以我们应该一个资源配一个引用计数，因为static是属于类的
        int *_pRefCount; //这个就是引用计数,凡是用浅拷贝都是要用引用计数，才能搞定这个东西
    public:
        //在构造函数,调用一次构造函数引用计数就加1
        shared_ptr(T *ptr)
            : _ptr(ptr), _pRefCount(new int(1)) //原生指针支持拷贝,用指针，不同的人就可以指向同一个资源

        {
            //只有第一个人会调用构造函数
            // _refcout=1;//就为1,管理不同的资源就会把别人的给修改了,
        }

        shared_ptr(const shared_ptr<T> &sp)            //调用拷贝构造
            : _ptr(sp._ptr), _pRefCount(sp._pRefCount) //引用计数也拷贝过去
        {
            // ++_refcout;
            // ++(*_pRefCount); //因为是同一个资源，所以就可以对它进行++，
            AddRef();
        }
        ~shared_ptr()
        {

            Release();
        }

        //如何解决拷贝问题,管理权转移，只有一个人析构它

        T &operator*()
        {
            return *_ptr;
        }
        T *operator->() //返回原生指针即可
        {
            return _ptr;
        }
        void Release()
        {
            (*_pRefCount)--; //析构的时候，把引用计数--
            if (!(*_pRefCount) && _ptr)
            {
                cout << "delete" << endl;
                delete _ptr; //析构函数把他清理
                delete _pRefCount;
                _ptr = nullptr;
                _pRefCount = nullptr;
                //delete是把原来对应的空间给释放掉,但是对应的指针还在堆区里面，所以还能用
            }
        }
        void AddRef()
        {
            (*_pRefCount)++;
        }
        shared_ptr<T> &operator=(const shared_ptr<T> &sp) //这个就牵扯到两个资源，
        {
            if (_ptr != sp._ptr) //自己给自己赋值
            {
                //原来的引用计数减一
                Release();
                _ptr = sp._ptr;//delete之后指针还在，指向不同的空间就行了
                _pRefCount = sp._pRefCount; //现在引用计数也要和其相等
                AddRef();
            }
            return *this;
        }
    };
    //这样是不行的
    // template<class T>
    // int shared_ptr<T>::_refcout=0;//在类外面初始化,要像声明一样操作
};

void demo3()
{
    Shared_Ptr::shared_ptr<int> sp(new int);
    Shared_Ptr::shared_ptr<int> sp1(sp);
    Shared_Ptr::shared_ptr<int> sp2(sp);
    Shared_Ptr::shared_ptr<int> sp3(sp);
    Shared_Ptr::shared_ptr<int> sp4(new int(3)); //这样就可以做到构造的对象就只析构一次
    sp1=sp4;
    sp2=sp4;
    sp=sp4;
    // sp3=sp4;

    //指向的堆上资源的线程安全的问题是访问的人处理的，智能指针不管
    //引用计数的线程安全问题是智能指针要处理的
    
    *sp4=3;
    *sp=4;


    cout<<(*sp3)<<endl;
    cout << __LINE__ << endl;
}

int main()
{
    // demo1();
    // demo2();
    demo3();
    return 0;
}