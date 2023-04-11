#pragma once
//序列化
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <cstring>
using namespace std;

// 存储数据流的容器,因为数据在TCP里面是以字节流的形式来展示
// Buffer这个类继承了vector<char>这个容器,所以所有的数据都是放到这个容器里面
class Buffer : public std::vector<char>
{
public:
    typedef std::shared_ptr<Buffer> ptr; //把当前的一个buffer的智能指针重命名为ptr
    Buffer() : curpos_(0) {}
    Buffer(const char *s, size_t len) : curpos_(0)
    {
        insert(begin(), s, s + len);
    }
    const char *data() //返回buffer容器的底层指针
    {
        return &(*this)[0];
    }
    const char *curdata() //返回buffer容器从curpos开始位置的底层指针
    {
        return &(*this)[curpos_]; //返回从curpos位置开始的字符串
    }
    size_t cursize() const //返回当前可读取的数据个数
    {
        return size() - curpos_;
    }
    void offset(int k) { curpos_ += k; }
    //插入到数据流中
    void append(const char *s, size_t len)
    {
        insert(end(), s, s + len); //把数据尾插进去
    }
    //把游标设置成0，清空里面所有的数据
    void reset()
    {
        curpos_ = 0;
        clear();
    }

private:
    size_t curpos_; //表示当前数据流的读取位置
};

// 主机字节序是否小端字节序
static bool isLittleEndian() //如果是小端字节序的话，就返回一个小端字节序
{
    static uint16_t flag = 1;
    static bool little_end_flag = *((uint8_t *)&flag) == 1; //取对应的第一个字节，如果是1的话说明就是一个小端机
    return little_end_flag;
}

class Serializer
{
public:
    typedef std::shared_ptr<Serializer> ptr; //再把serializer这个函数的智能指针设置为ptr，暴露给外面
    Serializer()
    {
        buffer_ = std::make_shared<Buffer>(); // buffer这里是一个智能指针，所以我们需要先make_shared来构造一下这个智能指针对象
    }
    Serializer(const char *s, size_t len)
    {
        buffer_ = std::make_shared<Buffer>();
        input(s, len); //使用了一个字符串来进行初始化
    }
    Serializer(Buffer::ptr buffer) //使用了一个Buffer的智能指针来进行初始化
        : buffer_(buffer)
    {
    }

    template <typename T>
    void input_type(T t); //在类里面声明，但是在类外面定义

    template <typename T>
    void output_type(T &t);

    void reset() //调用buffer中的reset函数来清空数据
    {
        buffer_->reset();
    }
    void clear() //清空数据
    {
        reset();
    }
    void input(const char *data, int len) // input就是把数据添加到buffer里面
    {
        buffer_->append(data, len);
    }

    template <typename Tuple, std::size_t Id>
    //用来反序列化
    //将数据导入到特定的元组的某一个位置上
    // Deserialize the tuple.
    // Deserializer d{ss};
    // getv<Tuple, 0>(d, t);将d上的数据导入到元组0号位置的数据上
    // getv<Tuple, 1>(d, t);

    void getv(Serializer &ds, Tuple &t) //反序列化serializer对象中的二进制数据，并构造该数据的tuple
    {
        ds >> std::get<Id>(t); //将数据导入到元组中，
    }
    //可变参数模板，I的
    template <typename Tuple, std::size_t... I>
    //这个里面使用的是一个索引序列
    //将数据全部一次性导入到一个元组中
    //    auto result = get_tuple<Tuple>(std::make_index_sequence<size>{});//使用的是Tuple这个元组，函数参数是一个索引数组

    Tuple get_tuple(std::index_sequence<I...>)
    {
        Tuple t;
        //这个地方使用了一个逗号表达式，先解析左边的每问题就直接放回左边的，如果有问题再返回右边的0
        //相当于从元组t的第I个位置获取元素如果有问题则返回值为0
        std::initializer_list<int>{(getv<Tuple, I>(*this, t), 0)...};//一个一个填充对应的数据，因为使用模板参数，
        return t;
    }

    template <typename T>
    Serializer &operator>>(T &i) //流输出
    {
        output_type(i);
        return *this;
    }

    template <typename T>
    Serializer &operator<<(T i) //重载<<，向buffer里面添加数据,重载了流输入
    {
        input_type(i); //根据对应的不同类型，调用对应的函数
        return *this;
    }

    const char *data() //放回当前数据的首地址
    {
        return buffer_->curdata();
    }
    size_t size() const //返回buffer中的当前还可以读取的元素
    {
        return buffer_->cursize();
    }
    std::string toString() //将buffer首地址中的数据转化成为string类型
    {
        return std::string(data(), size());
    }

private:
    static void byteOrder(char *s, int len) //按照字节序来插入
    {
        if (isLittleEndian())         //如果当前是小端机，就需要把字符串进行反转
            std::reverse(s, s + len); //小端机低位存高地址，高位存低地址
    }

private:
    int byteOrder_;
    Buffer::ptr buffer_; //这个是一个智能指针对象
};

template <typename T>
inline void Serializer::input_type(T v) //这个地方就是在类里面声明然后在类外面进行实现,这个一般是非字符串类型要这样做
{
    size_t len = sizeof(v);                 //获得当前v的字节数
    char *p = reinterpret_cast<char *>(&v); //把传入进行的v强制类型转化成一个字符串
    byteOrder(p, len);                      //将数据按照符合计算机存储的格式来排序
    input(p, len);                          //把数据添加到buffer中,
}

//偏特化，这个地方需要写一个<>,针对string做一个偏特化
template <>
inline void Serializer::input_type(std::string v) //指定特化成什么类型
{
    // 先存入字符串长度，存入字符串的长度是因为在反序列化的时候，程序可以先读取字符串的长度，并且根据长度信息在二进制流中定位字符串数据

    uint16_t len = v.size();
    input_type(len);                               //先输入字符串的长度,都是使用前两个字节先存储字符串的长度，两个字节后才会获得对一个的数据
    byteOrder(const_cast<char *>(v.c_str()), len); //将v按照对应的字节序列的方式进行一个转化,去除const属性
    // 将转化好在字符串放到buffer中
    input(v.c_str(), len);
}

//再进行一个偏特化
template <>
inline void Serializer::input_type(const char *v)
{
    input_type<std::string>(std::string(v)); //指定调用string类型实现的函数
}

template <typename T>
inline void Serializer::output_type(T &v) //根据buffer里面存储的数据进行一个反序列化输出
{
    size_t len = sizeof(v); //先获得元素的字节大小
    assert(size() >= len);
    ::memcpy(&v, data(), len); //把buffer中的数据拷贝给v,这个地方地区的是一个按照了小端机器存储的数据
    buffer_->offset(len);      //将对应的buffer中的有变进行移动
    //获得数据之后还要把数据进行一个字节序列调整
    byteOrder(reinterpret_cast<char *>(&v), len); //再把他根据对应的字节许转化回来,因为插入的时候就因为是小端机而反转了一次
    //所以现在获得的时候也要再反转回来
}

//将输出
template <>
inline void Serializer::output_type(std::string &v) //将对应的流里面的字符串类型进行输出到对应的元素中
{
    uint16_t strLen = 0; //获得字符串的长度
    output_type(strLen); //先从里面获得对应的字符串长度，才能根据长度获得对应的数据
    v = std::string(data(), strLen);
    buffer_->offset(strLen);
    byteOrder(const_cast<char *>(v.c_str()), strLen);
}