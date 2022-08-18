#include <iostream>
using namespace std;
#include <string>

double Division(int a, int b)
{
    if (b == 0)
    {
        string errmsg("/0");
        throw errmsg; //抛出这个errmsg,这个errmsg是一个临时对象，

        // throw"division by zero condition";//b是0的话，就出现错误，不让程序终止掉
        //抛一个字符串出来
    }
    else
        return ((double)a / (double)b); //直接除，如果发生除0错误，就直接终止掉，我们不想
}

void func2()
{
    int len, time;
    cin >> len >> time;
    if (time != 0)
        throw 1.1; //抛出一个int类型变量
    //异常没有被捕获,直接就中断了
    else
        cout << len << " " << time << endl;
}

void func1()
{
    try
    {
        int len, time;
        cin >> len >> time;
        cout << Division(len, time) << endl;
    }
    catch (const string &errmsg) //捕获一下,和抛出的类型是要匹配的,抛出异常之后程序就终止了
    {
        //有点像实际参数传给形参
        //把对象进行拷贝捕获
        cout << errmsg << endl;
    }
    func2();
}

void demo1()
{
    try
    {
        func1();
        //如果正常执行的话，下面的catch就不会执行

        //如果有异常的话，就直接就跳到了catch的地方了,
    }

    catch (const string &errmsg) //捕获一下,和抛出的类型是要匹配的,抛出异常之后程序就终止了
    {
        //有点像实际参数传给形参
        //把对象进行拷贝捕获
        cout << errmsg << endl;
    }
    catch (int errid) // catch是可以有很多个
    {
        cout << errid << endl;
    }
    catch (...) //这个就可以捕获上面我们没写的位置类型的异常，程序就不会终止了
    {
        cout << "unknown exception" << endl;
    }
}

void func()
{
    int *arr = new int[10]; //可以用只能指针尝试处理
    int len, time;
    cin >> len >> time;
    try
    {
        cout << Division(len, time) << endl;
    }
    catch (const string &errmsg) //这里提前把他捕获了，后面也能正常运行
                                 //拦截异常不是要处理异常，而是要正常释放资源
    {
        cout << "delete []" << arr << endl; //这样就可以了,但是我们希望最外层进行处理
        delete[] arr;
        throw errmsg; //重复抛出异常
    }
    catch (...) //这里提前把他捕获了，后面也能正常运行
                //拦截异常不是要处理异常，而是要正常释放资源
    {
        cout << "delete []" << arr << endl; //这样就可以了,但是我们希望最外层进行处理
        delete[] arr;
        throw; //捕获到什么就抛出什么对象
    }
    //这个地方抛异常，后面的代码就不会执行了，就会出现内存泄露的问题
    //异常安全的问题
    cout << "delete []" << arr << endl; //这样就可以了,但是我们希望最外层进行处理
    delete[] arr;
}
void demo2()
{
    try
    {
        func();
    }
    catch (const string &errmsg) //上面再抛出的异常就在这个地方统一处理
    {
        cout << errmsg << endl;
    }
}

//异常的继承体系
class Exception //异常的基类对象
{
public:
    Exception(const string &errmsg, int &id)
        : _errmsg(errmsg), _id(id)
    {
    }
    virtual string what() const //多态
    {
        return _errmsg;
    }

protected:
    string _errmsg; //错误的描述
    int _id;        //错误的编号,区分某种错误，对某种错误进行特殊处理
    //比如假如说网络错误的话，我们不能直接反馈信息，而是要重复去尝试10次直到不行，才反馈，所以id就是表示错误的编号
};

class SqlException : public Exception
{
public:
    SqlException(const string &errmsg, int id, const string &sql)//记录一下sql语句
        : Exception(errmsg, id), _sql(sql) //调用父类的构造函数
    {
    }
    virtual string what() const //多态,子类重写了父类的虚函数
    {
        string str = "SqlException :"; //前缀
        
        str += _errmsg;
        str+="->";
        str += _sql;
        return str; //这样就行了
    }

private:
    string _sql; //请求类型是什么
};

class CacheException : public Exception
{
public:
    CacheException(const string &errmsg, int id)
        : Exception(errmsg, id) //调用父类的构造函数
    {
    }
    virtual string what() const //多态
    {
        string str = "CacheException :"; //前缀
        str += _errmsg;
        return str; //这样就行了
    }
};

class HttpException : public Exception
{
public:
    HttpException(const string &errmsg, int id, const string &type)
        : Exception(errmsg, id), _type(type) //调用父类的构造函数
    {
    }
    virtual string what() const //多态,子类重写了父类的虚函数
    {
        string str = "HttpException "; //前缀
        str += _type;
        str += ":";
        str += _errmsg;
        return str; //这样就行了
    }

private:
    string _type; //请求类型是什么
};

void SQLMgr()
{
    if (rand() % 9 == 0)
    {
        throw SqlException("权限不足", 100,"select * from name = 'zhansang'"); //但是我们怎么知道是谁的权限不足
    }
    //但是可能三者都会抛异常
}

void CacheMgr()
{
    if (rand() % 3 == 0)
    {
        throw CacheException("权限不足", 100); //但是我们怎么知道是谁的权限不足
    }
    if (rand() % 5 == 0)
    {
        throw CacheException("数据不存在", 101);
    }
    //...缓存里面再查到数据库
    SQLMgr();
}

//我们可以抛任意类型的异常，但是必须要继承父类
void HttpServer()
{
    //...数据来了网络先接收，走到缓存里面去
    if (rand() % 2 == 0)
    {
        throw HttpException("请求资源不在", 100, "get");
    }
    if (rand() % 7 == 0)
    {
        throw HttpException("权限不足", 101, "post");
    }
    throw "xxxxxx";//未知异常，程序不会崩
    CacheMgr();
}
#include <chrono>
#include <thread>
#include <unistd.h>
void ServerStart()
{
    while (1)
    {
        this_thread::sleep_for(chrono::seconds(1));
        try
        {
            HttpServer();
        }

        // 这个下面就是异常的捕获
        catch (const Exception &e) // const类型的this指针，里面的成员也都要在最后面加const
        {
            //我们可以用一个多态,
            // 1.虚函数的重写  2. 父类的指针或引用去调用,

            //这样就可以用了，把他们写到对应的日志库里面就行了
            std::cerr << e.what() << endl; //捕获去调用这个对象就是多态
        }
        catch (...)
        {
            std::cerr << "unknown Exception" << endl;
        }
    }
}

void demo3()
{
    ServerStart();
}



#include<vector>
void demo4()
{
    try
    {
        vector<int> v(10,5);
        v.resize(1000000000000);//bad_alloc
        // v.at(10)=100;//out of range
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
int main()
{
    // demo1();
    // demo2();
    // demo3();
    demo4();
    return 0;
}