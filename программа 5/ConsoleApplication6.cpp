// ConsoleApplication6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(void)
{
	setlocale(LC_ALL, "Russian");
	char let;
	string slovo;
	string pre;
	string pro, mid;
	int n, max, d, a, maxp;
	ifstream in("in.txt");
	if (!in.is_open())
	{
		cout << " in.txt" << endl;
		return -4;
	}
	in.get(let);
	ofstream out("out.txt");
	if (!out.is_open())
	{
		cout << "out.txt" << endl;
		return -4;
	}
	a = 0;
	n = 0;
	while (!in.eof())
	{
		in.get(let);
		a = a + 1;
		n = n + 1;
		if (let == ' ' || let == '?' || let == '!' || let == '.')
		{ if (d<n)
		{
			slovo = pro;
			d = n;
				pro.clear();
				n = 0;
		}
			if (let == '?' || let == '!' || let == '.' && maxp < a)
			{
				pre =  mid;
				maxp = a;
				mid.clear();
				a = 0;
			}
		}
		else
			pro = pro + let;
		mid = mid = let;
	}
	out << endl << slovo << endl;
	out << endl << pre << endl;
	system("pause");
	return 0;
}