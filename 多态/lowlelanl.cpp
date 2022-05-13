#include <iostream>
using namespace std;

class person
{
public:
    virtual void buyticket()
    {
        cout << "all" << endl;
    }
    void f()
    {
        cout<<"hello world"<<endl;
    }
protected:
    int _a = 0;
};
class student : public person
{
public:
    virtual void buyticket()
    {
        cout << "half" << endl;
    }

private:
    int _b = 0;
};


void func(person& p)//p看到的还是父类对象，看到的一样是个虚表指针，只不过父类对象里面的虚表里面，是重写的虚函数，所以就是调用不同的函数
//对象的虚函数表里面存的是什么，就决定了掉的是什么
{
    p.buyticket();//找虚
    p.f();//普通函数调用是直接调用
}
int main()
{
    person mike;
    student jason;
    func(mike);//到mike里面找到虚函数指针，在虚函数指针里面找到对应的虚函数，然后调用它
    func(jason);//如果是子类，就会发生切割（切片），
    return 0;
}