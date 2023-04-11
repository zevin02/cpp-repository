#pragma once

#include <zmq.hpp>
#include <memory>
#include "serializer.hpp"
#include <functional>
#include <map>
enum rpc_role
{
    RPC_CLIENT,
    RPC_SERVER
};

class rpc
{
public:
    rpc()
        : context_(1) //我们给定了一个线程
    {
    }
    ~rpc()
    {
        context_.close(); //使用完了便断开连接
    }
    void as_server(int port) //当前rpc以server的形式存在
    {
        role_ = RPC_SERVER; //设置当前的rpc的角色
        //为当前的rpc设置
        socket_ = unique_ptr<zmq::socket_t, function<void(zmq::socket_t *)>>(new zmq::socket_t(context_, ZMQ_REQ), [](zmq::socket_t *sock)
                                                                             {sock->close();delete sock;sock=nullptr; }); //使用unique_ptr智能指针进行一个初始化
        std::string addr = "tcp://*:" + std::to_string(port);
        cout << addr << endl;
        socket_->bind(addr); //绑定对应的地址
    }
    template <class F>
    //注册一个函数
    void regist(const string &name, F func)
    {
        //这个函数bind，绑定的第一个参数是func（我们固定死了），后面还有3个占位符，说明这个函数总共有4个参数

        mapFunctions_[name] = bind(&rpc::callproxy<F>, this, func, std::placeholders::_1, std::placeholders::_2, placeholders::_3);
    }
    template <class F>
    //这个地方的func就是rpc要server注册的函数，pr就是一个序列化工具，data就是要处理的数据，len就是处理数据的长度
    void callproxy(F func, Serializer *pr, const char *data, int len)
    {
        callproxy_(func, pr, data, len); //调用对应的整数的处理函数，因为func函数的长数可能有多个,这个地方调用的是一个函数指针
    }

    // template<class R,class ...Args>
    //真正执行函数的地方,并且进行一个序列化
    // template <typename R, typename C, typename S, typename... Args>
    // void callproxy_(R (C::*func)(Args...), S *s, Serializer *pr, const char *data, int len)
    // // void callproxy_(std::function<R(Args...)> func,Serializer* pr,const char* data,int len)
    // {
    //     using args_type = std::tuple<typename std::decay<Args>::type...>; // decay是一个弱化的功能
    // }
    template <typename R, typename... Args>
    void callproxy_(R (*func)(Args...), Serializer *pr, const char *data, int len)
    {
        callproxy_(std::function<R(Args...)>(func), pr, data, len);//当前的函数指针再转化成一个function
    }

    template<class R,class ...Args>
    void callproxy_(function<R(Args...args)>func,Serializer* pr,const char* data,int len)
    {
        //在这个地方实现对应的注册功能
        using args_type=std::tuple<typename std::decay<Args>...>;//将元素中的每一个元素都进行一个弱化
        

    }

private:
    int role_;               //当前rpc的角色
    zmq::context_t context_; //这个地方的context表示的是zeroMQ上下文的类，提供了创建和管理zeroMQ套接字的环境，用于套接字通信

    unique_ptr<zmq::socket_t, std::function<void(zmq::socket_t *)>> socket_;              //这个智能指针设置了定制删除器，管理的是一个zmq套接字对象
    std::map<std::string, function<void(Serializer *, const char *, int)>> mapFunctions_; //将对应的一个key映射到一个函数上
};