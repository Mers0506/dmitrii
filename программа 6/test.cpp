/*Реализовать класс КРЕСТИКИ-НОЛИКИ НА ДОСКЕ 3х3. 
Требуемые методы: конструктор, деструктор, установка крестика/нолика в заданную клетку, 
удаление крестика/нолика из заданной клетки, определение победителя в данной позиции
 (для выигрыша необходимо составить горизонтальную, вертикальную или диагональную линию 
 из 3 одинаковых знаков), определение лучшего хода в данной позиции для заданного игрока.
Написать главную функцию, тестирующую данный класс путём создания его объектов и проведения 
над ними различных операций.
*/


#include "field.h"
#include <iostream>
#include <locale.h>
#include <fstream>

using namespace std;

// -1 ничья
// -2 победа крестик
// -3 победа нолик
// -4 если файл сохранен
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
cout<<"Провал теста: ход невозможен"<<endl;
cout<<"Партия "<<game<<" ход "<<turn<<endl;
return false;
}
i++;
turn++;
}
cout<<"Тестовая партия "<<game<<" сыграна"<<endl;
field.printResult();
switch (turnsi[i])
{
case -1:
if (field.isOver())
{
cout<<"Провал теста: ожидали незаконченную партию"<<endl;
field.print();
return false;
}
break;
case -2:
if (!field.isWon(true))
{
cout<<"Провал теста: ожидали победу крестиков"<<endl;
field.print();
return false;
}
break;
case -3:
if (!field.isWon(false))
{
cout<<"Провал теста: ожидали победу ноликов"<<endl;
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
cout<<"Всего сыграно "<<game-1<<" тестовых партий"<<endl;
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

		cout << "Ходит " <<
			(field.isCrossTurnNow() ? "Крестик. " : "Нолик. ") << "1 - выполнить ход, 2 - получить подсказку" << endl;
		cin >> type;
		if (type == 2){
			field.bestTurn2();
			
		
		}
		if (type == 1){

			cout << "Пожалуйста, введите ход 1-3 (номер колонки, затем номер строки)" << endl;
			
			cin >> line >> column;
		
		bool fg = field.makeTurn(line, column);
		
		if (fg != false && field.statWon() == 0){
		field.print();
		cout << "Отменить ход? 1 - отменить, 2 - продолжить игру" << endl;
		cin >> flag;
		
			if (flag == 1){field.removeTurn(line, column);}
			}
		
		}
	}
	field.printResult();
	return 0;
}