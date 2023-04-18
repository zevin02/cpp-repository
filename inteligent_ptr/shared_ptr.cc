#include<iostream>
using namespace std;
#include<memory>

int main()
{
    shared_ptr<int> sp=make_shared<int>();
    *sp=10;
    sp.get();//是获得他指向对象的指针，返回类型为指针类型
    cout<<*sp.get();//这个是和*sp一样
    return 0;
}