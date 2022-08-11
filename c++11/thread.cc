#include <iostream>
#include <thread>
using namespace std;
#include <mutex>
#include <atomic>
/*
    c++11的线程库可以跨平台
    thread里面的线程函数,只要是可调用对象都可以
    * 函数指针
    * lambda表达式
    * 类对象的仿函数

*/

// demo1:两个线程对同一个变量进行++，堆上的和数据段上的数据都是共享的

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

        cout << std::this_thread::get_id() << "++x " << x << endl; //获得对应的线程id

        //抢到锁的人执行的指令太少了，导致另一个人刚离开回去休息又回来了，而是在这里循环等待，一直问，好了我就进去执行，（自旋锁）
        ++x;
    }
    mtx.unlock();
}

#endif
//我们可以对这些数进行原子操作，不用锁

atomic<int> x(0); //这样对x的操作就变成了原子操作,不能用=

void Func(int n)
{
    for (int i = 0; i < n; i++)
    {
        ++x;
    }
}
#define Lambda

#include<vector>


void threadpool()
{
    //实现一个线程池
    atomic<int> x(0);
    //我们实现一个n个线程都对它进行加m次
    int n,m;
    cin>>n>>m;
    vector<thread> vthds;
    vthds.resize(n);//我们直接就开n个线程，用thread的默认构造函数进行初始化，无参的，就不是不运行
    //这里还有还可以用移动构造和移动赋值
    atomic<int> costtime(0);
    for(size_t i=0;i<vthds.size();i++)
    {
        vthds[i]=thread([m,&x,&costtime](){
            int begin=clock();
            for(int i=0;i<m;i++)
            {
                x++;//这里的x是原子变量
            }
            int end=clock();
            costtime+=(end-begin);
        });//这里我们用了移动赋值，构造了一个线程对象，线程里面用的是lambda表达式
    }
    for(auto& e:vthds)
    {
        e.join();//这里必须要用&，如果不用的话，就会去掉拷贝构造，这是不允许的
    }
    cout<<x<<endl;
    cout<<costtime<<endl;


}


int main()
{
    // #ifdef Func

    //     thread t1(Func, 10);
    //     thread t2(Func, 20);
    //     //主线程等待一下子线程

    //     t1.join();
    //     t2.join();
    // #endif
    threadpool();
    // #ifdef Lambda
    // int x = 0;
    // mutex mtx;
    // int N = 10000;
    // atomic<int> costtime1(0);
    // thread t1([&]
    //           {
    //     int begin1 = clock();
    //     mtx.lock();
    //     for (int i = 0; i < N; i++)
    //     {
    //         x++;
    //     }
    //     mtx.unlock();
    //     cout<<x<<endl;
    //     int end1 = clock();
    //     costtime1 += (end1 - begin1); 
    //     cout<<costtime1<<endl;});//lambda表达式可以去处理一些小函数
    // cout << x << ":" << costtime1 << endl;

    // // costtime1就是调用花费的时间 }); //这里用一个可调用对象就可以了，我们这里用lambda表达式，&全部捕获 }); });
    // //项目里面，我们还是用原子的，相对更好一点

    // int costtime2 = 0;
    // thread t2([&]
    //           {
    //               int begin2 = clock();
    //     mtx.lock();

    //               for (int i = 0; i < N; i++)
    //               {
    //                   x++;
    //               }
    //     mtx.unlock();
    //               int end2 = clock();
    //               costtime2 = end2 - begin2; }); // costtime1就是调用花费的时间 });
    // t1.join();
    // t2.join();
    // cout << x << ":" << costtime1 << endl;

    // #endif
    return 0;
}