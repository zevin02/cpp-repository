#include<iostream>
using namespace std;

//string���ǹ����ַ�������
#include<string>

//�����涨��
template<class T>
class basic_string
{
private:
	T* _str;
	//...
};


//���� --ֵ--���Ž���ӳ���ϵ--�������ֵ�ͷ��Ž�����Ӧ��ϵ�� 
// ASCILL�����---��ʾӢ�ı���
// unicode ---������ascill����ʾȫ�������ֱ���
//�ְ���utf -8��utf-16 
//gbk        --     �й��Լ��������ı����
// ���ֿ�����2���ֽڣ�
// 
//typrdef basic_string<char> string,�����õ���typedef������ģ�ģ���

//int main()
//{
//	string s1("hello");
//	char str2[] = "�Է�";
//	cout << sizeof(char) << endl;
//	cout << sizeof(wchar_t) << endl;//2���ֽڣ�wstring
//
//	return 0;
//}



//��ʼ��

void init()
{
	string s1;
	string s2("hello world");
	string s3(s2);
	//cin >> s1;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	//substring (3)	

	//string(const string & str, size_t pos, size_t len = npos);
	//�����ִ����г�ʼ����pos�Ǵ�0��ʼ����string�����Ⱥ���len�����Ƚ��п���


	string s4(s2, 2, 6);
	cout << s4 << endl;
	string s5(s2, 2);
	cout << s5 << endl;

	//string (const char* s, size_t n);
	string s7("hello world", 3);//ȡǰ3���ַ�
	cout << s7 << endl;
	//string(size_t n, char c);����Ūn��c
	string s8(3, '!');//������
}


void func()
{
	string s1("hello");
	//�����㡮\0��������������stringûʲô����size�Ǻ����Ϊ�˱�֤������һ����
	cout << s1.size() << endl;//5
	cout << s1.length() << endl;//5
	cout << s1.max_size() << endl;//ûʲô����
	cout << s1 << endl;
								  //��������
	cout << s1.capacity() << endl;//15
	s1.clear();//����Ч���ݶ������,�ռ䱣������ɿ��ַ�����0���ַ�
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	if (s1.empty())//�жϴ��ַ����Ƿ�Ϊ�գ����Ƿ񳤶�Ϊ0
	{
		cout << "not" << endl;
	}


}


//char& operator[] (size_t pos);��������÷�������Ϊ����������ڶ��Ͽ��ٵģ������������ڣ����ҿ��Զ����е��ַ������޸ģ������Լ��ٿ�����������ҪĿ�ģ�
void operatoracess()
{
	string s1("hello world");
	for (size_t i = 0; i < s1.length(); i++)
	{
		cout << s1[i];//[]�Ƕ�����ֹ���򣬼�����
		s1[i] += 1;
	}
	cout << endl;
	for (size_t i = 0; i < s1.length(); i++)
	{
		s1.at(i) -= 1;//��������һ����
		cout << s1.at(i) << endl;//at�����쳣������
	}
	cout << endl;

}

void add()
{
	string s;
	s.push_back('a');
	s.append("bcde");//β��bcd
	cout << s << endl;
	s += '!';//Ҳ����������������ؽ���ʵ��β�壬�Ƽ�
}


class Solution {
public:
	bool isletter(char ch)
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
			return true;
		else return false;

	}
	string reverseOnlyLetters(string s) {
		int begin = 0, end = s.size() - 1;
		while (begin <= end)
		{
			if (isletter(s[begin]) && isletter(s[end]))//yes
			{
				swap(s[begin], s[end]);
				begin++;
				end--;
			}
			else if (isletter(s[begin]) && (!isletter(s[end])))
			{
				end--;
			}
			else if (!isletter(s[begin]) && isletter(s[end]))
			{
				begin++;
			}
			else
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