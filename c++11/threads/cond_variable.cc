#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

//两个线程交替打印，一个打印奇数，一个打印偶数
void test1()
{
    int n = 100;
    // t1打印奇数
    int i = 0;
    mutex mtx;
    bool flag = false;
    condition_variable cv;
    thread t1([&]()
              {
        while(i<n)
        {
            
            //尽量不要单独用lock和unlock
            // lock_guard<mutex> lock(mtx);//这个是出了作用域才解锁
            unique_lock<mutex> lock(mtx);

            //wait后面的是可调用对象，函数，lambda，仿函数
            // cv.wait(lock,[&flag](){return flag;});//在里面如果是false，就会一直阻塞,直到变成true才会开始，唤醒之后flag为true，就打印，
            //这里的wait是直到条件为真才会去执行任务
            cv.wait(lock,[&](){return i%2==1;});
            //唤醒和里面条件都会挡住它
            cout<<this_thread::get_id()<<"->"<<i<<" "<<endl;
            i++;
            flag=!flag;
            cv.notify_one();//唤醒一个

        } });
    // t2打印偶数
    thread t2([&]()
              {
           while(i<n){
            unique_lock<mutex> lock(mtx);
            //!flag是true，这里获取到不会阻塞，就会运行了
            // cv.wait(lock,[&flag](){return !flag;});
            cv.wait(lock,[&](){return i%2==0;});
            cout<<this_thread::get_id()<<"->"<<i<<" "<<endl;;
            i++;
            flag=!flag;//保证下一个自己不会打印
            cv.notify_one();//唤醒
           } });
    t1.join();
    t2.join();
}

int main()
{
    test1();
    return 0;
}