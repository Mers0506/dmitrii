#ifndef _FIELD_H
#define _FIELD_H

//Ячейка поля
enum Cell
{
	CROSS,
	ZERO,
	EMPTY
};
class Field
{
	// Массив 3*3 для хранения поля
	Cell cells[3][3];
	bool isCrossTurn;
	
	// Победитель
	Cell winner;

    void checkWinner();
	
public:
	// Очистка поля
	Field(bool isCrossFirst);
	// Очистка поля по требованию
	void clear(bool isCrossFirst);

	// column - номер колонки хода, от 1 до 3
	// line - номер строки хода, от 1 до 3
    bool makeTurn(int line, int column);
	bool removeTurn(int line, int column);
	bool isWon(bool cross) const;
	bool isOver() const;
	int statWon();
	int  bestTurn(); //Устанавливает ход компьютера
	void initEvr();
	int x, y;
	int turn[2];
	int masEvr[3][3];
	// Доступ к ячейкам
	// i номер колонки от 1 до 3
	// j номер строчки от 1 (верхняя) до 3 (нижняя)
	Cell getCell(int i, int j) const;
	bool isCrossTurnNow() const;
	// Распечатка в консоль
	void print() const;
	void printText(int pos1, int pos2);
	// Распечатка результата в консоль
	void printResult() const;
	// Сохранение игры в файл
    void saveGame() ;
	// Открытие сохраненной игры из файла
	void openGame() ;
	
};

#endif