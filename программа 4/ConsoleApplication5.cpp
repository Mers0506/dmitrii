// ConsoleApplication5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
using namespace std;
int main(void)
{
	setlocale(LC_ALL, "rus");
	int n, m, max;
	ifstream in("in.txt");
	if (!in.is_open())
	{
		cout << "Not open in.txt" << endl;
		return -4;
	}
	in >> n >> m;
	int** A = new int*[m + 2];
	for (int i = 0; i < n + 2; i++)
	{
		A[i] = new int[m + 2];
	}
	for (int i = 0; i < m + 2; i++)
	{
		for (int j = 0; j < n + 2; j++)
		{
			if (i != 0 && i != m + 1 && j != 0 && j != n + 1)
			{
				in >> A[i][j];
			}
			else
			{
				A[i][j] = 0;
			}
		}
	}

	ofstream out("out.txt");
	if (!out.is_open())
	{
		cout << "Not create out.txt" << endl;
		return -4;
	}
	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			out << A[i - 1][j - 1] + A[i - 1][j] + A[i - 1][j + 1] + A[i][j - 1] + A[i][j] + A[i][j + 1] + A[i + 1][j - 1] + A[i + 1][j] + A[i + 1][j + 1] << ' ';
		}
		out << endl;
	}
	system("pause");
	return 0;
}
