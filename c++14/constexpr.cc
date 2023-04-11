#include<iostream>
using namespace std;


//constexpr关键字表示就是在编译的时候就能进行求值的常数表达式
//使用constexpr关键字修饰的变量一般在编译的时候就能确定下来，可以当作常量
//常用来声明枚举常量和数组常量，

constexpr int add(int x)
{
    return x+x;
}
int main()
{
    constexpr int  result=add(5);//在调试的时候，发现这个函数无法跳转，说明在编译的时候就已经执行好了，所以无法跳转
    
    static_assert(result==10,"unexpected result");//我们使用静态断言来判断是否是一个全局的常量
    return 0;
}