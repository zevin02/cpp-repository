
#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
//给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
//
//说明：本题中，我们将空字符串定义为有效的回文串。
//

bool isletter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c<'10' && c >='0'))
	{
		return true;
	}
	return false;
}

//验证回文
bool isPalindrome(string s) {
	string s1;
//	auto it = s.begin();
  string::iterator it =s.begin();
	while (it != s.end())
	{
		if (isletter(*it))
		{
			if (((*it) >= 'A' && (*it) <= 'Z'))
			{
				(*it) += 32;
			}
			s1 += (*it);
			it++;
		}
		else
		{
			it++;
		}
	}
	cout << s1 << endl;
	string s2 = s1;
	reverse(s1.begin(), s1.end());
	if (s2 == s1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void test()
{
  string s="race a car";
 if( isPalindrome(s))
 {
   cout<<"yes"<<endl;
 }
 else 
 {
   cout<<"no"<<endl;
 }


}
int main()
{
  test();
  return 0;
}


