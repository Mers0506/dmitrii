// ConsoleApplication6.cpp: ���������� ����� ����� ��� ����������� ����������.
//



#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(void)
{
	setlocale(LC_ALL, "Russian");
	//���������� ����������
	char let;
	string slovo;
	string pre, r;
	string pro, mid;
	int n, d, a, m;
	//�������� �������� ������ , � �������� �� ������������� �����
	ifstream in("in.txt");
	if (!in.is_open())
	{
		cout << " in.txt" << endl;
		return -4;
	}
	//�������� ��������� ������ � ��������  �� ������������� �����
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
	r = ',';
	//������ �����
	while (!in.eof())
	{
		// ������� ����� ����� � � ��������
		in.get(let);
		a = a + 1;
		n = n + 1;
		// ���������� � ������� �����
		
		mid = mid + let;
		// �������� �� ��������� ����� ��� ����������� 
		if (let == ' ' || let == '?' || let == '!' || let == '.' || let == ',')
		{
			pro = pro + r;
			//�������� �� ����� ������� �����
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

			// �������� �� ����� ������� ������������ 
			if (let == '?' || let == '!' || let == '.')
			{
				if (m < a)
				{
					pre = mid;
					m = a;
					mid.clear();
					a = 0;
				}
				else {
					mid.clear();
					a = 0;
				}
			}

		}
		pro = pro + let;

	}
	// ����� ������ �������� ����������� � ����� 
	out << "����� ������� �����." << endl << slovo << endl;
	out << "����� ������� �����������." << endl << pre << endl;

	return 0;
}
