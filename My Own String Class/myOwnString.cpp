#include <iostream>
#include <string>
#include <conio.h>		//getch()函数要包含此头文件
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;
  //若在VC6下运行该程序，需将 include<iostream> 改为 include<iostream.h> ,且将 using namespace std; 改为 using std::string; 。


/* ----基类TString的定义  与  各成员函数  的实现---- */
class TString
{
protected:
	char *content;
	int len;
public:
	TString(char *str=NULL);	/* 定义构造函数 */
	~TString();			/* 定义析构函数 */
};

TString::TString(char *str)		//不再带缺省值
{
	// 首先考虑str为NULL或str为空串的情况
	if (str==NULL || str[0]==0) 
	{
		content = NULL;
		len     = 0;
	}
	else 
	{
		len     = strlen(str);
		content = new char[len+1];
		if (content)
			strcpy(content, str); //含'\0'拷贝
		else 
		{
			/* 申请不到空间的情况 */
			content = NULL;
			len     = 0;
		}
	}
}

TString::~TString()
{
	if (content)
		delete content;
}


/* ----派生类TString_1的定义  与  各成员函数和友元函数  的实现---- */
class TString_1:public TString
{
	//不需再定义新的数据成员，需定义新的成员函数，以实现：
	//    各种数据类型对该类进行初始化、类的输入和输出
public:
	TString_1(char *str=NULL):TString(str){}	/* 定义构造函数 */
	
	TString_1(const TString_1 &);               /* 定义复制构造函数*/
	friend istream & operator>>(istream &,TString_1 &);
	friend ostream & operator<<(ostream &,TString_1 &);
};

TString_1::TString_1(const TString_1 &s)
{
	len=s.len;
	content=new char[len+1];
	if (content==NULL)
	{
		cout<<"空间不足"<<endl;
		len=0;
	}
	else
		strcpy(content,s.content);
}

istream & operator>>(istream &in,TString_1 &s)
{
	char *p=new char[20],*p1=p;
	int n=0;
	if (p==NULL)
	{
		cout<<"空间不够"<<endl;
		return in;
	}
	in>>p1;
	while (*p1&&*p1!=' ')
	{
		n++;
		p1++;
	}
	if (s.content!=NULL)
		delete s.content;
	s.content=new char[n+1];
	if (s.content==NULL)
	{
		cout<<"空间不够"<<endl;
		s.len=0;
	}
	else
	{
		strncpy(s.content,p,n);
		*(s.content+n)=0;
		s.len=n;
	}
	delete []p;
	return in;
}

ostream & operator<<(ostream &out,TString_1 &s)
{
	if (s.content==NULL)
		out<<"<NULL>";
	else
		out<<s.content;
	return out;
}


/* ----派生类TString_2的定义  与  各成员函数和友元函数  的实现---- */
class TString_2:public TString_1
{
	//不需再定义新的数据成员，需定义新的成员函数，以实现：
	//    各种数据类型对该类进行赋值、两个类的字符串之间的拼接
public:
	TString_2(char *str=NULL):TString_1(str){}	/* 定义构造函数 */
	
	TString_2(const TString_2 &);               /* 定义复制构造函数*/
	
	TString_2 & operator=(const TString_2 &);
	friend TString_2 operator+(const TString_2 &,const TString_2 &);
};

TString_2::TString_2(const TString_2 &s)
{
	len=s.len;
	content=new char[len+1];
	if (content==NULL)
	{
		cout<<"空间不足"<<endl;
		len=0;
	}
	else
		strcpy(content,s.content);
}

TString_2 & TString_2::operator=(const TString_2 &s)
{
	if (s.content==NULL)
	{
		content=NULL;
		len=0;
	}
	else
	{
		if (content!=NULL)
			delete content;
		len=s.len;
		content=new char[len+1];
		if (content==NULL)
		{
			cout<<"空间不足"<<endl;
			len=0;
		}
		else
			strcpy(content,s.content);
	}
	return *this;
}

TString_2 operator+(const TString_2 &s1,const TString_2 &s2)
{
	TString_2 s;
	if (s1.content==NULL&&s2.content==NULL)
		return s;
	s.content=new char[s1.len+s2.len+1];
	if (s.content==NULL)
	{
		cout<<"空间不足"<<endl;
		return s;
	}
	if (s1.content!=NULL)
		strcpy(s.content,s1.content);
	else
		*s.content=0;
	if (s2.content!=NULL)
		strcat(s.content,s2.content);
	s.len=s1.len+s2.len;
	return s;
}


/* ----派生类TString_3的定义  与  各成员函数和友元函数  的实现---- */
class TString_3:public TString_2
{
	//不需再定义新的数据成员，需定义新的成员函数，以实现：
	//    两个类中字符串的比较、求取类中字符串的长度、用"+="运算符连接一个类和一个字符数组
public:
	TString_3(char *str=NULL):TString_2(str){}	/* 定义构造函数 */
	
