/*
    get():就是获得原生指针,但是是一个右值类型，无法取地址
    reset(),用来重新指定这些指针所持有的内存对象,使用reset可以更加安全和方便的管理内存，计数起会相应的更新

*/

#include <iostream>
#include <string>
#include <vector>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>

using namespace std;

void testReset()
{
    unique_ptr<int> ptr(new int(42)); //引用计数为1
    // ptr.reset(new int(100));//引用计数-1,释放原来的内存对象
    // ptr.reset();//释放原来的内存对象
    int a = 2;
    int *p = &a;
    ptr.reset(p); //该智能指针重新指向指针p，
    cout << *ptr << endl;
}

std::vector<std::string> GetLocalIpAddresses()
{
    std::vector<std::string> ip_addresses;
    ifaddrs *if_addr_struct = nullptr; //这里定义对应的结构体

    // 使用 std::unique_ptr 管理 ifaddrs 结构体的内存
    // 这里的decltype的作用是自动推导定制删除器的函数指针类型
    // 后面&，就是指定了需要使用的定制删除器
    
    std::unique_ptr<ifaddrs, decltype(&freeifaddrs)> ifaddrs_ptr(nullptr, &freeifaddrs);
    if (getifaddrs(&if_addr_struct) == -1)
    { //使用if_addr_struct绑定
        return ip_addresses;
    }
    ifaddrs_ptr.reset(if_addr_struct); //将智能指针重新指向绑定的那个指针
                                       //现在智能指针就管理着if_addr_struct 这个结构体
                                       //我们现在使用if_addr_struct 来处理即可，后续智能指针会自动清理资源
    for (ifaddrs *ifa = if_addr_struct; ifa; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr)
        {
            continue;
        }
        void *tmp_addr_ptr = nullptr;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            // check it is IP4 and not a loopback address
            tmp_addr_ptr = &((sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char address_buffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmp_addr_ptr, address_buffer, INET_ADDRSTRLEN);
            ip_addresses.emplace_back(address_buffer);
        }
        else if (ifa->ifa_addr->sa_family == AF_INET6)
        {
            // check it is IPv6 and not a loopback address
            tmp_addr_ptr = &((sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
            char address_buffer[INET6_ADDRSTRLEN];
            inet_ntop(AF_INET6, tmp_addr_ptr, address_buffer, INET6_ADDRSTRLEN);
            ip_addresses.emplace_back(address_buffer);
        }
    }

    return ip_addresses;
}
void demoReset()
{
    GetLocalIpAddresses();
}
void testDecltype()
{

}
int main()
{
    testReset();
    return 0;
}