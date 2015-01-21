/*����������� ����� ��������-������ �� ����� 3�3. 
��������� ������: �����������, ����������, ��������� ��������/������ � �������� ������, 
�������� ��������/������ �� �������� ������, ����������� ���������� � ������ �������
 (��� �������� ���������� ��������� ��������������, ������������ ��� ������������ ����� 
 �� 3 ���������� ������), ����������� ������� ���� � ������ ������� ��� ��������� ������.
�������� ������� �������, ����������� ������ ����� ���� �������� ��� �������� � ���������� 
��� ���� ��������� ��������.
*/


#include "field.h"
#include <iostream>
#include <locale.h>
#include <fstream>

using namespace std;

// -1 �����
// -2 ������ �������
// -3 ������ �����
// -4 ���� ���� ��������
int turnsi[] =
{
    1,1,2,3,1,3,3,2,-1,2,1,1,1,3,-2,1,2,1,1,3,3,-3,
0
};
int turnsj[] =
{
	1,2,2,3,3,1,2,1,-1,2,1,3,2,1,-2,1,2,3,2,3,2,-3,
	0
};
int type;
int flag = 0;

bool test(void)
{
int i=0;
int game=1;
int turn=1;

Field field(true);
while ((turnsi[i] != 0)&&(turnsj[i]!=0))
{
while ((turnsi[i] > 0)&&(turnsj[i]>0))
{
if (!field.makeTurn(turnsi[i], turnsj[i]))
{
cout<<"������ �����: ��� ����������"<<endl;
cout<<"������ "<<game<<" ��� "<<turn<<endl;
return false;
}
i++;
turn++;
}
cout<<"�������� ������ "<<game<<" �������"<<endl;
field.printResult();
switch (turnsi[i])
{
case -1:
if (field.isOver())
{
cout<<"������ �����: ������� ������������� ������"<<endl;
field.print();
return false;
}
break;
case -2:
if (!field.isWon(true))
{
cout<<"������ �����: ������� ������ ���������"<<endl;
field.print();
return false;
}
break;
case -3:
if (!field.isWon(false))
{
cout<<"������ �����: ������� ������ �������"<<endl;
field.print();
return false;
}
break;
}
i++;
game++;
turn = 1;
field.clear(true);
}
cout<<"����� ������� "<<game-1<<" �������� ������"<<endl;
return true;
}


int main(void)
{
	setlocale(LC_ALL, "Russian");
	if (!test())
	 return -1;
	Field testfield(true);
	int stesti[] = { 1, 2, 3,	0 };
	int stestj[] = { 1, 2, 3, 0};

	int i = 0;
	while ((stesti[i] != 0) || (stestj[i] != 0))
	{
		testfield.makeTurn(stesti[i],stestj[i]);
		testfield.saveGame();
		i++;
	}
	

	


	Field field(true);
	int flag = 0;
	int line, column;
//	int turn[2];
	while (!field.isOver())
	{
		field.print();

		cout << "����� " <<
			(field.isCrossTurnNow() ? "�������. " : "�����. ") << "1 - ��������� ���, 2 - �������� ���������" << endl;
		cin >> type;
		if (type == 2){
			field.bestTurn2();
			
		
		}
		if (type == 1){

			cout << "����������, ������� ��� 1-3 (����� �������, ����� ����� ������)" << endl;
			
			cin >> line >> column;
		
		bool fg = field.makeTurn(line, column);
		
		if (fg != false && field.statWon() == 0){
		field.print();
		cout << "�������� ���? 1 - ��������, 2 - ���������� ����" << endl;
		cin >> flag;
		
			if (flag == 1){field.removeTurn(line, column);}
			}
		
		}
	}
	field.printResult();
	return 0;
}