#include "serializer.hpp"
#include"rpc.hpp"

string Strcat(string s)
{
    return "111";
}


void rpc_test()
{
    rpc server;
    server.as_server(555);//作为服务器，给定一个端口号
    server.regist("strcat",Strcat);//注册一个函数
}

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
    string ret = buffer.data(); //获得底层的指针
    Serializer serializer1;
    int data = 100;        //如果是插入一个整形的话，直接插进去
    serializer1 << data;   //把数据按照流的方式输入进去
    string data1 = "word"; //插入一个字符串的话，就需要先获得他的字符串长度
    serializer1 << data1;
    cout << serializer1.toString() << endl; //输出当前的数据
    // int od;
    // serializer1>>od;
    // cout<<od<<endl;
    string ll;
    serializer1 >> ll;
    cout << ll << endl;

    // auto result =  get_tuple<0, 1, 2>(serializer);
    // std::cout << std::get<0>(result) << ", " << std::get<1>(result) << ", " << std::get<2>(result) << std::endl;
    tuple<int,string,float> ss(32,"hello",2.2);//这个tuple里面就是一个元组
    auto result=make_tuple(0,string());//生成一个空的元组
    

    // server.register();//给rpc的服务器注册一个成员函数
    // server.run();//运行server服务器
    rpc_test();
    return 0;
}