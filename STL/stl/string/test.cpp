#include<iostream>
using namespace std;
#include<cstdio>
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


//���� --ֵ--���Ž���ӳ���ϵ--���������ֵ�ͷ��Ž�����Ӧ��ϵ�� 
// ASCILL�����---��ʾӢ�ı���
// unicode ---������ascill����ʾȫ�������ֱ���
//�ְ���utf -8��utf-16 
//gbk        --     �й��Լ����������ı����
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
	string s1;//�޵��ù��캯��
	string s2("hello world");//���캯��
	string s3(s2);//��������
	//cin >> s1;
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	//substring (3)	

	//string(const string & str, size_t pos, size_t len = npos);
	//�����ִ����г�ʼ����pos�Ǵ�0��ʼ����string�����Ⱥ���len�����Ƚ��п���


	string s4(s2, 2, 6);
	cout << s4 << endl;//llo wo
	string s5(s2, 2);//Ĭ�ϴ�����Ϊ2�ĵط������ȡ���е�s2
	cout << s5 << endl;//ello world

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
	s1.clear();//����Ч���ݶ�������,�ռ䱣������ɿ��ַ�����0���ַ�
	cout << s1 << endl;
	cout << s1.capacity() << endl;
	if (s1.empty())//�жϴ��ַ����Ƿ�Ϊ�գ����Ƿ񳤶�Ϊ0
	{
		cout << "not" << endl;
	}


}


//char& operator[] (size_t pos);��������÷�������Ϊ����������ڶ��Ͽ��ٵģ������������ڣ����ҿ��Զ����е��ַ������޸ģ����ߵ��ã������Լ��ٿ�����������ҪĿ�ģ�


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
		cout << s1.at(i) << endl;//at�����쳣������,���黹��ʹ��[ ]
	}
	cout << endl;

}

//���ַ�������β�������ַ����ַ���
void add()
{
	string s;
	s.push_back('a');
	s.append("bcde");//β��bcd
	cout << s << endl;//abcd
	s += '!';//Ҳ����������������ؽ���ʵ��β�壬�Ƽ�,abcd!
}


//ֻ�����ַ�
//abc-bcd-qwlkj��� jkl-wqd-cbcba  
//
class Solution {
public:
  //�������һ�����ʵĳ����硰hello world  ��g

  int lengthOfLastWord(string s) {
            int end=s.size()-1;
                    while(s[end]==' ')
                    {
                                  s.erase(end,1);//�޷�ʹ��
                                              end--;
                                                      
                                                      
                    }
                            
                    size_t pos=s.rfind(" ");

                    string sub=s.substr(pos+1);
                    return sub.size();



                        
  }




};

//������1.������2.��Χfor
void test_string1()
{
  
string s1("hello");
string::iterator it=s1.begin();//s1.begin(),�ǵ�һ�����ݵĵ�ַ��s1.end���������һ�����ݵĺ�һ���ĵ�ַ
//���iterator�Ƕ�����string���棬it����ָ���˵�һ�����ݵĵ�ַ
//���ڿ����������һ����ָ��һ��������
//
while(it!=s1.end())//ֱ����β�ͽ����ˣ����ǲ�������<
{
  cout<<*it<<" ";//*����ȡ��������
  ++it;//����һ����ַ
}
cout<<endl;
//���˿��Զ�������д
 it=s1.begin();//s1.begin(),�ǵ�һ�����ݵĵ�ַ��s1.end���������һ�����ݵĺ�һ���ĵ�ַ
//���iterator�Ƕ�����string���棬it����ָ���˵�һ�����ݵĵ�ַ
//���ڿ����������һ����ָ��һ��������
//
while(it!=s1.end())//ֱ����β�ͽ�����
{
  *it-=1;//*����ȡ��������
  ++it;//����һ����ַ
}
cout<<endl;


//��Χfor,auto�����Զ�ʶ��
//for(auto e:s1)//��s1����ÿ���ַ�ȡ������ֵ��e������Ҫ�Լ�++���Զ��жϽ���
//{
//  cout<<e<<" ";
//}
cout<<endl;

//Ҫ�޸ľ�Ҫ������
//for(auto& e:s1)
//{
//  e-=1;
//}
cout<<endl;

//���������
//���ű���
string::reverse_iterator rit=s1.rbegin();//rbegin�����������һ�����ݵĵ�ַ
//Ϊ�˼򻯴���Ҳ����ֱ��auto�Ƶ�
//
//auto  rit=s1.rbegin()
//
while(rit!=s1.rend())//rend�����ǵ�һ�����ݵ�ǰһ����ַ
{
  cout<<*rit<<" ";//olleh������������
  ++rit;//�����������++���������ߵ�
}
cout<<endl;

//������������������ʲô�أ����е������������õ��������ַ����޸�
//1.����string����˵������[]���㹻����,ȷʵ���Բ��õ�����
//2�������������������ݽṹ��Ҳ����ʹ�ã���list��map��set����Щ�ǲ�֧��[]����Ϊֻ��������һ���Ķ�����֧��[]�������±꣬
//���ۣ�������string�û��õ��������������ǻ���ϲ���±��[],

//����const����������ͨ�������ǿɶ���д��
string cstr("hello world");
//funcion(cstr);
string::const_iterator re=s1.begin();//ֻ����д��ͬ�����з��������
//cbegin��������const����������������ƽʱ����̫�ã�

}



