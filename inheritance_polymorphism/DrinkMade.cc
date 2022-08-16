#include <iostream>
using namespace std;

class DrinkBase
{
public:
    virtual void boil() = 0; //这个是给子类去重写的
    virtual void brew() = 0;
    virtual void incup() = 0;
    virtual void pour() = 0;
    void MakeDrink()
    {
        boil();
        brew();
        incup();
        pour();
    }
};

class Coffee : public DrinkBase
{
public:
    virtual void boil()
    {
        cout<<__LINE__<<endl;
    }
    virtual void brew()
    {
        cout<<__LINE__<<endl;
    }
    virtual void incup()
    {
        cout<<__LINE__<<endl;

    }
    virtual void pour()
    {
        cout<<__LINE__<<endl;
    }
};


class Tea : public DrinkBase
{
public:
    virtual void boil()
    {
        cout<<__LINE__<<endl;
    }
    virtual void brew()
    {
        cout<<__LINE__<<endl;
    }
    virtual void incup()
    {
        cout<<__LINE__<<endl;

    }
    virtual void pour()
    {
        cout<<__LINE__<<endl;
    }
};


void makewater(DrinkBase& db)//用一个基类来接收
{
    db.MakeDrink();
}

int main()
{
    Coffee cfe;
    makewater(cfe);
    Tea t;
    makewater(t);
    return 0;
}