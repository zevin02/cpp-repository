#include"serializer.hpp"
int main()
{
    Buffer buffer;
    if (buffer.empty()) //这里的empty调用的直接就是vector<char>实现的empty
    {
        string s = "hello";
        buffer.append(s.c_str(), s.size());
    }
    //把buffer的偏移量移动到index为2的位置
    buffer.offset(2);
    string ret = buffer.data();//获得底层的指针
    Serializer serializer1;
    int data=100;
    serializer1<<data;//把数据按照流的方式输入进去
    string data1="word";
    serializer1<<data1;
    cout<<serializer1.toString()<<endl;//
    int od;
    serializer1>>od;
    cout<<od<<endl;
    string ll;
    serializer1>>ll;
    cout<<ll<<endl;

    return 0;
}