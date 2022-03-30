#pragma once
#include <string.h>
#include <iostream>
using namespace std;
namespace xzw
{
    class string
    {
    private:
        char *_str;
        size_t size;
        size_t capacit;

    public:
        string(const char *str) //构造函数
            //: _str(str)//不能这样写，因为我们要能够动态的扩容
            : _str(new char[strlen(str) + 1]) //我们要new才可以动态的扩容，
        {
            strcpy(_str, str);
        }
        string(const string &s) //传引用拷贝
            : _str(new char[strlen(s._str) + 1])
        {
            strcpy(_str, s._str);
        }
        //assign，赋值运算符
        string &operator=(const string &s) //我们也要自己写，不然就是浅拷贝，还要考虑自己给自己赋值
        {
            //如果自己给自己赋值，要拷贝的东西被我们毁掉，就没办法操作了
            // if (this!=&s)
            // {
            //     delete[] _str; //直接简单粗暴的把原来的空间给释放调，,我们不能把s给释放调，说不定以后还会用到s的数据，有可能new失败
            //     //先把原来的空间给释放调，再重新开辟一块空间
            //     _str = new char[strlen(s._str) + 1];//开一个和s一样大的空间，
            //     strcpy(_str, s._str);
            // }
                 if (this!=&s)
            {
                char* tmp=new char[strlen(s._str)+1];
                strcpy(tmp,s._str);//先拷贝再释放掉
                delete [] _str;//
                _str=tmp;
            }
            return *this;//出了作用于*this还在，所以传引用返回
        }
        ~string() //析构函数
        {
            delete[] _str; //new完之后就要delete
            _str = nullptr;
        }
    };
    void test_string1()
    {
        string s("hello ");
        //string s2(s);//拷贝构造,对默认类型会完成数值拷贝，浅拷贝，指向同一块空间，出了作用域，调用释放函数，自定义类型，调用他的拷贝构造
        //我们不能在同一块空间
        string s2(s);
        string s3("hello ");
        s = s3; //如果我们不写就是浅拷贝，连着地址一起拷贝过去了，s内存还没有释放，内存泄漏
        //我们不能直接去拷贝，因为可能会出现空间不够，导致还要去进一步的扩容，小拷贝到大，会导致空间用不完，
        s="alcd";
        printf("sdahello,world a\n");
    }
}