	TString_3(const TString_3 &);               /* 定义复制构造函数*/

	int length();			/* 定义length()函数 */
	
	TString_3 & operator=(const TString_3 &);
	friend TString_3 operator+(const TString_3 &,const TString_3 &);
	TString_3& operator+=(char *);
	friend bool operator<(const TString_3 &,const TString_3 &);
	friend bool operator<=(const TString_3 &,const TString_3 &);
	friend bool operator>(const TString_3 &,const TString_3 &);
	friend bool operator>=(const TString_3 &,const TString_3 &);
	friend bool operator==(const TString_3 &,const TString_3 &);
	friend bool operator!=(const TString_3 &,const TString_3 &);
	friend int TStringLen(TString_3 &);
};

TString_3::TString_3(const TString_3 &s)
{
	len=s.len;
	content=new char[len+1];
	if (content==NULL)
	{
		cout<<"空间不足"<<endl;
		len=0;
	}
	else
		strcpy(content,s.content);
}

TString_3 & TString_3::operator=(const TString_3 &s)
{
	if (s.content==NULL)
	{
		content=NULL;
		len=0;
	}
	else
	{
		if (content!=NULL)
			delete content;
		len=s.len;
		content=new char[len+1];
		if (content==NULL)
		{
			cout<<"空间不足"<<endl;
			len=0;
		}
		else
			strcpy(content,s.content);
	}
	return *this;
}

TString_3 operator+(const TString_3 &s1,const TString_3 &s2)
{
	TString_3 s;
	if (s1.content==NULL&&s2.content==NULL)
		return s;
	s.content=new char[s1.len+s2.len+1];
	if (s.content==NULL)
	{
		cout<<"空间不足"<<endl;
		return s;
	}
	if (s1.content!=NULL)
		strcpy(s.content,s1.content);
	else
		*s.content=0;
	if (s2.content!=NULL)
		strcat(s.content,s2.content);
	s.len=s1.len+s2.len;
	return s;
}

TString_3& TString_3::operator+=(char *s)
{
	if (content!=NULL)
	{
		char *p;
		p=new char[len+1];
		strcpy(p,content);
		delete content;
		int L=strlen(s);
		content=new char[len+L+1];
		strcpy(content,p);
		strcat(content,s);
		len+=L;
		delete p;
		return *this;
	}
	else
	{
		len=strlen(s);
		content=new char[len+1];
		strcpy(content,s);
		return *this;
	}
}

bool operator<(const TString_3 &s1,const TString_3 &s2)
{
	if (s1.content==NULL)
		if (s2.content==NULL)
			return false;
		else
			return true;
	if (s2.content==NULL)
		return false;
	int flag=strcmp(s1.content,s2.content);
	if (flag<0)
		return true;
	else
		return false;
}

bool operator<=(const TString_3 &s1,const TString_3 &s2)
{
	if (s1.content==NULL)
		return true;
	if (s2.content==NULL)
		return false;
	int flag=strcmp(s1.content,s2.content);
	if (flag<=0)
		return true;
	else
		return false;
}

bool operator>(const TString_3 &s1,const TString_3 &s2)
{
	if (s1.content==NULL)
		return false;
	if (s2.content==NULL)
		return true;
	int flag=strcmp(s1.content,s2.content);
	if (flag>0)
		return true;
	else
		return false;
}

bool operator>=(const TString_3 &s1,const TString_3 &s2)
{
	if (s1.content==NULL)
		if (s2.content==NULL)
			return true;
		else
			return false;
	if (s2.content==NULL)
		return true;
	int flag=strcmp(s1.content,s2.content);
	if (flag>=0)
		return true;
	else
		return false;
}

bool operator==(const TString_3 &s1,const TString_3 &s2)
{
	if (s1.content==NULL)
		if (s2.content==NULL)
			return true;
		else
			return false;
	if (s2.content==NULL)
		return false;
	int flag=strcmp(s1.content,s2.content);
	if (flag==0)
		return true;
	else
		return false;
}

bool operator!=(const TString_3 &s1,const TString_3 &s2)
{
	if (s1.content==NULL)
		if (s2.content==NULL)
			return false;
		else
			return true;
	if (s2.content==NULL)
		return true;
	int flag=strcmp(s1.content,s2.content);
	if (flag!=0)
		return true;
	else
		return false;
}

int TStringLen(TString_3 &s)
{
	return s.len;
}

int TString_3::length()
{
	return len;
}


/* ----改进类TString_wonderful的定义与各成员函数的实现，该类各运算符重载部分的执行效率远高于以上各类---- */
//     主要的改进是把字符串的存取、拼接和比较用链表来实现，避免了反复开辟和释放超大空间带来的时间和空间开销
class TString_wonderful
{
public:
	TString_wonderful();
	int length();
	TString_wonderful &operator+=(char*);
	int operator==(char*);
	int operator!=(char*);
	~TString_wonderful();
private:
	struct Link
	{
		char *data;
		int part_len;
		Link *next;
	} *head, *tail;
	int len;
};

