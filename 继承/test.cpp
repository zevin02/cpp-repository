#include <iostream>
using namespace std;
#include <string>
// class Person
// {
// public:
// 	void Print()
// 	{
// 		cout << "name:" << _name << endl;
// 		cout << "age:" << _age << endl;
// 	}

// protected:
// 	string _name = "peter"; // 姓名
// 	int _age = 18;			// 年龄
// private:
// 	int _aa;
// };
// // 继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分。这里体现出了Student和
// //Teacher复用了Person的成员。下面我们使用监视窗口查看Student和Teacher对象，可以看到变量的复用。
// //调用Print可以看到成员函数的复用。
// //Person里的成员变量和成员函数都被包含了进去
// class Student : public Person
// {
// public:
// 	// void f()
// 	// {
// 	// 	_aa=1;//在类里面也不能使用
// 	// }
// protected:
// 	int _stuid; // 学号
// };
// class Teacher : public Person
// {
// protected:
// 	int _jobid; // 工号
// };
// int main()
// {
// 	Student s;
// 	//s._aa=1;//在类外面不能用
// 	Teacher t;
// 	s.Print();
// 	t.Print();
// 	return 0;
// }
class person
{
protected:
	string _sex;
	string _name;
	int _age;
};

class student : public person
{
public:
	int _no;
};

int main()
{
	person p;
	student s;
	//父类=子类赋值兼任-》切割，切片
	//只有public继承可以
	//把子类里面父类的那一部分切割过去，给父类
	//父类的指针和父类的引用
	//这里不存在类型转换，是语法天然支持的行为
	p=s;
	//父类不能给子类对象

	person*ptr=&s;//指针只能得到其中的父类的部分
	person& ref=s;//变成子类对象当中父类对象的别名
	//父类不能给子类
	//但是指针和引用可以
	//可以强制转换
	student*pptr=(student*)&p;//会有越界访问的风险
	student& rref=(student&)p;

	return 0;
}