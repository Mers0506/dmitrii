#include <QCoreApplication>
#include <QDebug>

#include "conio.h"

#define HEIGHT 8
#define WIDTH 8

//Форрма (базовый класс)
struct Shape
{
public:
  int xCoord;
  int yCoord;
  int height;
  int width;
  char **figure;
};

//Форма 'Планер' (наследуется от 'Shape')
struct Glider : public Shape
{                                         //   | X |
  static const int GLIDER_SIZE = 3;       //- -|- -|- -
  Glider( int x , int y );                //   |   | X
  ~Glider();                              //- -|- -|- -
};                                        // X | X | X

//Форма 'Мигалка' (наследуется от 'Shape')
struct Blinker : public Shape
{                                         //   | X |
  static const int BLINKER_HEIGHT = 3;    //- -|- -|- -
  static const int BLINKER_WIDTH = 1;     //   | X |
                                          //- -|- -|- -
  Blinker( int x , int y );               //   | X |
  ~Blinker();
};

//Основной механизм:
class GameOfLife
{
public:
  GameOfLife( Shape shp );  //Конструктор класса
  void print();             //Вывод на экран
  void control();           //Чтение с команды клавиатуры
  void update();            //Обновление состояния
  char getState( char state , int xCoord , int yCoord , bool toggle); //Получить новое состояние точки
  void iterate(unsigned int iterations);  //Итерация рабочего цикла

private:
  char world[HEIGHT][WIDTH];      //Состояние на четном шаге
  char otherWorld[HEIGHT][WIDTH]; //Состояние на нечентром шаге
  Shape shape;                    //Форма
  bool toggle;                    //Переключение чет/нечет
  bool runTheGame;                //Начало/завершение процесса
};

GameOfLife::GameOfLife( Shape shp )// : shape(shp) , toggle(true)
{
  int i, j;

  shape = shp;
  toggle = true;
  runTheGame = true;

  //Заполняем пустые клетки:
  for (i = 0; i < HEIGHT; i++ )
  {
    for (j = 0; j < WIDTH; j++ )
    {
      world[i][j] = '.';
    }
  }

  //Выставляем объект:
  for (i = shape.yCoord; i - shape.yCoord < shape.height; i++)
  {
    for (j = shape.xCoord; j - shape.xCoord < shape.width; j++)
    {
      if ( i < HEIGHT && j < WIDTH )
      {
        world[i][j] = shape.figure[ i - shape.yCoord ][j - shape.xCoord ];
      }
    }
  }
}

//Вывод текущего состояния на экран:
void GameOfLife::print()
{
  int i, j;
  QDebug debug = qDebug();

  //Очищаем экран:
  system("cls");

  debug << "\n";

  //Выводим состояние
  for (i = 0; i < HEIGHT; i++ )
  {
    for (j = 0; j < WIDTH; j++ )
    {
      if (toggle)
        debug << world[i][j];
      else
        debug << otherWorld[i][j];
    }
    debug << "\n";
  }
}

void GameOfLife::control()
{
  int key;

  key = getch();

  switch (key)
  {
  case 27:              //Esc
    runTheGame = false;
    break;
  }

}

void GameOfLife::update()
{
  for ( int i = 0; i < HEIGHT; i++ )
  {
    for ( int j = 0; j < WIDTH; j++ )
    {
      if (toggle)
        otherWorld[i][j] = GameOfLife::getState(world[i][j], i, j, toggle);
      else
        world[i][j] = GameOfLife::getState(otherWorld[i][j], i, j, toggle);
    }
  }

  //Меняем состоянием переключателя:
  toggle = !toggle;
}

char GameOfLife::getState( char state, int yCoord, int xCoord, bool toggle )
{
  int i, j;
  int neighbors = 0;

  //Сканируем окрестность:
  for (i = yCoord - 1; i <= yCoord + 1; i++)
  {
    for (j = xCoord - 1; j <= xCoord + 1; j++)
    {
      //Пропускам саму точку:
      if (i == yCoord && j == xCoord)
      {
        continue;
      }
      //Исключаем краевые точки:
      if ((i > -1) && (i < HEIGHT) && (j > -1) && (j < WIDTH))
      {
        //Нашли соседа:
        if ((toggle && (world[i][j] == 'X')) || (!toggle && (otherWorld[i][j] == 'X')))
        {
          neighbors++;
        }
      }
    }
  }

  //Если клетка жива:
  if (state == 'X')
  {
    if ((neighbors > 1) && (neighbors < 4))
      //Клетка продолжает жить
      return 'X';
    else
      //Клетка 'умирает' от одиночества или от  перенаселения
      return '.';
  }
  else
  {
    if (neighbors == 3)
      //Мертвая клетка оживает:
      return 'X';
    else
      //Мертвая клетка остается мертвой:
      return '.';
  }
}

//Совершение итерации:
void GameOfLife::iterate( unsigned int iterations )
{
  int i;

  for ( i = 0; i < iterations; i++ )
  {
    if (runTheGame)
    {
      //Вывод на экран:
      print();

      //Управление процессом:
      control();

      //Обновление состояния:
      update();
    }
  }
}

Glider::Glider( int x , int y )
{
  int i, j;

  xCoord = x;
  yCoord = y;
  height = GLIDER_SIZE;
  width = GLIDER_SIZE;

  //Выделяем память по указатели на строки:
  figure = new char*[GLIDER_SIZE];

  //Выделяем память под строки двумерного массива:
  for (i = 0; i < GLIDER_SIZE; i++ )
  {
    figure[i] = new char[GLIDER_SIZE];
  }

  //Заполняем фон:
  for (i = 0; i < GLIDER_SIZE; i++ )
  {
    for (j = 0; j < GLIDER_SIZE; j++ )
    {
      figure[i][j] = '.';
    }
  }
                        // _ _ _ _ _ _
  figure[0][1] = 'X';   //|   | X |
  figure[1][2] = 'X';   //|- -|- -|- -
  figure[2][0] = 'X';   //|   |   | X
  figure[2][1] = 'X';   //|- -|- -|- -
  figure[2][2] = 'X';   //| X | X | X
}

Glider::~Glider()
{
  int i;

  //Освобождаем память двумерного массива:
  for (i = 0; i < GLIDER_SIZE; i++)
  {
    //Удаляем строки:
    delete[] figure[i];
  }
  delete[] figure;
}

Blinker::Blinker( int x , int y )
{
  int i, j;

  xCoord = x;
  yCoord = y;
  height = BLINKER_HEIGHT;
  width = BLINKER_WIDTH;
  figure = new char*[BLINKER_HEIGHT];

  for (i = 0; i < BLINKER_HEIGHT; i++)
  {
    figure[i] = new char[BLINKER_WIDTH];
  }
                                          // _ _ _ _ _ _ _
  for (i = 0; i < BLINKER_HEIGHT; i++)    //|   | X |   |
  {                                       //|- -|- -|- -|-
    for (j = 0; j < BLINKER_WIDTH; j++)   //|   | X |   |
    {                                     //|- -|- -|- -|-
      figure[i][j] = 'X';                 //|   | X |   |
    }
  }
}

Blinker::~Blinker()
{
  int i;

  for (i = 0; i < BLINKER_HEIGHT; i++)
  {
    delete[] figure[i];
  }
  delete[] figure;
}

int main()
{
  Glider glider(0,0);
  Blinker blinker(1,0);

  GameOfLife gol(glider);
  gol.iterate(20);

  GameOfLife gol2(blinker);
  gol2.iterate(20);
}