TString_wonderful::TString_wonderful()
{
	len=0;
	head=tail=NULL;
}

int TString_wonderful::length()
{
	return len;
}

TString_wonderful &TString_wonderful::operator+=(char *str)
{
	if (str==NULL||str[0]=='\0')
		return *this;
	int len_incr=strlen(str);
	if (head==NULL)
	{
		head=tail=new Link;
		if (head!=NULL&&(head->data=new char[len_incr+1])!=NULL)
		{
			head->next=NULL;
			head->part_len=len_incr;
			strcpy(head->data, str);
			len=len_incr;
		}
	}
	else if (len_incr+tail->part_len<=307200)
	{                                                            
		char *temp=new char[tail->part_len+len_incr+1];
		if (temp !=NULL)
		{
			strcpy(temp, tail->data);
			strcat(temp, str);
			delete tail->data;
			tail->data=temp;
			tail->part_len+=len_incr;
			len+=len_incr;
		}
		else                                                  
		    len=0;
	}
	else
	{                                                          
		tail->next=new Link;
		if (tail->next!=NULL&&(tail->next->data=new char[len_incr+1])!=NULL)
		{
			tail->next->next=NULL;
			tail->next->part_len=len_incr;
			strcpy(tail->next->data, str);
			tail=tail->next;
			len+=len_incr;
		}
		else                                              
			len=0;
	}
	return *this;
}

int TString_wonderful::operator==(char *str)
{
	if (head==NULL)
		return str==NULL ? true : false;
	else
	{
		int offset=0;
		int i;
		Link *cur=head;
		while (cur)
		{
			for (i=0; i<cur->part_len; i++, offset++)
			{
				if (str[offset]!=cur->data[i])
					return 0;
			}
			cur=cur->next;
		}
		return str[offset]== NULL ? true : false;
	}
}

int TString_wonderful::operator!=(char *str)
{
	return !(*this==str);
}

TString_wonderful::~TString_wonderful()
{
	Link *temp=head;
	while (temp !=NULL)
	{
		if (temp->data !=NULL)
			delete [] temp->data;
		tail=temp->next;
		delete temp;
		temp=tail;
	}
}



