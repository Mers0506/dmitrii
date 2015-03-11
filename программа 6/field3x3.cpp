#include "field.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

Field::Field(bool isCrossFirst)
{
  clear(isCrossFirst);
}

void Field::clear(bool isCrossFirst)
{
  isCrossTurn = isCrossFirst;
  winner = EMPTY;
  for (int i = 0; i<3; i++)
    for (int j = 0; j<3; j++)
      cells[i][j] = EMPTY;
}

//	int iT, jT; Переименовал и убрал в класс
bool Field::makeTurn(int column, int line)
{
  if (winner != EMPTY)
    return false;
  // корректность ввода
  if (column < 1 || column > 3)
    return false;
  if (line < 1 || line > 3)
    return false;
  iT = column - 1;
  jT = line - 1;

  if (cells[iT][jT] == EMPTY)
  {
    cells[iT][jT] = isCrossTurn ? CROSS : ZERO;
    checkWinner();

    isCrossTurn = !isCrossTurn;

    return true;
  }
  return false;
}

bool Field::removeTurn(int line, int column){
  cells[line-1][column-1] = EMPTY;
  isCrossTurn = !isCrossTurn;
  return true;
}

void Field::checkWinner() // Кто победил?

{
  winner = EMPTY;
  int i, j, sum1, sum;
//  int k1 = 0, k2 = 0, k3 = 0, k4 = 0;
//  int	max1 = 0, max2 = 0, max3 = 0, max4 = 0;

  // Проверка по строкам
  for (i = 0; i < 3; i++)
  {
    sum = 0;
    for (j = 0; j < 3; j++)
    {
      if (cells[i][j] == cells[iT][jT])
      {
        sum++;
      }
    }
    if (sum == 3)
    {
      winner = cells[iT][jT];
      return;
    }
  }
  // Проверка по столбцам
  for (j = 0; j < 3; j++)
  {
    sum = 0;
    for (i = 0; i < 3; i++)
    {
      if (cells[i][j] == cells[iT][jT])
      {
        sum++;
      }
    }
    if (sum == 3)
    {
      winner = cells[iT][jT];
      return;
    }
  }

  // Проверка по диагоналям
  sum = 0;
  sum1= 0;
  for (i = 0; i < 3; i++)
  {
    if (cells[i][i] == cells[iT][jT])
    {
      sum++;
    }
    if (cells[2 - i][i] == cells[iT][jT])
    {
      sum1++;
    }

  }
  if ((sum == 3) || (sum1 == 3))
  {
    winner = cells[iT][jT];
    return;
  }

/*  
  for (int q = 0; q < 3; q++)
  {
    if (cells[q][jT] == cells[iT][jT])
    {
      while ((cells[q][jT] == cells[q + k1][jT]) && (q + k1 < 3))
      {
        k1++;
        if (k1 > 2)
        {
          winner = cells[iT][jT];
          break;
        }
        if ((k1<3) && (k1>max1))
        {
          max1 = k1;
          k1 = 0;
        }
      }
    }
    if (cells[iT][q] == cells[iT][jT])
    {
      while ((cells[iT][q] == cells[iT][q + k2]) && (q + k2 < 3))
      {
        k2++;
        if (k2 > 2)
        {
          winner = cells[iT][jT];
          break;
        }
        if ((k2<3) && (k2>max2))
        {
          max2 = k2;
          k2 = 0;
        }
      }
    }
    if (cells[q][jT + iT - q] == cells[iT][jT])
    {
      while ((cells[q][jT + iT - q] == cells[q + k3][jT + iT - q - k3]) && (q + k3 < 3))
      {
        k3++;
        if (k3 > 2)
        {
          winner = cells[iT][jT];
          break;
        }
        if ((k3<3) && (k3>max3))
        {
          max3 = k3;
          k3 = 0;
        }
      }
    }

    if (cells[q][q] == cells[iT][jT])
    {
      while ((cells[q][q] == cells[q+k4][q + k4]) && (q + k4 < 3))
      {
        k4++;
        if (k4 > 2)
        {
          winner = cells[iT][jT];
          break;
        }
        if ((k4<3) && (k4>max4))
        {
          max4 = k4;
          k4 = 0;
        }
      }
    }
  }



  for (int q = 1; q < 3; q++)
  {
    for (int q1 = 0; q1 < 2; q1++)
    {
      if (cells[q1][q + q1] == cells[iT][jT])
      {
        while ((cells[q1][q + q1] == cells[q1 + k4][q + k4 + q1]) && (q1 + k4 < 3))
        {
          k4++;
          if (k4 > 2)
          {
            winner = cells[iT][jT];
            break;
          }
          if ((k4<3) && (k4>max4))
          {
            max4 = k4;
            k4 = 0;
          }
        }
        if (cells[q + q1][q1] == cells[iT][jT])
        {
          while ((cells[q + q1][q1] == cells[q + k4 + q1][q1 + k4]) && (q1 + k4 < 3))
          {
            k4++;
            if (k4 > 2)
            {
              winner = cells[iT][jT];
              break;
            }
            if ((k4<3) && (k4>max4))
            {
              max4 = k4;
              k4 = 0;
            }
          }
        }
      }
    }
  }
*/
}

