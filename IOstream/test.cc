#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct info
{
    string name;
    int age;
};
class Date
{
private:
    int day;
    int age;

public:
    ostringstream &operator<<(ostringstream &oss)
    {
        oss << day << " " << age;
        return oss;
    }
    Date(int d=1,int a=1)
    :day(d),age(a)
    {}
};
int main()
{
    // ofstream ofs("rr.txt");
    // ofs<<"你好啊";
    // ifstream ifs("rr.txt");
    // string ss;
    // ifs>>ss;
    // cout<<ss<<endl;
    // ofstream ofs("rr.txt",ios_base::out|ios_base::binary);
    // string name="asdasfsdfds";
    // ofs.write(name.c_str(),name.size());
    ifstream ifs("rr.txt", ios_base::in | ios_base::binary);
    char *buff = new char[1024];
    ifs.read(buff, 1024);
    cout << buff << endl;
    delete[] buff;
    ostringstream oss;
    info in = {"asd", 1};
    oss << in.name << " " << in.age; //结构化的数据转化成string,流都是以空格和换行来分割的
    string str = oss.str();
    cout << str;

    //字符串转结构化数据

    istringstream iss(str);
    string name;
    int age;
    iss >> name >> age; //这样就能把数据取处理了
    cout << name << age << endl;
    Date d(1,2);
    ostringstream iso;
    // iso<<d;
    return 0;
}