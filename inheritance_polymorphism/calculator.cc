#include <iostream>
using namespace std;

//使用多态实现计算器
class Calculator
{
public:
    virtual int GetResult() = 0;
    Calculator(int a, int b)
        : n1(a), n2(b)
    {
    }

    Calculator(const Calculator &cal)
        : n1(cal.n1), n2(cal.n2)
    {
    }

protected:
    int n1;
    int n2;
};

class Add : public Calculator
{
public:
    Add(int a, int b)
        : Calculator(a, b)
    {
    }
    virtual int GetResult()
    {
        return Calculator::n1+Calculator::n2;
    }
};


class Del : public Calculator
{
public:
    Del(int a, int b)
        : Calculator(a, b)
    {
    }
    virtual int GetResult()
    {
        return n1-n2;//在在子类里面可以直接调用父类的成员
    }
private:
    int n3;
};


int func(Calculator* base)//用这个函数就可以
{
    int ret=base->GetResult();
    cout<<ret<<endl;
}


int func(Calculator& base)//用引用重载
{
    int ret=base.GetResult();
    cout<<ret<<endl;
}
int main() 
{
    Add x(1,2);
    int ret=x.GetResult();
    cout<<ret<<endl;
    Del m(1,2);
    ret=m.GetResult();
    cout<<ret<<endl;

    Calculator* base=new Add(5,2);//new一个子类给父类
    func(base);
    delete base;

    Del c(4,2);
    func(c);

    return 0;
}