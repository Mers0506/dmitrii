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
	//обьявление переменных
	char let;
	string slovo;
	string pre;
	string pro, mid;
	int n, d, a, m;
	//открытие входного потока , и проверка на существование файла
	ifstream in("in.txt");
	if (!in.is_open())
	{
		cout << " in.txt" << endl;
		return -4;
	}
	//открытие выходного потока и проверка  на существование файла
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
	//начало цикла
	while (!in.eof())
	{
		// функция берет букву и и счетчики
		in.get(let);
		a = a + 1;
		n = n + 1;
		// накопление в текущий буфер
		pro = pro + let;
		mid = mid + let;
		// проверка на окончания слова или предложения 
		if (let == ' ' || let == '?' || let == '!' || let == '.' || let == ',')
		{
			//проверка на самое длинное слово
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

			// проверка на самое длинное предложениия 
			if (let == '?' || let == '!' || let == '.' && m < a)
			{
				pre = mid;
				m = a;
				mid.clear();
				a = 0;
			}
		}

	}
	// вывод самого длинного предложения и слова 
	out << "самое длинное слово." << endl << slovo << endl;
	out << "самое длинное предложение." << endl << pre << endl;

	return 0;
}
