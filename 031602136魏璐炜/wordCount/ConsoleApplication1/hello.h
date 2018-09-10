#pragma once
#include "pch.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include <vector>
#include<map>
using namespace std;
extern char b[100000];
extern int j;
extern int count_;
extern vector<string> str;
extern vector<string> str_shorted;
extern map<string, int> strmap;
extern map<string, int>::iterator q;
extern ofstream d;
extern string a;
extern int w;
extern int max;
extern bool flag1;

void agefile(string filename)
{
	char c;
	ifstream s(filename);
	if (!s)
	{
		cout << "error" << endl;
		flag1 = false;
	}
	while (s.get(c))
	{
		b[j++] = c;
	}
//	cout << "characters:" << j << endl;
	d << "characters:" << j << endl;
}
void count_all(string buf, bool notempty = false)
{

	int i;
	for (i = 0; i < j; i++)
	{
		if (b[i] != ' '&&b[i] != '\n')
		{
			buf.insert(buf.end(), b[i]);
			//		buf += b[i];
		}
		else
		{
			if (b[i] == '\n')
			{
				notempty = false;
				for (int j = 0; j < buf.size(); j++)
				{
					if (buf[j] > 32)
						notempty = true;
				}
				if (notempty == true)
					count_++;
			}
			if (buf != "")
			{
				str.push_back(buf);
				buf.clear();
			}
		}
	}
	if (buf != "")
	{
		for (int k3 = 0; k3 < buf.size(); k3++)
		{
			if (buf[k3] > 32)
				notempty = true;
		}
		if (notempty == true)
			count_++;
		str.push_back(buf);
		buf.clear();
	}
	for (i = 0; i < str.size(); i++)
	{

		bool flag = false;
		for (int k = 0; k < str[i].size(); k++)
		{
			if (str[i][k] > 32)
				flag = true;
		}
		if (str[i][0] >= 48 && str[i][0] <= 57)
		{
			flag = false;
		}
		if (str[i].size() > 4 && flag == true)
		{
			str_shorted.push_back(str[i]);
		}
	}
	for (i = 0; i < str_shorted.size(); i++)
	{
		if (strmap.find(str_shorted[i]) == strmap.end())
		{
			strmap[str_shorted[i]] = 1;
		}
		else
		{
			strmap[str_shorted[i]]++;
		}
	}
//	cout << "lines:" << count_ << endl;
//	cout<< "words:" << str_shorted.size() << endl;
	d << "lines:" << count_ << endl;
	d << "words:" << str_shorted.size() << endl;
}

void addword(bool flag = true,int max=-999)
{
	bool flag2 = false;
	q = strmap.begin();
	for (int s1 = 0; s1 < 10; s1++)
	{
		flag2 = false;
		if (flag == false)
		{
			break;
		}
		flag = true;
		max = -999;
		while (q != strmap.end())
		{
			if (q->second > max)
			{
				flag2 = true;
				max = q->second;
				a = q->first;
			}
			q++;
		}
		if (flag2 == true)
		{
//			cout << "<" << a << ">:" << max << endl;
			d << "<" << a << ">:" << max << endl;
		}
		q = strmap.begin();
		strmap[a] = -10;
		for (int j1 = 0; j1 < str_shorted.size(); j1++)
		{
			if (strmap[str_shorted[j1]] == -10)
			{
				w++;
			}
		}
		if (w == str_shorted.size())
		{
			flag = false;
		}
		w = 0;
	}
}

