#include<map>
#include<algorithm>
#include<iostream>
using namespace std;
#include<set>
#include<vector>
struct cnt_word
{
    string word;
    int cnt;
}a[100];
bool cmp(cnt_word a,cnt_word b)
{
    if(a.cnt==b.cnt)
    {
        //按字典序列从小到大排序
        return a.word<b.word;
    }
    return a.cnt>b.cnt;//按出现次数从大到小排序
}
int main()
{
    //使用map去映射
    map<string,int>res;//用string去映射int
    int n;
    cin>>n;
    while(n--)
    {
        string word;
        cin>>word;
        if(res[word]==0)//不曾出现过
        {
            res[word]++;
        }
        //已经出现过了
        else 
        {
            res[word]++;
        }       
    }
    //统计完成
    //对内部元素进行排序
    auto it=res.begin();
   int i=0;
    while(it!=res.end())
    {
        a[i].cnt=(*it).second;
        a[i].word=(*it).first;
        i++;
        it++;
    }
    sort(a,a+i,cmp);
    //map是按照字典序，建的字典序列越高，就排的越考前
    cout<<a[0].word<<endl;
    return 0;
}