void Field::bestTurn(){
  int x, y; // Перенос из класса
  initEvr();

  int temp = 0;

  if (masEvr[1][1] == 0){                //Всегда ставим в середине
    makeTurn(2, 2);
    printText(2, 2);
    return; 
  }

  for (int i = 0, temp = 0; i<3; i++){        //Проверяем на победу  O по горизонтали.
    for (int j = 0; j<3; j++)
      temp += masEvr[i][j];
    if (temp == 2){
      for (int g = 0; g<3; g++)
        if (masEvr[i][g] == 0){
          makeTurn(i + 1, g + 1);
          printText(i+1, g+1);
          return; 
        }
    }
//  temp = 0; Лишнее!
  }

  for (int i = 0, temp = 0; i<3; i++){        //Проверяем на победу  O по вертикали.
    for (int j = 0; j<3; j++)
      temp += masEvr[j][i];
    if (temp == 2){
      for (int g = 0; g<3; g++)
        if (masEvr[g][i] == 0){
          makeTurn(g + 1, i + 1);
          printText(g+1, i+1);
          return; 
        }
    }
//  temp = 0; Лишнее!
  }

  for (int i = 0, temp = 0; i<3; i++){            //Проверяем на победу О по диагонали [0][0]
    temp += masEvr[i][i];
    if (temp == 2)
      for (int i = 0; i<3; i++)
        if (cells[i][i] == EMPTY){
          makeTurn(i + 1, i + 1);
          printText(i+1, i+1);
          return; 
        }
  }

//  temp = 0; Лишнее!
//  temp += (masEvr[0][2] + masEvr[1][1] + masEvr[2][0]); //Проверяем по диагонали [0][2]
  temp = (masEvr[0][2] + masEvr[1][1] + masEvr[2][0]); //Проверяем по диагонали [0][2]
  if (temp == 2)
    //  for (int i = 0; i<3; i++) Цикл не нужен (лишний), здесь тупо проверка по элементам. ОШИБКА?
      if (cells[0][2] == EMPTY){
//      temp = 0; Лишнее!
        makeTurn(1, 3);
        printText(1, 3);
        return; 
      }
      else if (cells[1][1] == EMPTY){
//      temp = 0; Лишнее!
        makeTurn(2, 2);
        printText(2, 2);
        return; 
      }
      else if (cells[2][0] == EMPTY){
//      temp = 0; Лишнее!
        makeTurn(3, 1);
        printText(3, 1);
        return; 
      }

      for (int i = 0, temp = 0; i<3; i++){        //Проверяем на победу  X по вертикали.
        for (int j = 0; j<3; j++)
          temp += masEvr[j][i];
        if (temp == -2){
          for (int g = 0; g<3; g++)
            if (masEvr[g][i] == 0){
              makeTurn(g + 1, i + 1);
              printText(g+1, i+1);
              return; 
            }
        }
//      temp = 0; Лишнее!
      }

      for (int i = 0, temp = 0; i<3; i++){        //Проверяем на победу X по горизонтали.
        for (int j = 0; j<3; j++)
          temp += masEvr[i][j];
        if (temp == -2){
          for (int g = 0; g<3; g++)
            if (masEvr[i][g] == 0){
              makeTurn(i + 1, g + 1);
              printText(i+1, g+1);
              return; 
            }
        }
//      temp = 0; Лишнее!
      }

      for (int i = 0, temp = 0; i<3; i++){            //Проверяем на победу X по диагонали
        temp += masEvr[i][i];
        if (temp == -2)
          for (int i = 0; i<3; i++)
            if (cells[i][i] == EMPTY){
              makeTurn(i + 1, i + 1);
              printText(i+1,i+1);
              return; 
            }
      }

//      temp = 0; Лишнее!
//      temp += (masEvr[0][2] + masEvr[1][1] + masEvr[2][0]); //Проверяем по диагонали [0][2]
      temp = (masEvr[0][2] + masEvr[1][1] + masEvr[2][0]); //Проверяем по диагонали [0][2]
      if (temp == -2)
//        for (int i = 0; i<3; i++) Цикл не нужен (лишний), здесь тупо проверка по элементам. ОШИБКА?
          if (cells[0][2] == EMPTY){
//      temp = 0; Лишнее!
            makeTurn(1, 3);
            printText(1, 3);
            return; 
          }
          else if (cells[1][1] == EMPTY){
//      temp = 0; Лишнее!
            makeTurn(2, 2);
            printText(2, 2);
            return; 
          }
          else if (cells[2][0] == EMPTY){
//      temp = 0; Лишнее!
            makeTurn(3, 1);
            printText(3, 1);
            return; 
          }

          //В случайную пустую клетку
          do{
            x = rand() % 3;
            y = rand() % 3;
          } while (!(x >= 0 && x<3 && y >= 0 && y<3 && cells[x][y] == EMPTY));
          makeTurn(x + 1, y + 1);
          printText(x+1, y+1);
}

