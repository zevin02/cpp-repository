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
        //align，赋值运算符
        string&operator=(const string &s)//我们也要自己写，不然就是浅拷贝
        {
            strcpy(this->_str,s._str);
            return *this;

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
        string s3("sortt");
        s=s3;
        printf("hello\n");
    }
}