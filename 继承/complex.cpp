/*
class Student
class Teacher

class Assistant :public Student ,public Teacher

*/

#include <iostream>
#include <string>
using namespace std;

class person
{
public:
    string _name;
};

class student :virtual public person
{
public:
    int id;
};

class teacher : virtual public person//虚继承，就没有了数据冗余，在腰部继承下来
{
public:
    string course;
    //继承下来的person，name相当于父类的引用，别名
};

class assistant : public student, public teacher
{
public:
    string who;
};

int main()
{
    assistant a;
    //我们对person的名字就会具有二义性
    //不知道是那个父类的名字
    a.id=1;
    //二义性，我们还可以解决
    a.student::_name="zha";//用这种方法就可以解决二义性
    a.teacher::_name="laozhi ";//
    //数据冗余，就没办法就觉
    //我们可以使用虚继承结解决二义性

    return 0;
}
