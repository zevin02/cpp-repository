#include<iostream>
using namespace std;
#include<cstdio>
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


//char& operator[] (size_t pos);这里的引用返回是因为这个数组是在堆上开辟的，出了作用域还在，并且可以对其中的字符进行修改，或者调用，还可以减少拷贝（不是主要目的）


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


  //计算最后一个单词的长度如“hello world  ”g

  int lengthOfLastWord(string s) {
            int end=s.size()-1;
                    while(s[end]==' ')
                    {
                                  s.erase(end,1);//无法使用
                                              end--;
                                                      
                                                      
                    }
                            
                    size_t pos=s.rfind(" ");

                    string sub=s.substr(pos+1);
                    return sub.size();



                        
  }




};

//遍历，1.迭代器2.范围for
void test_string1()
{
  
string s1("hello");
string::iterator it=s1.begin();//s1.begin(),是第一个数据的地址，s1.end（）是最后一个数据的后一个的地址
//这个iterator是定义在string里面，it现在指向了第一个数据的地址
//现在可以先想象成一个像指针一样的类型
//
while(it!=s1.end())//直到结尾就结束了，但是不建议用<
{
  cout<<*it<<" ";//*就是取他的数据
  ++it;//到下一个地址
}
cout<<endl;
//除了可以读还可以写
 it=s1.begin();//s1.begin(),是第一个数据的地址，s1.end（）是最后一个数据的后一个的地址
//这个iterator是定义在string里面，it现在指向了第一个数据的地址
//现在可以先想象成一个像指针一样的类型
//
while(it!=s1.end())//直到结尾就结束了
{
  *it-=1;//*就是取他的数据
  ++it;//到下一个地址
}
cout<<endl;


//范围for,auto可以自动识别
//for(auto e:s1)//把s1里面每个字符取出来赋值给e，不需要自己++，自动判断结束
//{
//  cout<<e<<" ";
//}
cout<<endl;

//要修改就要用引用
//for(auto& e:s1)
//{
//  e-=1;
//}
cout<<endl;

//反向迭代器
//倒着遍历
string::reverse_iterator rit=s1.rbegin();//rbegin（），是最后一个数据的地址
//为了简化代码也可以直接auto推到
//
//auto  rit=s1.rbegin()
//
while(rit!=s1.rend())//rend（）是第一个数据的前一个地址
{
  cout<<*rit<<" ";//olleh，反过来遍历
  ++rit;//反向迭代器的++，是往左走的
}
cout<<endl;

//迭代器遍历的意义是什么呢：所有的容器都可以用迭代器这种访问修改
//1.对于string类来说，利用[]都足够好用,确实可以不用迭代器
//2。对于其他容器（数据结构）也可以使用，如list，map，set，这些是不支持[]，因为只有像数组一样的东西才支持[]遍历和下标，
//结论：：对于string得会用迭代器，但是我们还是喜欢下标加[],

//还有const迭代器，普通迭代器是可读可写的
string cstr("hello world");
//funcion(cstr);
string::const_iterator re=s1.begin();//只读不写，同理还有反向迭代器
//cbegin（）就是const迭代器，但是我们平时都不太用，

}



//对于容量的函数
void test_string3()
{
string s1;
s1.reserve(100);//可以设置容量的大小，容量就是100，加上原来的容量
string s2;
s2.resize(100,'x');//也是可以设置容量的大小，同时还可以对其进行初始化，如将s1有效数据的后面全部设置成x，如果没有第二个参数，则默认是‘\0’
}





//对于find，c_str ,rfind的认识与理解
void test_string2()
{

string s2="hello world";
cout<<s2.c_str()<<endl;//将string转变成c语言的形式字符串，char*，以\0截至
string file("test.txt");
//我们要以c语言的形式打开一个文件
FILE* fout=fopen(s2.c_str(),"w"); //fopen第一个参数是char*，所以用这函数

//要求取出文件的后缀

  size_t pos=file.find('.');//在file里面查找‘x’的位置，find的返回值是size_t,下标从0开始，查找第一个符合的坐标，否则就返回-1
  
string s1(file,pos);
cout<<s1<<endl;
if(pos!=string::npos)
{
  string suffix=file.substr(pos);
cout<<suffix<<endl;
}

//rfind()//可以从后面完前找，找到第一个.，方便找后缀名
//https://blog.csdn.net/m0_61567378?spm=1000.2115.3001.5343
string url("http://blog.csdn.net/m0_61567378?spm=1000.2115.3001.5343");
//找协议头
size_t pos1=url.find(':');//：前面的就是协议头

string protocol=url.substr(0,pos1-0);//取得字串就是从0开始，到pos1位置，长度为pos1的字串，也就是http
cout<<protocol<<endl;

//找域名，
size_t pos2=url.find('/',pos1+3);//find默认从0开始找，现在我们给定他从pos1+3位置处开始找，也就是b开始，往后找，找到/的位置

string domain=url.substr(pos1+3,pos2-pos1-3);
cout<<domain<<endl;

//统一资源定位
string uri=url.substr(pos2+1);
cout<<uri<<endl;


}



//
void test_string4()
{

//insert不太推荐用,O(n),效率低

  string s="hell";
  s.insert(0,"owlod");//在头上插入一个owlod，是从第0个位置往后插入
  s.insert(0,1,'x');//在头上插入一个x,是
  s.insert(4,"xx");//从第4个位置往后插入xx
  cout<<s<<endl;

  //要挪动数据效率很低，
  s.erase(4,2);//从4位置，删除两个长度的字符
  cout<<s<<endl;
  s.erase(s.size()-1,1);//尾删
  s.erase(3);//第二个参数不给值就后面全部都删除了

  //尾删也可以
//s.pop_back();

//输入一整行的数据，包括‘ ’
getline(cin,s);//第一个参数是流 


}


int main()
{
//	init();
//	func();
//	operatoracess();
//	add();
//	Solution sl;

//	sl.reverseOnlyLetters("Test1ng-Leet=code-Q!");
//test_string1();
//test_string3();
//test_string2();
//test_string4();
Solution ts;
string s="hello world  ";
int k=ts.lengthOfLastWord(s);
cout<<k<<endl;
return 0;

}



