//���������ĺ���
void test_string3()
{
string s1;
s1.reserve(100);//�������������Ĵ�С����������100������ԭ��������
string s2;
s2.resize(100,'x');//Ҳ�ǿ������������Ĵ�С��ͬʱ�����Զ�����г�ʼ�����罫s1��Ч���ݵĺ���ȫ�����ó�x�����û�еڶ�����������Ĭ���ǡ�\0��
}





//����find��c_str ,rfind����ʶ������
void test_string2()
{

string s2="hello world";
cout<<s2.c_str()<<endl;//��stringת���c���Ե���ʽ�ַ�����char*����\0����
string file("test.txt");
//����Ҫ��c���Ե���ʽ��һ���ļ�
//FILE* fout=fopen(s2.c_str(),"w"); //fopen��һ��������char*���������⺯��

//Ҫ��ȡ���ļ��ĺ�׺

  size_t pos=file.find('.');//��file������ҡ�x����λ�ã�find�ķ���ֵ��size_t,�±��0��ʼ�����ҵ�һ�����ϵ����꣬����ͷ���-1
  
string s1(file,pos);
cout<<s1<<endl;
if(pos!=string::npos)
{
  string suffix=file.substr(pos);
cout<<suffix<<endl;
}

//rfind()//���ԴӺ�����ǰ�ң��ҵ���һ��.�������Һ�׺��
//https://blog.csdn.net/m0_61567378?spm=1000.2115.3001.5343
string url("http://blog.csdn.net/m0_61567378?spm=1000.2115.3001.5343");
//��Э��ͷ
size_t pos1=url.find(':');//��ǰ��ľ���Э��ͷ

string protocol=url.substr(0,pos1-0);//ȡ���ִ����Ǵ�0��ʼ����pos1λ�ã�����Ϊpos1���ִ���Ҳ����http
cout<<protocol<<endl;

//��������
size_t pos2=url.find('/',pos1+3);//findĬ�ϴ�0��ʼ�ң��������Ǹ�������pos1+3λ�ô���ʼ�ң�Ҳ����b��ʼ�������ң��ҵ�/��λ��

string domain=url.substr(pos1+3,pos2-pos1-3);
cout<<domain<<endl;

//ͳһ��Դ��λ
string uri=url.substr(pos2+1);
cout<<uri<<endl;


}



//
void test_string4()
{

//insert��̫�Ƽ���,O(n),Ч�ʵ�

  string s="hell";
  s.insert(0,"owlod");//��ͷ�ϲ���һ��owlod���Ǵӵ�0��λ���������
  s.insert(0,1,'x');//��ͷ�ϲ���һ��x,��
  s.insert(4,"xx");//�ӵ�4��λ���������xx
  cout<<s<<endl;

  //ҪŲ������Ч�ʺܵͣ�
  s.erase(4,2);//��4λ�ã�ɾ���������ȵ��ַ�
  cout<<s<<endl;
  s.erase(s.size()-1,1);//βɾ
  s.erase(3);//�ڶ�����������ֵ�ͺ���ȫ����ɾ����

  //βɾҲ����
//s.pop_back();

//����һ���е����ݣ������� ��
getline(cin,s);//��һ���������� 


}



void test_string5()
{

  string s1="hello";
  string s2="string";
  cout<<(s1<s2)<<endl;//h<s���Ծ���С��

  cout<<("hello"<s2)<<endl;//char*��Ҳ���ԱȽ�
  cout<<(string("hello")<s2)<<endl;//����Ҳ�ǿ��Ե�
}



//�ַ��������ε�ת��


void test_string6()
{

  int val=stoi("1234");//ת���int
  cout<<val<<endl;//1234
  double val1=stod("123");
  //ת����ַ���
  string str=to_string(12.345);
string s=to_string(123456);


  string str = to_string(12.345);

}


//ǳ���������ֵ��������ÿ���ֽ�һ�𿽱�
//����ָ�����͵ľͲ����Կ�ǳ����
//ǳ��������ҵ�����ֶ�û�ģ�����ȫȫ�ĳ�
//������ǳ���ҵ�������֣�����ȫ�ĳ�
//

class  my_string 
{
  private:
    char* _str;
  public:
    //���캯��
    my_string(const char* str)
    :_str(new char[strlen(str)+1])
    {
strcpy(_str,str);
    }

    //��������Ҫ�����
    my_string(const my_string& s)
      :_str(new char[strlen(str)+1])
    {
      strcpy(_str,s.str);
    }

}

void test_string7()
{


}

void test()
{
  string s("aaaaaa");
  s.resize();

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
//int k=ts.lengthOfLastWord(s);
//cout<<k<<endl;
//test_string6();

string s1 = "A man, a plan, a canal: Panama";
test();
//isPalindrome(s1);

return 0;

}



















