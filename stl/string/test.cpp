#include<iostream>
using namespace std;

//string就是管理字符串的类
#include<string>

//库里面定义
template<class T>
class basic_string
{
private:
	T* _str;
	//...
};


//编码 --值--符号建立映射关系--编码表（用值和符号建立对应关系） 
// ASCILL编码表---表示英文编码
// unicode ---（包含ascill）表示全世界文字编码
//又包含utf -8，utf-16 
//gbk        --     中国自己量身定做的编码表
// 汉字可以用2个字节，
// 
//typrdef basic_string<char> string,我们用的是typedef后出来的，模板的

//int main()
//{
//	string s1("hello");
//	char str2[] = "吃饭";
//	cout << sizeof(char) << endl;
//	cout << sizeof(wchar_t) << endl;//2个字节，wstring
//
//	return 0;
//}



//初始化

void init()
{
	string s1;//无调用构造函数
	string s2("hello world");//构造函数
	string s3(s2);//拷贝构造
	//cin >> s1;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	//substring (3)	

	//string(const string & str, size_t pos, size_t len = npos);
	//利用字串进行初始化，pos是从0开始，从string里面先后数len个长度进行拷贝


	string s4(s2, 2, 6);
	cout << s4 << endl;//llo wo
	string s5(s2, 2);//默认从坐标为2的地方往后截取所有的s2
	cout << s5 << endl;//ello world

	//string (const char* s, size_t n);
	string s7("hello world", 3);//取前3个字符
	cout << s7 << endl;
	//string(size_t n, char c);连续弄n个c
	string s8(3, '!');//！！！
}


void func()
{
	string s1("hello");
	//不计算‘\0’，这两个对于string没什么区别，size是后出现为了保证容器的一致性
	cout << s1.size() << endl;//5
	cout << s1.length() << endl;//5
	cout << s1.max_size() << endl;//没什么意义
	cout << s1 << endl;
								  //计算容量
	cout << s1.capacity() << endl;//15
	s1.clear();//把有效数据都清理掉,空间保留，变成空字符串，0个字符
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	if (s1.empty())//判断此字符串是否为空，即是否长度为0
	{
		cout << "not" << endl;
	}


}


//char& operator[] (size_t pos);这里的引用返回是因为这个数组是在堆上开辟的，出了作用域还在，并且可以对其中的字符进行修改，还可以减少拷贝（不是主要目的）
void operatoracess()
{
	string s1("hello world");
	for (size_t i = 0; i < s1.length(); i++)
	{
		cout << s1[i];//[]是断言终止程序，检查错误
		s1[i] += 1;
	}
	cout << endl;
	for (size_t i = 0; i < s1.length(); i++)
	{
		s1.at(i) -= 1;//和上面是一样的
		cout << s1.at(i) << endl;//at是抛异常检查错误,建议还是使用[ ]
	}
	cout << endl;

}

//对字符串进行尾部添加字符或字符串
void add()
{
	string s;
	s.push_back('a');
	s.append("bcde");//尾插bcd
	cout << s << endl;//abcd
	s += '!';//也可以利用运算符重载进行实现尾插，推荐,abcd!
}


//只交换字符
//abc-bcd-qwlkj变成 jkl-wqd-cbcba  
//
class Solution {
public:
	bool isletter(char ch)//判断是否为字母
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
			return true;
		else return false;

	}
	string reverseOnlyLetters(string s) {
		int begin = 0, end = s.size() - 1;//利用双指针法进行操作
		while (begin <= end)//两者相遇那就停止了
		{
			if (isletter(s[begin]) && isletter(s[end]))//yes,前后两个都是字母
			{
				swap(s[begin], s[end]);
				begin++;//
				end--;
			}
			else if (isletter(s[begin]) && (!isletter(s[end])))//前面是，后面不是
			{
				end--;
			}
			else if (!isletter(s[begin]) && isletter(s[end]))//前不是，后是
			{
				begin++;//begin往后走
			}
			else//都不是，begin往后走，end往前走
			{
				begin++;
				end--;
			}

		}
		return s;
	}

};
int main()
{
	init();
	func();
	operatoracess();
	add();
	Solution sl;

	sl.reverseOnlyLetters("Test1ng-Leet=code-Q!");
	return 0;
}
