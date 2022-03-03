//大数相加
//12334+23
//

#include<iostream>
using namespace std;
#include<string>


class Solution {
  public:
    string addStrings(string num1, string num2) {
      int end1=num1.size()-1;//最后一位
      int end2=num2.size()-1;
      int next=0;//进位
      string retstr;
      while(end1>=0||end2>=0)//两个都走完才走完
      {
            int x1=0;
                if(end1>=0)
                {
                  x1=num1[end1]-'0';
                      --end1;
                          
                }
                int x2=0;
                if(end2>=0)
                {
                      
                  x2=num2[end2]-'0';
                  --end2;

                }
                int ret=x1+x2+next;
                if(ret>9)
                {
                      next=1;
                          ret-=10;

                }
                else
                {
                      next=0;//没有进位就置为0

                }
                retstr.insert(retstr.begin(),ret+'0');



      }

      if(next==1)
      {
            retstr.insert(retstr.begin(),'1');

      }

      return retstr;
          
    }

};


void test()
{
  Solution st;
  string num1="1231";
  string num2="1111";

  string ret=st.addStrings(num1,num2);
  cout<<ret<<endl;
  
}

int main()
{
test();
  return 0;
}
