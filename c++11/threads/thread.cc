#include <iostream>
#include <thread>
using namespace std;
#include <mutex>
#include <atomic>
/*
    c++11的线程库可以跨平台
    thread里面的线程函数,只要是可调用对象都可以
    * 函数指针
    * lambda表达式(小函数用就行了)
    * 类对象的仿函数

*/

// demo1:两个线程对同一个变量进行++，堆上的和数据段上的数据都是共享的
//调用join就是会阻塞掉主线程，等线程都执行完之后才会放开主线程
// detach把它和主线程分离开来，后台回收

#if 0
int x = 0;
mutex mtx; //定义一个锁出来
void Func(int n)
{
    //每个线程都有自己的栈，各自在执行自己的func，
    mtx.lock();
    //不能放在里面，放在里面的话，每一次都要去竞争这个锁资源，
    //加在外面变成了串行，运行，就没有意义了，理论上应该加在里面，这样就能交替并行运行
    for (int i = 0; i < n; i++)
    {
        //放在这里锁的事情和释放也有消耗，
        //对用户态的切换，要保存上下文

        cout << std::this_thread::get_id() << "++x " << x << endl; //获得对应的线程id，这里是一个结构体，因为它可以跨平台

        //抢到锁的人执行的指令太少了，导致另一个人刚离开回去休息又回来了，而是在这里循环等待，一直问，好了我就进去执行，（自旋锁）
        ++x;
    }
    mtx.unlock();
}

#endif
//我们可以对这些数进行原子操作，不用锁

atomic<int> x(0); //这样对x的操作就变成了原子操作,不能用=
atomic_long m{0};//这两者是一样的
atomic<long> n(2);
void Func(int n)
{
    for (int i = 0; i < n; i++)
    {
        ++x;
    }
}
#define Lambda

#include <vector>

void threadpool()
{
    //实现一个线程池
    atomic<int> x(0);
    //我们实现一个n个线程都对它进行加m次
    int n, m;
    cin >> n >> m;
    vector<thread> vthds;
    vthds.resize(n); //我们直接就开n个线程，用thread的默认构造函数进行初始化，无参的，就不是不运行
    //这里还有还可以用移动构造和移动赋值
    atomic<int> costtime(0);
    for (size_t i = 0; i < vthds.size(); i++)
    {
        vthds[i] = thread([m, &x, &costtime]()
                          {
            int begin=clock();
            for(int i=0;i<m;i++)
            {
                x++;//这里的x是原子变量
            }
            int end=clock();
            costtime+=(end-begin); }); //这里我们用了移动赋值，构造了一个线程对象，线程里面用的是lambda表达式
    }
    for (auto &e : vthds)
    {
        if (e.joinable()) //判断是否可被join，
            e.join();     //这里必须要用&，如果不用的话，就会去掉拷贝构造，这是不允许的
    }
    cout << x << endl;
    cout << costtime << endl;
}
#include <ratio>
#include <chrono>

/*
void func(int& x)//绝对不能传左值引用
{
    x+=10;
}
*/

//解决方案1
/*
void func(int* x)//用指针肯定是可以的
{
    *x+=10;
}

*/

//解决方案2

void func(int &x) //绝对不能传左值引用
{
    x += 10;
}

template <class Lock>
class LockGuard
{
private:
    Lock& _lock;//&,const,和没有默认构造函数的变量，都必须在初始化列表进行初始化

public:
    LockGuard(Lock& lock)//在构造函数的时候就行加锁，但是互斥锁是不支持拷贝的，也要保持是同一把锁
    :_lock(lock)//这里的_lock是mtx的别名
    {
        _lock.lock();
    }
    ~LockGuard()
    {
        _lock.unlock();//在析构函数的时候进行解锁
    }
};

void vfunc(vector<int> &vt, int x, int base, mutex &mtx)
{
    try
    {
        /* code */
        if (base == 200)
        {
            //对应第一个线程就让他sleep一下
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        for (int i = 0; i < x; i++)
        {
            //用IO把速度降下来
            // mtx.lock(); //这样用锁有问题
            // LockGuard<mutex> lock(mtx);//在这个里面就加锁，出了for作用域就解锁了，抛异常也算出了作用域，也解锁了,调用析构函数，生命周期到了

            lock_guard<mutex> lock(mtx);//这个是库里面提供的

            unique_lock<mutex> lockk(mtx);//这个效果也是一样的,除了提供构造和析构，中途解一下锁

            //这个push失败之后就会抛异常

            vt.push_back(i); //有线程安全的问题

            //抛异常之后unlock就不会被执行了，这样可能在上面push里面开空间也会出现问题，所以我们这里的锁可以写一个对象锁
            if (base == 100 && i == 3)
                throw bad_alloc();
            //这里就死锁了，
            // mtx.unlock();

            //会出现死锁，在
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        //捕捉到异常之后，把锁释放掉
        // mtx.unlock();
    }
}

void test()
{
    thread t1, t2;
    vector<int> vt;

    //两个线程要用同一个锁
    mutex mtx;
    //这里用的匿名对象，右值引用,线程要放在里面抛异常
    t1 = thread(vfunc, std::ref(vt), 5, 100, std::ref(mtx));  //这样是存在线程安全问题
    t2 = thread(vfunc, std::ref(vt), 10, 200, std::ref(mtx)); //
    //这种小程序用lambda就行了

    t1.join();
    t2.join();

    for (auto e : vt)
    {
        cout << e << " ";
    }
}

int main()
{
    #ifdef Func

        thread t1(Func, 10);
        thread t2(Func, 20);
        //主线程等待一下子线程

        t1.join();
        t2.join();
    #endif
    threadpool();
    #ifdef Lambda
    int x = 0;
    mutex mtx;
    int N = 10000;
    atomic<int> costtime1(0);
    thread t1([&]
              {
        int begin1 = clock();
        mtx.lock();
        for (int i = 0; i < N; i++)
        {
            x++;
        }
        mtx.unlock();
        cout<<x<<endl;
        int end1 = clock();
        costtime1 += (end1 - begin1);
        cout<<costtime1<<endl;});//lambda表达式可以去处理一些小函数
    cout << x << ":" << costtime1 << endl;

    // costtime1就是调用花费的时间 }); //这里用一个可调用对象就可以了，我们这里用lambda表达式，&全部捕获 }); });
    //项目里面，我们还是用原子的，相对更好一点

    int costtime2 = 0;
    thread t2([&]
              {
                  int begin2 = clock();
        mtx.lock();

                  for (int i = 0; i < N; i++)
                  {
                      x++;
                  }
        mtx.unlock();
                  int end2 = clock();
                  costtime2 = end2 - begin2; }); // costtime1就是调用花费的时间 });
    t1.join();
    t2.join();
    cout << x << ":" << costtime1 << endl;

    #endif
    // this_thread::sleep_for(std::chrono::)

    int n = 10;
    // 严格来说thread的参数不能是左值引用，
    
    thread t1(func,&n);//这样子对n的加，不可以，传值拷贝
    thread t1(func, std::ref(n)); //这样弄就可以了
    t1.join();
    cout << n << endl;
    test();
    return 0;
}