void Field::initEvr()
{
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (cells[i][j] == EMPTY) masEvr[i][j] = 0;
      else if (cells[i][j] == CROSS) masEvr[i][j] = -1;
      else if (cells[i][j] == ZERO) masEvr[i][j] = 1;

    }
  }
}

int Field::statWon(){
  int status = 0;
  if (winner == EMPTY){ status = 0; }
  else
  {status = 1;
  }

  return status;
}

bool Field::isWon(bool cross) const
{
  return cross ? (winner == CROSS) : (winner == ZERO);
}

bool Field::isOver() const
{
  if (winner != EMPTY)
    return true;
  for (int i = 0; i<3; i++)
    for (int j = 0; j<3; j++)
      if (cells[i][j] == EMPTY)
        return false;
  return true;
}

Cell Field::getCell(int i, int j) const
{
  if (i <= 0 || i>3 ||
    j <= 0 || j>3)
    return EMPTY;
  return cells[i - 1][j - 1];
}

bool Field::isCrossTurnNow() const
{
  return isCrossTurn;
}

char sym[] = { 'X', '0', '.' };

void Field::print() const
{
  cout << "  1-2-3" << endl;
  for (int j = 0; j<3; j++)
  {
    cout << j+1 << " ";
    for (int i = 0; i<3; i++)
    {
      cout << sym[cells[i][j]] << " ";
    }
    cout << endl;
  }
  //	cout << "  1-2-3" << endl;
}
void Field::printText(int pos1, int pos2){
  cout << "За Вас походил компьютер в клетку " << pos1<<","<<pos2<<" Это наилучший ход по мнению компьютера!!!"<< endl;



}
void Field::printResult() const
{
  if (isWon(true))
  {
    cout << "Победили крестики" << endl;
  }
  else if (isWon(false))
  {
    cout << "Победили нолики" << endl;
  }
  else if (isOver())
  {
    cout << "Ничья" << endl;
  }
  else
  {
    cout << "Партия не закончена" << endl;
  }



}

void Field::openGame()
{
  ifstream in("SavedGame.txt");

  int a;

  for (int q = 0; q < 3; q++)
  {
    for (int q1 = 0; q1 < 3; q1++)
    {

      in >> a;
      if (a == 2)
        cells[q][q1] = EMPTY;
      if (a == 1)
        cells[q][q1] = ZERO;
      if (a == 0)
        cells[q][q1] = CROSS;

    }
  }


  in.close();
}
void Field::saveGame() 
{   
  ofstream out("SavedGame.txt");
  out.clear();

  for (int q = 0; q < 3; q++)
  {
    for (int q1 = 0; q1 < 3; q1++)
    {
      out << cells[q][q1];
    }
    out << endl;
  }


  out.close();
}


