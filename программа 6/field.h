#ifndef _FIELD_H
#define _FIELD_H

//������ ����
enum Cell
{
	CROSS,
	ZERO,
	EMPTY
};
class Field
{
	// ������ 3*3 ��� �������� ����
	Cell cells[3][3];
	bool isCrossTurn;
	
	// ����������
	Cell winner;

    void checkWinner();
	
public:
	// ������� ����
	Field(bool isCrossFirst);
	// ������� ���� �� ����������
	void clear(bool isCrossFirst);

	// column - ����� ������� ����, �� 1 �� 3
	// line - ����� ������ ����, �� 1 �� 3
    bool makeTurn(int line, int column);
	bool removeTurn(int line, int column);
	bool isWon(bool cross) const;
	bool isOver() const;
	int statWon();
	int  bestTurn(); //������������� ��� ����������
	void initEvr();
	int x, y;
	int turn[2];
	int masEvr[3][3];
	// ������ � �������
	// i ����� ������� �� 1 �� 3
	// j ����� ������� �� 1 (�������) �� 3 (������)
	Cell getCell(int i, int j) const;
	bool isCrossTurnNow() const;
	// ���������� � �������
	void print() const;
	void printText(int pos1, int pos2);
	// ���������� ���������� � �������
	void printResult() const;
	// ���������� ���� � ����
    void saveGame() ;
	// �������� ����������� ���� �� �����
	void openGame() ;
	
};

#endif