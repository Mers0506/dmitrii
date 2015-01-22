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
	int n, d, a, m;
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
	d = 0;
	m = 0;

	while (!in.eof())
	{
		in.get(let);
		a = a + 1;
		n = n + 1;
		pro = pro + let;
		mid = mid + let;
		if (let == ' ' || let == '?' || let == '!' || let == '.' || let == ',')
		{
			if (d<n)
			{

				slovo = pro;
				d = n;
				pro.clear();
				n = 0;
			}
			else if (d == n)
			{

				slovo = slovo + pro;
				n = 0;
				pro.clear();
			}
			else {
				n = 0;
				pro.clear();
			}


			if (let == '?' || let == '!' || let == '.' && m < a)
			{
				pre = mid;
				m = a;
				mid.clear();
				a = 0;
			}
		}

	}

	out << "самое длинное слово." << endl << slovo << endl;
	out << "самое длинное предложение." << endl << pre << endl;

	return 0;
}
