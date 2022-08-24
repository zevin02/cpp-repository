#include<iostream>
using namespace std;


void demo1()
{
    //c++兼容C语言，所以C++也是强类型的语言
    /*
        1. 隐式类型转换：在编译的时候自动就进行，不需要我们手动操作（相近类型，意义相似类型就可以）
        2. 强制类型转换：需要我们自己处理

    */

   int i=10;
   double d=i;//隐式类型转换
   int* p=&i;
//    int address=(int)p;//强制类型转换
}

void demo2()
{
    //C++语言为了加强类型转换的可视性，引入了4种命名的强制类型转换操作符
    //static_cast:用于两个类型之间意义相近的,不能用在两个不相关类型之间的转换

    double d=1.22;
    int a=static_cast<int> (d);//里面写的是要转化到的类型
    cout<<a<<endl;

    // int* p=static_cast<int*> (a);//int和int* 之间类型不相近，所以不能转换
}

void demo3()
{
    //reinterpret_cast:用于两个不相关类型之间的转换
    int a=10;
    int* p=reinterpret_cast<int*> (a);
    double d=2.2;
    // int x=reinterpret_cast<int>(d);//这个不能用在两个相近类型之间的转换
    // cout<<x<<endl;
}


void demo4()
{
    //const_cast就是把原来一个const属性的变量去除了const属性,方便赋值

    volatile const int a=10;//保持内存的可见性,告诉编译器不要优化，每次都到内存里面取数据
    int* p=const_cast<int*> (&a);
    *p=2;
    cout<<a<<endl;//打印出来还是10，
    cout<<*p<<endl;//这个是2
}

class A
{
    public:
    virtual void f();
    protected:
    int x;
    
};

class B:public A
{
    public:
    int m;
};

void func(A* pa)
{
    //如果pa是指向父类对象，就不做处理
    //如果pa是指向子类对象，就把它转回子类，并访问子类对象中的_b成员
    // B* pb1=static_cast<B*> (pa);//父类能转成功，子类也能转成功
    // cout<<"pb1="<<pb1<<endl;

    //这个时候dynamic_cast就能用了，可以用来识别指向父类对象还是子类对象

    //只能用于包含虚函数的类

    B* pb2=dynamic_cast<B*> (pa);
    if(pb2==nullptr)
    {
        //如果是指向nullptr，说明pa指向的是父类对象，转换不成功,返回nullptr
        cout<<"转换失败"<<endl;
    }
    else
    {
        cout<<"转换成功"<<endl;
        pb2->m=10;

    }
}
void demo5()
{
    //dynamic_cast :主要用于向下转换：父类对象指针/引用——————>>子类指针/引用（用dynamic_cast是安全的）
    //向上转换：子类给父类（赋值兼容性规则，不需要转换）
    A a;
    B b;
    a=b;//子给父，是天然可以的
    // b=a;//父给自，是不行的，
    func(&a);
    func(&b);


}

//意义：期望C++程序员，不要再用C的隐式类型转换，而是要全部规范使用，这样在项目维护的时候，就减少被类型转换的坑，但是实际上，很多人嫌麻烦，

//


int main()
{
    demo1();
    demo2();
    demo3();
    demo4();
    demo5();
    return 0;
}