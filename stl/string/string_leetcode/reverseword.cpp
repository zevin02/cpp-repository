#include<iostream>
using namespace std;
#include<string>

class Solution {
  
  public:
    string reverse(string s, int left, int right)
    {
        int begin = left;
          int end = right;
            while (begin <= end)
            {
                  swap(s[begin], s[end]);
                      begin++;
                          end--;
                            
            }
              return s;

    }
    string reverseWords(string s) {
        int end = s.size() - 1;
          size_t pos = s.find(' ');
            int befpos = -1;

              while (pos != string::npos)
              {

                    s = reverse(s, befpos + 1, pos - 1);
                        befpos = pos;
                            pos = s.find(" ", befpos + 1);
                              
              }
                return reverse(s, befpos + 1, end);
                  

    }

};


void test()
{
  Solution st;
  string s="s'teL ekat edoCteeL tsetnoc";
 string ret=st.reverseWords(s);
 cout<<ret<<endl;
  
}
int main()
{
  test();
  return 0;
}

