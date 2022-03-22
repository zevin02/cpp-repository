#include<iostream>
using namespace std;
#include<stack>
#include<queue>
//后进先出

void test1()
{
  stack<int> s;
  s.push(2);//入栈
  s.push(3);
  s.push(4);
  s.push(5);
  //不支持迭代器,如果支持迭代器的话，就不能支持后进先出
  while(!s.empty())
  {
    cout<<s.top()<<" ";
    s.pop();
  }
  cout<<endl;

}
void test2()
{
  queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  while(!q.empty())
  {
    cout<<q.front()<<" ";//队头
    cout<<q.back()<<" ";//队尾
    q.pop();//头删
  }
}
int main()
{
  test1();
  test2();
  return 0;
}
