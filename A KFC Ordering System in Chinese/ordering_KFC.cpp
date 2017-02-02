#include <iostream>
#include <iomanip> //格式输出
#include <cmath> //fabs
#include <windows.h> //取系统时间
#include <ctime>
#include <conio.h>
//#include <string.h>
#include <string>
//#include <cstring>
#include <process.h>
#include <cstdlib>
#include <fstream> //文件操作需要的头文件
using namespace std;

struct KFC 
{
	char no;
	char *name;
	float price;
};


struct SPECIAL 
{
	char *item;
	char *prompt;
	float price;
};


int main()
{
	srand(time(0));
	int comp(int *, int *, int);

	struct KFC n_menu[] = 
	{
		{'A', "香辣鸡腿堡", 15.0},
		{'B', "劲脆鸡腿堡", 15.0},
		{'C', "新奥尔良烤鸡腿堡", 15.5},
		{'D', "老北京鸡肉卷", 14.0},
		{'E', "川香嫩牛卷", 15.0},
		{'F', "吮指原味鸡", 9.0},
		{'G', "新奥尔良烤翅", 9.5},
		{'H', "香辣鸡翅", 8.5},
		{'I', "劲脆鸡米花", 10.0},
		{'J', "上校鸡块", 8.0},
		{'K', "薯条(小)", 7.0},
		{'L', "薯条(中)", 8.5},
		{'M', "薯条(大)", 10.0},
		{'N', "芙蓉鲜蔬汤", 6.0},
		{'O', "香甜粟米棒", 6.5},
		{'P', "土豆泥", 4.5},
		{'Q', "脆皮甜筒", 3.0},
		{'R', "百事可乐(小)", 6.0},
		{'S', "百事可乐(中)", 7.5},
		{'T', "百事可乐(大)", 9.0},
		{'U', "九珍", 9.5},
		{'V', "雪顶爱尔兰咖啡", 10.0},
		{'\0', NULL, 0}
	};

	struct SPECIAL s_menu[]=
	{
		{"AKR", "香辣汉堡超值套餐", 25},
		{"FHFFHFGTFGOTT", "超值全家桶", 84},
		{"QQ", "脆皮甜筒第2件半价", 4.5},
		{"LLL", "中薯买2送1", 17},
		{NULL, NULL, 0}
	};

	int i, j;
	for (i = 0; i <= 10; i++)
	{
		cout << ' ' << (n_menu + 2 * i)->no << ' ' << (n_menu + 2 * i)->name;
		for (j = 1; j <= 20 - strlen((n_menu + 2 * i)->name); j++)
			cout << ' ';
		cout << (n_menu + 2 * i)->price;
		if (int((n_menu + 2 * i)->price) - (n_menu + 2 * i)->price == 0 && (n_menu + 2 * i)->price < 10)
			cout << "      ";
		else if (int((n_menu + 2 * i)->price) - (n_menu + 2 * i)->price == 0 && (n_menu + 2 * i)->price >= 10)
			cout << "     ";
		else if (int((n_menu + 2 * i)->price) - (n_menu + 2 * i)->price != 0 && (n_menu + 2 * i)->price < 10)
			cout << "    ";
		else
			cout << "   ";
		cout << "|   ";
		cout << (n_menu + 2 * i + 1)->no << ' ' << (n_menu + 2 * i + 1)->name;
		for (j = 1; j <= 20 - strlen((n_menu + 2 * i + 1)->name); j++)
			cout << ' ';
		cout << (n_menu + 2 * i + 1)->price << endl;
	}


	cout << endl << "【优惠信息】：" << endl;
	cout << "香辣汉堡超值套餐=香辣鸡腿堡+薯条(小)+百事可乐(小)=25" << endl;
	cout << "超值全家桶=吮指原味鸡*5+新奥尔良烤翅*2+香辣鸡翅*2+香甜玉米棒+百事可乐(大)*3=84" << endl;
	cout << "脆皮甜筒第二件半价=脆皮甜筒*2=4.5" << endl;
	cout << "中薯买2送1=薯条(中)*3=17" << endl;
	cout << endl << "【输入规则说明】：" << endl;
	cout << "AKR=香辣鸡腿堡+薯条(小)+百事可乐(小) / ahaah=香辣鸡腿堡*3+香辣鸡翅*2" << endl;
	cout << "字母不分大小写，不限顺序，单独输入0则退出程序" << endl << endl;


	string str;
	int k, n, len, special, s;
	float total;
	i = 0;
	while ((n_menu + i)->no != 0)
		i++;
	n = i;
	int *a = new int[n];
	int *b = new int[n];

	while (1)
	{
		for (i = 0; i <= n - 1; i++)
			a[i] = 0;
		total = 0;
		cout << "请点单：";
		cin >> str;
		len = str.size();
		if (str == "0")
			break;

		for (i = 0; i <= len - 1; i++)
		{
			if (str[i] >= 'a' && str[i] <= 'v')
				str[i]-=32;
			if (str[i] < 'A' || str[i] > 'V')
			{
				cout << "输入错误，按任意键继续." << endl;
				break;
			}
			j = 0;
			while ((n_menu + j)->no != '\0')
			{
				if ((n_menu + j)->no == str[i])
				{
					a[j]++;
					break;
				}
				j++;
			}
		}

		if (i != len)
		{
			getchar();
			getch();
			cout << endl;
			continue;
		}
		cout << "您的点单=";
		i = j = 0;

		while ((n_menu + j)->no != '\0')
		{
			if (i == 0)
			{
				if (a[j] == 1)
				{
					cout<<(n_menu + j)->name;
					i++;
				}
				else if (a[j] >= 2)
				{
					cout<<(n_menu + j)->name << '*' << a[j];
					i++;
				}
			}
			else
			{
				if (a[j] == 1)
				{
					cout<< '+' << (n_menu + j)->name;
					i++;
				}
				else if (a[j] >= 2)
				{
					cout << '+' << (n_menu + j)->name << '*' << a[j];
					i++;
				}
			}
			j++;
		}

		s = k = i = j = 0;
		while ((s_menu+k)->item != NULL)
		{
			special = 0;
			for (i = 0; i <= n-1; i++)
				b[i] = 0;
			for (i = 0; i <= strlen((s_menu + k)->item) - 1; i++)
			{
				j = 0;
				while ((n_menu+j)->no != '\0')
				{
					if ((n_menu+j)->no == *((s_menu+k)->item + i))
					{
						b[j]++;
						break;
					}
					j++;
				}
			}
			while (comp(a, b, n) != 0)
			{
				for (i = 0; i <= n - 1; i++)
					a[i] -= b[i];
				special++;
			}
			if (special >= 1)
			{
				if (s == 0)
					cout << "   (包含 ";
				else
					cout << ',';
				s++;
				cout << (s_menu + k)->prompt << " *" << special;
				total += (s_menu + k)->price * special;
			}
			k++;
		}

		if (s != 0)
			cout << ')';

		for (i = 0; i <= n - 1; i++)
			total += a[i] * (n_menu + i)->price;

		cout << endl << "共计：" << total << "元" << endl << "点单完成，按任意键继续" << endl;
		getch();
		cout << endl;
	}
	

	delete []b;
	delete []a;
	system("pause");
	return 0;
}


int comp(int *a,int *b,int n)
{
	int i;
	for (i = 0; i <= n - 1; i++)
		if (a[i] < b[i])
			break;
	if (i != n)
		return 0;
	else
		return 1;
}
