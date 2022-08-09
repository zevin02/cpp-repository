#include <iostream>
using namespace std;
#include <string>
#include <fstream> //文件流
class B
{
public:
    int _a;
    operator bool() //被隐士类型转化成bool
    {
        //这个不用写返回值，这个意思就是说，这个类型可以被转化成bool
        return _a != 0;
    }
};
class Date
{

    friend ofstream& operator<<(ofstream& ofs, const Date& d);//重载一下<<添加友元，可以在外面使用

public:
    Date(int y = 1, int d = 1, int m = 1)
        :day(d), year(y), month(m)
    {}
    
private:
    int day;
    int year;
    int month;
};
struct ServerInfo
{
    string _ip;
    int _port;
    Date d;

};

ofstream& operator<<(ofstream& ofs, Date& d)//重载一下<<
{
    ofs << d.year << " " << d.month << " " << d.day << endl;
    return ofs;//为了支持连续的插入
}

void Test_Bin_CW()
{
    ServerInfo info = {"127.0.0.1", 8080};
    // fopen，fclose
    //二进制读写，fwrite，fread，内存里面字节什么样，就怎么写，但是这样文件里面看到的乱码，文件里面都是字节流，1个int4个字节，
    //文本读写，就是每个写都是转化成字符串读写，可以看到，fputs/fprintf,fscanf
    FILE *fout = fopen("test.bin", "w");
    fwrite(&info, sizeof(info), 1, fout);
    fclose(fout);
}

void Test_Bin_CR()
{
    ServerInfo info;
    // fopen，fclose
    //二进制读写，fwrite，fread，内存里面字节什么样，就怎么写，但是这样文件里面看到的乱码，文件里面都是字节流，1个int4个字节，
    //文本读写，就是每个写都是转化成字符串读写，可以看到，fputs/fprintf,fscanf
    FILE *fout = fopen("test.bin", "r");
    fread(&info, sizeof(info), 1, fout);
    fclose(fout);
}

class Configure
{
private:
    string _filename;

public:
    Configure(const char* filename)
    :_filename(filename)
    {}

    void Write_Bin(ServerInfo & info)
    {
        //写，就用ofstream
        ofstream ofs(_filename.c_str(),ios_base::out|ios_base::binary);//out到文件里面，以二进制的方式写
        //这个不需要我们去调用close，因为有析构函数
        ofs.write((const char*)&info,sizeof(info));//这样就能写到文件里面去了
    }

    void Read_Bin(ServerInfo & info)
    {
        ifstream ifs(_filename.c_str(),ios_base::in|ios_base::binary);
        ifs.read((char*)&info,sizeof(ServerInfo));//读取到info里面

    }

     void Write_Text( ServerInfo& info)//文本读写
    {
        ofstream ofs(_filename.c_str());
        //可以使用流插入<<
        ofs << info._ip << " " << info._port;//这样就写到文件里面去了,默认空格，换行作为分割
        ofs << info.d;
    }
    void Read_Text( ServerInfo& info)
    {
        ifstream ifs(_filename.c_str());
        //可以使用流插入<<像正常用流一样使用
        ifs>> info._ip >> info._port;//这样就写到文件里面去了
    }
};

int main()
{
#if 0
    int i=1;
    double b=1.1;
    cout<<i;//cout.operator<<(i),和printf比慢是因为底层封装的太多了
    cout<<b;
    //内置类型我们可以直接用cout<<,cin>>是因为库里面实现了，自定义类型就需要我们自己重载才可以用
    //这个在图形化界面里面就是cout流向控制台，cin就是从控制台提取放到内存里面
    cout<<i<<b;//两个地方
#endif
#if 0
    B b;
    while(b)//这个里面必须包含一个bool类型,我们重载一下bool就可以用了
    {
        //这里我们发送2号信号，operator里面的标志就被设置了，就停止了
        cin>>b._a;
    }
#endif

    // Test_Bin_CW();
    // Test_Bin_CR();
    ServerInfo info = {"127.0.0.1", 8080};
    Configure cm("config.bin");
    // cm.Write_Bin(info);
    ServerInfo in;
    cm.Read_Bin(in);
    cout<<in._ip<<":"<<in._port<<endl;
    return 0;
}