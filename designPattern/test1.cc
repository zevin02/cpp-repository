#include <iostream>
using namespace std;

// 设计一个类，智能在堆上创建对象
class HeapOnly
{
private:
    int _a;

private:
    HeapOnly() // 1.把构造函数私有化
    {
    }
    HeapOnly(const HeapOnly &cp) = delete; // 直接禁止使用拷贝构造
    HeapOnly &operator=(const HeapOnly &cp) = delete;

public:
    static HeapOnly *createobj() // 在类里面弄一个获得对象的方法
    {
        return new HeapOnly;
    }
};

void TestHeapOnly()
{
    // 正常的一个类可以在任何地方，栈上，堆上，静态区都可以
    /*
        1.需要把正常创建对象的渠道给封掉,
        *1.构造函数给私有化
        *2.拷贝构造也要私有化
    */
    // HeapOnly ho1;//不能使用,因为我们把构造函数给私有化了，所以不能弄
    // HeapOnly *pp=new HeapOnly;//这样也不行，因为他还是会调用构造函数，如果调用了构造函数，说明他还是可以在栈上开辟
    HeapOnly *ptr = HeapOnly::createobj();
    // HeapOnly copy(*ptr);
}

// 只能在栈上开辟
class StackOnly
{
public:
    static StackOnly creatobj()
    {
        return StackOnly(); // 构造一个临时对象，移动构造在有指针的类中才有用
    }
    // 不能把拷贝构造给封掉，因为上面创建临时对象也是通过拷贝构造的对象返回，
    // 同时拷贝构造还能够创建栈上对象

    // 所以我们可以把new给去掉
    void *operator new(size_t a) = delete;  // 直接禁止使用
    void operator delete(void *p) = delete; // 把指针传进来的delete给删除掉

private:
    int _a;
    StackOnly()
    {
    }
};

void TestStackOnly()
{
    // StackOnly* ho=new StackOnly;//这样就不能用了，因为构造函数死有
    StackOnly h = StackOnly::creatobj();
    // 这里有一个bug
    //  StackOnly* ptr=new StackOnly(h);//new的对象是通过拷贝构造，而不是构造函数
}

// 设计一个类，不能被拷贝
class CopyBan
{
private:
    CopyBan(const CopyBan &cb) = delete;
    CopyBan &operator=(const CopyBan &cb) = delete;
};

// 设计一个类不能被继承,使用final关键字，就不能够被继承
class A final
{
};
#include <vector>

// 单例模式，全局只有一个对象
// 全局只有一个对象，并且可以很方便的使用
// 这样操作就没有链接的问题

namespace hungry
{

    // 饿汉模式：就是提前准备好，我随时都可以使用，

    class CallInof
    {
    private:
        int _cnt;
        vector<pair<int, int>> _v;
        static CallInof _inst; // 在类里面只是声明一个对象，但是要在类外外面进行定义,所以之后使用的都是这个对象
        // 在类里面定义一个同一个对象必须定义成静态的，否则就会无限递归下去
        // 因为这个对象并不属于这个类,可以想象成定义了一个全局的对象，只不过他被限定在一个类域里面了

        CallInof()
            : _cnt(0)
        {
        }
        // 把拷贝构造给禁止使用

        CallInof(const CallInof &c) = delete;

    public:
        static CallInof &GetInstance()
        {
            // 获取单例
            // 或者使用指针也可以
            return _inst; // 因为这个对象出了作用领域还存在，所以使用传引用返回
        }
        void AddCallCnt(int n)
        {
            _cnt += n;
        }
    };
    CallInof CallInof::_inst; // 在类外面进行定义,在程序入口之前就进行了初始化,main函数之前就创建了，所以没有线程安全的问题
    // 简单

    // 缺点：无法控制单力创建初始化的顺序
    // 如果单例对象初始化很费时间，会导致程序启动慢

};
#include <mutex>
namespace idle
{
    // 懒汉模式：在第一次访问的时候才创建单例对象
    // 一般情况下单例对象不考虑释放问题，
    class CallInof
    {
    private:
        int _cnt;
        vector<pair<int, int>> _v;
        static CallInof *_pinst; // 在懒汉中，使用的是指针
        static mutex _mtx;       // 多个线程要访问的是同一个锁，所以也要设置静态的
        CallInof()
            : _cnt(0)
        {
        }
        // 把拷贝构造给禁止使用

        CallInof(const CallInof &c) = delete;

    public:
        static CallInof *GetInstance()
        {
            // 获取单例
            // 或者使用指针也可以
            if (_pinst == nullptr) // 先进行大范围的判断，可以减少很多对锁的使用，如果已经不为空的话
            {

                unique_lock<mutex> lock(_mtx); // 加锁只是为了保护第一次创建对象
                if (_pinst == nullptr)
                {
                    //
                    // 如果这个对象为空，说明这个对象还没被创建出来，所以因为调用了，说明我们需要创建这个对象
                    _pinst = new CallInof;
                }
                // return *_pinst;//这个的话就需要传引用返回
            }
            return _pinst; // 因为这个对象出了作用领域还存在，所以使用传引用返回
        }
        static CallInof& GetInstance2()//出了作用域还存在的
        {
            //但是再c++98中，静态对象不能保证线程安全，C++11中对象初始化才是线程安全的

            static CallInof p;//第二种懒汉模式,很简单

            return p; // 因为这个对象出了作用领域还存在，所以使用传引用返回
        }
        void AddCallCnt(int n)
        {
            _cnt += n;
        }

        // 释放单例，我们可以使用一个内部类
        // 实现一个内嵌垃圾回收类

        class CGarbo
        {
        public:
            ~CGarbo()
            {
                if (_pinst)
                {
                    delete _pinst;
                    _pinst = nullptr;
                }
            }
        };
        static CGarbo gc;
    };
    CallInof *CallInof::_pinst = nullptr; // 在初始化的时候定义成空，在实际调用的时候才开辟空间
    mutex CallInof::_mtx;
    CallInof::CGarbo CallInof::gc; // 在外面定义这个对象,吸构函数就释放了
};

void TestSingleten()
{
    // 我们需要去统计次数
    hungry::CallInof::GetInstance().AddCallCnt(3); // 当例++
}

int main()
{
    TestHeapOnly();
    TestStackOnly();
    TestSingleten();
    return 0;
}