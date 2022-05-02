
#include <string>
#include<iostream>
using namespace std;

class Person //父类
{
public:
    Person(const char *name /*="peter"*/) //构造函数
        : _name(name)                     //初始化列表，对值进行初始化
    {
        cout << "person()" << endl;
    }
    Person(const Person &s) //拷贝构造
        : _name(s._name)
    {
        cout << "person(const person& s)" << endl;
    }
    Person &operator=(const Person &s) //赋值相等
    {
        cout << "Person=" << endl;
        if (this != &s)
        {
            _name = s._name;
        }
        return *this;
    }
    ~Person()
    {
        cout << "~Person()" << endl;
    }

protected:
    string _name;
};

class Student : public Person //公有继承，子类
{
public:
    //父类没有默认构造函数，我们自己写
    Student(const char *s = "zhans", int num = 1)
        : Person(s) //调用默认构造，父类也是我们调用，不同于析构

          ,
          _num(num)
    {
    }

    Student(const Student &s)
        //把s当中父类的那一部分取出来
        : Person(s) //我们可以直接传，他会切片，所以不用担心，这是一个天然的部分
                    //这个之后会变成父类当中的别名
          ,
          _num(s._num)
    {
    }

    // s2=s1;
    Student &operator=(Student &s)
    {
        //赋值和拷贝构造类似，只不过他们是已经存在的对象进行赋值
        if (this != &s)
        {
            _num = s._num;

            // operator=(s);//调用父类的赋值运算，所以这里父类切的就是父类的那一部分，没有什么问题
            //上面的操作会无限递归下去，死循环
            Person::operator=(s); //我们指定一下就可以了
        }
    }

    //析构函数的名字，会被统一处理成destructor（）（至于为什么会这样，多态的时候我们就会讲解）
    //所以就会被构成隐藏
    #if 0
    //这段代码在vscode里面无法通过
    ~Student()
    {
        //Person::~Person();//这里要指定作用域才可以调用，，
        //我们指定了父类
        //调用父类的
        //delete[] p;
        //我们这里会发现调用两次析构，
        //我们子类先执行
    }
    //子类的析构函数不需要我们去显示调用，因为会在子类析构的时候自动调用父类的析构
    //我们初始化的时候，父类先构造，子类再构造，析构的时候子类先析构，父类再析构
    //所以我们实现子类析构函数的时候，不需要显示调用父类的析构函数，



    #endif

    
private:
    int _num = 1; //这里不是初始化，只是给了一个缺省值
    // string _s="dasd";
    // int *p=new int[10];
};

//派生类的重点4个默认成员函数，我们不写，编译器会默认生成会干些什么呢
//如果我们要写，要做些什么呢

// 我们不写，默认生成的派生类的构造和析构
// a。父类继承下来的 （调用父类的默认构造和析构处理） b。自己的（内置类型和自定义类型成员）(跟普通类是一样的)

//我们不写默认生成的拷贝构造和operator =
// a。父类继承下来的（调用父类的拷贝构造和operator=），完成值拷贝和浅拷贝    b。自己的（内置类型和自定义类型成员）(跟普通类是一样的)
/*

总结：
继承下来的调用父类处理，自己的按普通类基本规则
如果要我们自己处理呢，该如何去写，什么情况要自己写

父类的成员调用父类的对应构造，拷贝构造，operator=和析构处理
自己的成员按需求处理（普通类处理）

1.父类没有默认构造,我们要自己写
2.如果自己的子类有资源要进行释放，就需要我们自己写析构
3.如果子类有存在深拷贝问题，就需要我们自己实现拷贝构造和赋值



4.友元关系不能继承，父类的朋友，不一定是子类的朋友，所以不能访问他的私有成员，
5.继承与静态成员，静态成员无论继承怎么样，静态成员都是一样的，static count,继承都是一样样的，地址也是一样的，只有一份，


*/
int main()
{
    //一个类如果我们不写，我们会不会自动生成一个
    Student s;
    // Student s1(s); //拷贝构造
    // Student s3("jack", 18);
    // s1 = s3;
    return 0;
}