/* ----main函数部分---- */
int main()
{
	//该项目的引入与前言
	cout << "本项目的目的：仿照系统自带的string类，定义一系列与之功能完全相同的类。" << endl << endl;
	getch();
	cout << "字符串的基本操作都是基于一维字符数组的，因此其赋值、比较、连接、求长度等方法均要用函"
         << "数去实现，且实现过程中必须注意空间是否足够、最后是不是有'\\0'等情况。" << endl << endl;
	getch();
	cout << "本程序中，自定义了一个类族，逐步添加功能，使其与系统自带string类的功能完全一样，"
		 << "完成类与类、类与字符串常量、类与字符指针、类与字符数组等不同数据类型之间的一系列操作。" << endl << endl;
	getch();
	cout << "在每个功能的实现过程中，都使用了动态内存申请，且做到每次按需申请，不多使用一个字节。" << endl << endl;
	getch();
	cout << "有许多功能看似不难实现，实则特别容易出错，尤其是在处理空字符串的时候。稍微不注意，运行时就会死机。" << endl << endl;
	getch();
	cout << "为了全方位地检查各种隐含错误，每一个功能都设计了测试模块，使用大量实例来进行测试，"
		 << "保证程序运行效果的完美。" << endl << endl;
	//getch();
	//cout << "在经历了无数次出错与死机之后，程序最终达到完美状态。" << endl << endl;
	getch();
	cout << "下面请看各种测试部分：" << endl << endl;

	cout << endl << "任意键继续..." << endl;
	getch();
	cout << endl << endl << endl << endl << endl;

	//每个测试模块都用if的大括号扩起来，使各个部分相对独立，增强程序的清晰性和可读性
	if (1)        
	{
		TString_1 s1;                  //s1为NULL
		TString_1 s2("teststr2");      //s2为"teststr2"
		TString_1 s3="teststr3";       //s3为"teststr3"
		TString_1 s4=NULL;             //s4为NULL
		TString_1 s5="";               //s5为NULL

		cout << "定义对象并初始化测试(NULL及字符串常量初始化)" << endl<<endl;

		cout << "TString_1 s1;                  //s1为NULL" << endl
			 << "TString_1 s2(\"teststr2\");      //s2为\"teststr2\"" << endl
			 << "TString_1 s3=\"teststr3\";       //s3为\"teststr3\"" << endl
		     << "TString_1 s4=NULL;             //s4为NULL" << endl
			 << "TString_1 s5=\"\";               //s5为NULL" << endl << endl;

		cout << "s1应该是<NULL>，  实际输出：" << s1 << endl;
		cout << "s2应该是teststr2，实际输出：" << s2 << endl;
		cout << "s3应该是teststr3，实际输出：" << s3 << endl;
		cout << "s4应该是<NULL>，  实际输出：" << s4 << endl;
		cout << "s5应该是<NULL>，  实际输出：" << s5 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_1 s0   = "teststr1";
		char *str1   = "teststr2";
		char  str2[] = "teststr3";
		char *str3   = NULL;
		char  str4[] = "";
		TString_1 s1=s0, s2=str1, s3=str2, s4=str3, s5=str4;

		cout << "定义对象并初始化测试(TString对象及字符指针、字符数组)" << endl<<endl;

		cout << "TString_1 s0   = \"teststr1\";" << endl
			 << "char *str1   = \"teststr2\";" << endl
			 << "char  str2[] = \"teststr3\";" << endl
			 << "char *str3   = NULL;" << endl
			 << "char  str4[] = "";" << endl
			 << "TString_1 s1=s0, s2=str1, s3=str2, s4=str3, s5=str4;" << endl << endl;

		cout << "s1应该是teststr1，实际输出：" << s1 << endl;
		cout << "s2应该是teststr2，实际输出：" << s2 << endl;
		cout << "s3应该是teststr3，实际输出：" << s3 << endl;
		cout << "s4应该是<NULL>，  实际输出：" << s4 << endl;
		cout << "s5应该是<NULL>，  实际输出：" << s5 << endl;
		
		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_1 s1;
		
		cout << "重载cin测试" << endl << endl;

		cout << "TString_1 s1;" << endl << endl;
		
		cout << "请在键盘上输入Hello" << endl;
		cin >> s1;
		cout << "s1应该是Hello，实际输出：" << s1 << endl<<endl;

		cout << "请在键盘上输入Hello 123" << endl;
		cin >> s1;
		cout << "s1应该是Hello(以空格作为分隔符，只取空格前面的部分)，实际输出：" << s1 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_2 s1("Hello"), s2;
		
		cout << "赋值操作测试" << endl << endl;

		cout << "TString_2 s1(\"Hello\"), s2;" << endl << endl;

		cout << "s1应该是Hello， 实际输出：" << s1 << endl;
		
		s2=s1;
		cout << endl << "s2=s1;" << endl;
		cout << "s2应该是Hello， 实际输出：" << s2 << endl;
		
		s1="Hi";
		cout << endl << "s1=\"Hi\";" << endl;
		cout << "s1应该是Hi，    实际输出：" << s1 << endl;
		
		s2="";
		cout << endl << "s2=\"\";" << endl;
		cout << "s2应该是<NULL>，实际输出：" << s2 << endl;

		s1=NULL;
		cout << endl << "s1=NULL;" << endl;
		cout << "s1应该是<NULL>，实际输出：" << s1 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_2 s0, s1("tong"), s2("ji"), s3;

		cout << "连接(+)测试(两个TString_2类)"<< endl << endl;
		
		cout << "TString_2 s0, s1(\"tong\"), s2(\"ji\"), s3;" << endl;
		s3 = s1+s2;
		cout << endl << "s3 = s1+s2;" << endl; 
		cout << "s3应为tongji，实际输出：" << s3 << endl;
		
		s3 = s2+s1;
		cout << endl << "s3 = s2+s1;" << endl;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1+s0;
		cout << endl << "s3 = s1+s0;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s0+s2;
		cout << endl << "s3 = s0+s2;" << endl;
		cout << "s3应为ji，    实际输出：" << s3 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_2 s1("tong"), s3;

		cout << "连接(+)测试(TString_2类和字符串常量)"<< endl << endl;

		cout << "TString_2 s1(\"tong\"), s3;" << endl;
		s3 = s1+"ji";
		cout << endl << "s3 = s1+\"ji\";" << endl;
		cout << "s3应为tongji，实际输出：" << s3 << endl;
		
		s3 = "ji"+s1;
		cout << endl << "s3 = \"ji\"+s1;" << endl;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1+"";
		cout << endl << "s3 = s1+\"\";" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s1+NULL;
		cout << endl << "s3 = s1+NULL;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = ""+s1;
		cout << endl << "s3 = \"\"+s1;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = NULL+s1;
		cout << endl << "s3 = NULL+s1;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_2 s1("tong"), s3;
		char *str1="ji", *str2="", *str3=NULL;

		cout << "连接(+)测试(TString_2类和字符指针)"<< endl << endl;

		cout << "TString_2 s1(\"tong\"), s3;\nchar *str1=\"ji\", *str2=\"\", *str3=NULL;" << endl;
		s3 = s1+str1;
		cout << endl << "s3 = s1+str1;" << endl;
		cout << "s3应为tongji，实际输出：" << s3 << endl;
		
		s3 = str1+s1;
		cout << endl << "s3 = str1+s1;" << endl;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1+str2;
		cout << endl << "s3 = s1+str2;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = str2+s1;
		cout << endl << "s3 = str2+s1;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = s1+str3;
		cout << endl << "s3 = s1+str3;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = str3+s1;
		cout << endl << "s3 = str3+s1;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_2 s1("tong"), s3;
		char str1[]="ji", str2[]="";

		cout << "连接(+)测试(TString_2类和字符数组)"<< endl << endl;

		cout << "TString_2 s1(\"tong\"), s3;\nchar str1[]=\"ji\", str2[]=\"\";" << endl;
		s3 = s1+str1;
		cout << endl << "s3 = s1+str1;" << endl;
		cout << "s3应为tongji，实际输出：" << s3 << endl;
		
		s3 = str1+s1;
		cout << endl << "s3 = str1+s1;" << endl;
		cout << "s3应为jitong，实际输出：" << s3 << endl;

		s3 = s1+str2;
		cout << endl << "s3 = s1+str2;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		s3 = str2+s1;
		cout << endl << "s3 = str1+s1;" << endl;
		cout << "s3应为tong，  实际输出：" << s3 << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_3 s1="house", s2="horse", s3="house", s4="", s5=NULL;

		cout << "比较运算测试(两个TString_3类)" << endl << endl;

		cout << "TString_3 s1=\"house\", s2=\"horse\", s3=\"house\", s4=\"\", s5=NULL;" << endl << endl;

		cout << "串1=" << s1 << " 串2=" << s2 << " > 结果应为1，实际：" <<(s1 >  s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << " >=结果应为1，实际：" <<(s1 >= s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << " < 结果应为0，实际：" <<(s1 <  s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << " <=结果应为0，实际：" <<(s1 <= s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << " ==结果应为0，实际：" <<(s1 == s2) << endl;
		cout << "串1=" << s1 << " 串2=" << s2 << " !=结果应为1，实际：" <<(s1 != s2) << endl;
		
		cout << "串1=" << s1 << " 串3=" << s3 << " > 结果应为0，实际：" <<(s1 >  s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << " >=结果应为1，实际：" <<(s1 >= s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << " < 结果应为0，实际：" <<(s1 <  s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << " <=结果应为1，实际：" <<(s1 <= s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << " ==结果应为1，实际：" <<(s1 == s3) << endl;
		cout << "串1=" << s1 << " 串3=" << s3 << " !=结果应为0，实际：" <<(s1 != s3) << endl;

		cout << "串1=" << s1 << " 串4=" << s4 << " > 结果应为1，实际：" <<(s1 >  s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " >=结果应为1，实际：" <<(s1 >= s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " < 结果应为0，实际：" <<(s1 <  s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " <=结果应为0，实际：" <<(s1 <= s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " ==结果应为0，实际：" <<(s1 == s4) << endl;
		cout << "串1=" << s1 << " 串4=" << s4 << " !=结果应为1，实际：" <<(s1 != s4) << endl;

		cout << "串1=" << s1 << " 串5=" << s5 << " > 结果应为1，实际：" <<(s1 >  s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " >=结果应为1，实际：" <<(s1 >= s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " < 结果应为0，实际：" <<(s1 <  s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " <=结果应为0，实际：" <<(s1 <= s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " ==结果应为0，实际：" <<(s1 == s5) << endl;
		cout << "串1=" << s1 << " 串5=" << s5 << " !=结果应为1，实际：" <<(s1 != s5) << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_3 s1="house";

		cout << "比较运算测试(TString_3类和字符串常量)" << endl << endl;

		cout << "TString_3 s1=\"house\";" << endl << endl;

		cout << "串1=" << s1 << " 常量=horse" << " > 结果应为1，实际：" << (s1 >  "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << " >=结果应为1，实际：" << (s1 >= "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << " < 结果应为0，实际：" << (s1 <  "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << " <=结果应为0，实际：" << (s1 <= "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << " ==结果应为0，实际：" << (s1 == "horse") << endl;
		cout << "串1=" << s1 << " 常量=horse" << " !=结果应为1，实际：" << (s1 != "horse") << endl;

		cout << "串1=" << s1 << " 常量=house" << " > 结果应为0，实际：" << (s1 >  "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << " >=结果应为1，实际：" << (s1 >= "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << " < 结果应为0，实际：" << (s1 <  "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << " <=结果应为1，实际：" << (s1 <= "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << " ==结果应为1，实际：" << (s1 == "house") << endl;
		cout << "串1=" << s1 << " 常量=house" << " !=结果应为0，实际：" << (s1 != "house") << endl;

		cout << "串1=" << s1 << " 常量=" << " > 结果应为1，实际：" << (s1 >  "") << endl;
		cout << "串1=" << s1 << " 常量=" << " >=结果应为1，实际：" << (s1 >= "") << endl;
		cout << "串1=" << s1 << " 常量=" << " < 结果应为0，实际：" << (s1 <  "") << endl;
		cout << "串1=" << s1 << " 常量=" << " <=结果应为0，实际：" << (s1 <= "") << endl;
		cout << "串1=" << s1 << " 常量=" << " ==结果应为0，实际：" << (s1 == "") << endl;
		cout << "串1=" << s1 << " 常量=" << " !=结果应为1，实际：" << (s1 != "") << endl;

		cout << "串1=" << s1 << " 常量=<NULL>" << " > 结果应为1，实际：" << (s1 >  NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " >=结果应为1，实际：" << (s1 >= NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " < 结果应为0，实际：" << (s1 <  NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " <=结果应为0，实际：" << (s1 <= NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " ==结果应为0，实际：" << (s1 == NULL) << endl;
		cout << "串1=" << s1 << " 常量=<NULL>" << " !=结果应为1，实际：" << (s1 != NULL) << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}
	
	if (1) 
	{
		TString_3 s1="house";
		char *str2="horse", *str3="house", *str4="", *str5=NULL;

		cout << "比较运算测试(TString_3类和字符指针)" << endl << endl;

		cout << "TString_3 s1=\"house\";\nchar *str2=\"horse\", *str3=\"house\", *str4=\"\", *str5=NULL;" << endl << endl;

		cout << "串1=" << s1 << " 串2=" << str2 << " > 结果应为1，实际：" <<(s1 >  str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " >=结果应为1，实际：" <<(s1 >= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " < 结果应为0，实际：" <<(s1 <  str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " <=结果应为0，实际：" <<(s1 <= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " ==结果应为0，实际：" <<(s1 == str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " !=结果应为1，实际：" <<(s1 != str2) << endl;
		
		cout << "串1=" << s1 << " 串3=" << str3 << " > 结果应为0，实际：" <<(s1 >  str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " >=结果应为1，实际：" <<(s1 >= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " < 结果应为0，实际：" <<(s1 <  str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " <=结果应为1，实际：" <<(s1 <= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " ==结果应为1，实际：" <<(s1 == str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " !=结果应为0，实际：" <<(s1 != str3) << endl;

		cout << "串1=" << s1 << " 串4=" << str4 << " > 结果应为1，实际：" <<(s1 >  str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " >=结果应为1，实际：" <<(s1 >= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " < 结果应为0，实际：" <<(s1 <  str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " <=结果应为0，实际：" <<(s1 <= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " ==结果应为0，实际：" <<(s1 == str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " !=结果应为1，实际：" <<(s1 != str4) << endl;

		cout << "串1=" << s1 << " 串5=<NULL>" << " > 结果应为1，实际：" <<(s1 >  str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " >=结果应为1，实际：" <<(s1 >= str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " < 结果应为0，实际：" <<(s1 <  str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " <=结果应为0，实际：" <<(s1 <= str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " ==结果应为0，实际：" <<(s1 == str5) << endl;
		cout << "串1=" << s1 << " 串5=<NULL>" << " !=结果应为1，实际：" <<(s1 != str5) << endl;

		
		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}
	
	if (1)
	{
		TString_3 s1="house";
		char str2[]="horse", str3[]="house", str4[]="";

		cout << "比较运算测试(TString_3类和字符数组)" << endl << endl;

		cout << "TString_3 s1=\"house\";\nchar str2[]=\"horse\", str3[]=\"house\", str4[]=\"\";" << endl << endl;

		
		cout << "串1=" << s1 << " 串2=" << str2 << " > 结果应为1，实际：" <<(s1 >  str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " >=结果应为1，实际：" <<(s1 >= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " < 结果应为0，实际：" <<(s1 <  str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " <=结果应为0，实际：" <<(s1 <= str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " ==结果应为0，实际：" <<(s1 == str2) << endl;
		cout << "串1=" << s1 << " 串2=" << str2 << " !=结果应为1，实际：" <<(s1 != str2) << endl;
		
		cout << "串1=" << s1 << " 串3=" << str3 << " > 结果应为0，实际：" <<(s1 >  str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " >=结果应为1，实际：" <<(s1 >= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " < 结果应为0，实际：" <<(s1 <  str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " <=结果应为1，实际：" <<(s1 <= str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " ==结果应为1，实际：" <<(s1 == str3) << endl;
		cout << "串1=" << s1 << " 串3=" << str3 << " !=结果应为0，实际：" <<(s1 != str3) << endl;

		cout << "串1=" << s1 << " 串4=" << str4 << " > 结果应为1，实际：" <<(s1 >  str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " >=结果应为1，实际：" <<(s1 >= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " < 结果应为0，实际：" <<(s1 <  str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " <=结果应为0，实际：" <<(s1 <= str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " ==结果应为0，实际：" <<(s1 == str4) << endl;
		cout << "串1=" << s1 << " 串4=" << str4 << " !=结果应为1，实际：" <<(s1 != str4) << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}
	
	if (1) 
	{
		TString_3 s1="tong", s2;

		cout << "求长度测试(length()函数)" << endl;

		cout << endl << "TString_3 s1=\"tong\", s2;" << endl;
		
		cout << "s1为tong，  长度应为4，实际：" << s1.length() << endl;
		cout << "s2为<NULL>，长度应为0，实际：" << s2.length() << endl;
		s2 = s1+"ji";
		cout << endl << "s2 = s1+\"ji\";" << endl;
		cout << "s2为tongji，长度应为6，实际：" << s2.length() << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	if (1) 
	{
		TString_3 s1="tong", s2;

		cout << "求长度测试(TStringLen()函数)" << endl;
		
		cout << endl << "TString_3 s1=\"tong\", s2;" << endl;

		cout << "s1为tong，  长度应为4，实际：" << TStringLen(s1) << endl;
		cout << "s2为<NULL>，长度应为0，实际：" << TStringLen(s2) << endl;
		cout << "串为tongji，长度应为6，实际：" << TStringLen(s1+(s2="ji")) << endl;
		cout << "串为tongji，长度应为6，实际：" << TStringLen(s1+"ji") << endl;
		cout << "串为tongji，长度应为6，实际：" << TStringLen(s2=(s1+"ji")) << endl;
		cout << "串为tong，  长度应为4，实际：" << TStringLen(s1+NULL) << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	//以下部分是一个测试CPU速度的程序块，申请100MB字节的空间存放一个超大的字符串
	//执行速度与  "+="运算符重载部分的算法 和 CPU性能  有关
	if (1) 
	{
		TString_3 s1;
		int     total, len, i;
		char    temp[65536];
		long    t_start, t_end;
		char   *crc_str;

		cout << "以下部分是一个内存性能的测试(大约需要3-6分钟)" << endl << endl;
		getch();
		cout << "以动态内存申请和释放的方式，为TString_3类一个对象的字符指针申请内存空间，以内存耗尽或申请满100MB字节为结束条件" << endl << endl;
		getch();
		cout << "执行速度与  \"+=\",\"==\",\"!=\"等运算符重载部分的算法 和 CPU的性能  有关" << endl << endl;
		getch();
		cout << "一次申请 32KB~64KB 字节不等，内存耗尽或申请满100MB字节则结束" << endl << endl;
		getch();
		cout << "运行期间请不要关闭窗口，因为在该部分结束后仍有别的功能。" << endl << endl;
		cout << "按任意键开始" << endl;
		getch();

		crc_str = new char[100*1024*1024+65536]; //申请（100MB+64KB）空间
		*crc_str = 0; //置为空串

		t_start = GetTickCount(); //取当前系统时间，单位毫秒
		srand(time(0));
		total = 0;
		while(1)
		{
		    len = 32768 + rand()%32768;

			cout << "s1已有长度：" << (double)total/(1024*1024) << " MB字节，本次增加 " << len << " 字节" << endl;
			for(i=0; i<len; i++)
				temp[i] = ' '+rand()%95;	//数组用随机字符填充
			temp[len] = 0;
			total += len;
			s1 += temp;
			strcat(crc_str, temp);
			if (s1.length()==0 || s1.length() > 1024*1024*100)	//满100MB或内存耗尽则结束
				break;
		}
		t_end = GetTickCount();   //取当前系统时间

	    cout << "time=" << (t_end - t_start)/1000.0 << endl; 
		if (s1.length()==0)
		    cout << "内存分配到达 " << total/(1024*1024) << " MB字节后，内存耗尽" << endl;
		else
		    cout << "内存分配到达满100MB，测试结束" << endl;

		if (s1!=crc_str)          //调试程序时用到
			cout << "s1累加验证出错，需检查程序的实现部分" << endl;
		else
			cout << "    本次测试耗时 " << (t_end - t_start)/1000.0 << "秒" << endl;

		delete crc_str;

		cout << "    以下部分更加精彩  " << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}
	

	if (1) 
	{
		string s1;
		int     total, len, i;
		char    temp[65536];
		long    t_start, t_end;
		char   *crc_str;

		cout << "以下部分与上部分的执行步骤相同，但是使用的是系统定义的string类对象及其各种运算符" << endl << endl;
		getch();
		cout << "在同一台电脑上，这两部分的执行时间不同，可以马上看出系统string类与我们定义的仿string类在算法实现方面的优劣" << endl << endl;
		getch();
		cout << "一次申请 32KB~64KB 字节不等，内存耗尽或申请满100MB字节则结束，这一次的时间大约在60秒以内" << endl << endl;
		getch();
		cout << "运行期间请不要关闭窗口，在该部分结束后仍有别的功能。" << endl << endl;
		cout << "按任意键开始" << endl;
		getch();

		crc_str = new char[100*1024*1024+65536]; //申请（100MB+64KB）空间
		*crc_str = 0; //置为空串

		t_start = GetTickCount(); //取当前系统时间，单位毫秒
		srand(time(0));
		total = 0;
		while(1)
		{
		    len = 32768 + rand()%32768;

			cout << "s1已有长度：" << (double)total/(1024*1024) << " MB字节，本次增加 " << len << " 字节" << endl;
			for(i=0; i<len; i++)
				temp[i] = ' '+rand()%95;	//数组用随机字符填充
			temp[len] = 0;
			total += len;
			s1 += temp;
			strcat(crc_str, temp);
			if (s1.length()==0 || s1.length() > 1024*1024*100)	//满100MB或内存耗尽则结束
				break;
		}
		t_end = GetTickCount();   //取当前系统时间

	    cout << "time=" << (t_end - t_start)/1000.0 << endl; 
		if (s1.length()==0)
		    cout << "内存分配到达 " << total/(1024*1024) << " MB字节后，内存耗尽" << endl;
		else
		    cout << "内存分配到达满100MB，测试结束" << endl;

		if (s1!=crc_str)          //调试程序时用到
			cout << "s1累加验证出错，需检查程序的实现部分" << endl;
		else
			cout << "    本次测试耗时 " << (t_end - t_start)/1000.0 << "秒" << endl;

		delete crc_str;

		cout << "    以下部分更加精彩(^_^)" << endl;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}


	if (1) 
	{
		const int MAX_BYTES = 100*1024*1024;
		TString_wonderful s1;

		int     total, len, i;
		char    temp[65536];
		long    t_start, t_end;
		char   *crc_str;

		cout << "该部分与上部分的执行步骤相同，但是这次使用的是上面定义的改进后的TString_wonderful类对象" << endl << endl;
		getch();
		cout << "对\"+=\",\"==\",\"!=\"等运算符重载的实现部分做了很大改进，使其执行效率与系统自带的string类非常接近" << endl << endl;
		getch();
		cout << "主要的改进是把字符串的存取、拼接和比较用链表来实现，避免了反复开辟和释放超大空间带来的时间和空间开销" << endl << endl;
		getch();
		cout << "在同一台电脑上，对比这部分和上部分的执行时间，可以看出系统string类与我们定义的TString_wonderful类在算法实现方面的优劣，可以看出两者已经十分接近"
			 << "(在某些运行环境下，这部分比上一部分还要快)" << endl << endl;
		getch();
		cout << "一次申请 32KB~64KB 字节不等，内存耗尽或申请满100MB字节则结束，这一次的时间大概在60秒以内" << endl << endl;
		getch();
		cout << "运行期间请不要关闭窗口。" << endl << endl;
		cout << "按任意键开始" << endl;
		getch();

		crc_str = new char[MAX_BYTES+65536]; //申请（100MB+64KB）空间
		*crc_str = 0; //置为空串

		t_start = GetTickCount(); //取当前系统时间，单位毫秒
		srand(time(0));
		total = 0;
		while(1) 
		{
			len = 32768 + rand()%32768;

			cout << "s1已有长度：" << s1.length()/(1024.0*1024) << " MB字节，本次增加 " << len << " 字节" << endl;
			for(i=0; i<len; i++)
				temp[i] = ' '+rand()%95;	//数组用随机字符填充
			temp[len] = 0;
			total += len;
			s1 += temp;
			strcat(crc_str, temp);
			if (s1.length()==0 || s1.length() > MAX_BYTES)	//满100MB或内存耗尽则结束
				break;
		}
		t_end = GetTickCount();   //取当前系统时间

		cout << "time=" << (t_end - t_start)/1000.0 << endl; 
		if (s1.length()==0)
			cout << "内存分配到达 " << total/(1024.0*1024) << " MB字节后，内存耗尽" << endl;
		else
			cout << "内存分配到达满100MB，测试结束" << endl;

		if (s1!=crc_str)          //调试程序时用到
			cout << "s1累加验证出错，需检查程序的实现部分" << endl;
		else
			cout << "    本次测试耗时 " << (t_end - t_start)/1000.0 << "秒" << endl;

		delete crc_str;

		cout << endl << "任意键继续..." << endl;
		getch();
		cout << endl << endl << endl << endl << endl;
	}

	cout << "可以看出，本程序定义的TString_wonderful类的执行效率非常高，已可与系统自带的string类媲美。" << endl << endl;
	cout << "至此，程序已经全部结束" << endl << endl << endl << endl << endl;

	system("pause");

	return 0;
}
