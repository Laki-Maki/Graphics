#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Canvas.h"
using namespace std;


int main()
{
	setlocale(0, "");
	canvas c; // создаем холст

	cout << "Меню" << endl;
	cout << "1. Нарисовать точку" << endl;
	cout << "2. Нарисовать линию" << endl;
	cout << "3. Нарисовать четырехугольник незакрашенный" << endl;
	cout << "4. Нарисовать закрашенный четырехугольник" << endl;
	cout << "5. Нарисовать незакрашенный эллипс" << endl;
	cout << "6. Нарисовать закрашенный эллипс" << endl;
	cout << "7. Нарисовать незакрашенный шестиугольник" << endl;
	cout << "8. Нарисовать закрашенный шестиугольник" << endl;
	cout << "9. Удалить фигуру" << endl;
	cout << "10. Очистить список" << endl;
	cout << "11. Вывести спискок" << endl;
	cout << "12. Нарисовать" << endl;
	cout << "13. Exit" << endl;
	int choise;

	do
	{
		cout << endl << endl << "Выбери пункт: ";
		cin >> choise;
		switch (choise)
		{
		case 1:
		{
			int x, y;
			cout << "введите координаты (x1, y1): ";
			cin >> x >> y;
			c.add((shape*)new point(x, y, RGB(255, 0, 255)), "Точка");
			//b.append("точка\n");
			break;
		}
		case 2:
		{
			int x1, y1, x2, y2;
			cout << "введите координаты (x1, y1, x2, y2): ";
			cin >> x1 >> y1 >> x2 >> y2;
			c.add((shape*)new line(x1, y1, x2, y2, RGB(255, 0, 255)), "Линия");
			//b.append("линия\n");
			break;
		}
		case 3:
		{
			int x1, y1, x2, y2;
			cout << "введите координаты (x1, y1, x2, y2): ";
			cin >> x1 >> y1 >> x2 >> y2;
			c.add((shape*)new rectangle(x1, y1, x2, y2, RGB(0, 0, 255), false, RGB(0, 255, 0)), "незакрашенный четырехугольник");
			//b.append("незакрашенный четырехугольник\n");
			break;
		}
		case 4:
		{
			int x1, y1, x2, y2;
			cout << "введите координаты (x1, y1, x2, y2): ";
			cin >> x1 >> y1 >> x2 >> y2;
			c.add((shape*)new rectangle(x1, y1, x2, y2, RGB(0, 0, 255), true, RGB(0, 255, 0)), "закрашенный четырехугольник");
			//b.append("закрашенный четырехугольник\n");
			break;
		}
		case 5:
		{
			int x1, y1, x2, y2;
			cout << "введите координаты (x1, y1, x2, y2): ";
			cin >> x1 >> y1 >> x2 >> y2;
			c.add((shape*)new ellipse(x1, y1, x2, y2, RGB(0, 0, 255), false, RGB(0, 255, 0)), "незакрашенный эллипс");
			//b.append("незакрашенный эллипс\n");
			break;
		}
		case 6:
		{
			int x1, y1, x2, y2;
			cout << "введите координаты (x1, y1, x2, y2): ";
			cin >> x1 >> y1 >> x2 >> y2;
			c.add((shape*)new ellipse(x1, y1, x2, y2, RGB(0, 0, 255), true, RGB(0, 255, 0)), "закрашенный эллипс");
			//b.append("закрашенный эллипс\n");
			break;
		}
		case 7:
		{
			//int x, y;
			POINT a[6];
			cout << "введите координаты (x1, y1 ... x6, y6): ";
			for (int i = 1; i <= 6; i++)
			{
				cin >> a[i].x >> a[i].y;
			}
			c.add((shape*)new polygon(a, RGB(0, 0, 255), false, RGB(0, 255, 0)), "незакрашенный шестиугольник");
			//b.append("незакрашенный шестиугольник\n");
			break;
		}
		case 8:
		{
			//int x, y;
			POINT a[6];
			cout << "введите координаты (x1, y1 ... x6, y6): ";
			for (int i = 1; i <= 6; i++)
			{
				cin >> a[i].x >> a[i].y;
			}
			c.add((shape*)new polygon(a, RGB(0, 0, 255), true, RGB(0, 255, 0)), "закрашенный шестиугольник");
			//b.append("закрашенный шестиугольник\n");
			break;
		}
		case 9:
		{
			c.show_name_figures();
			int k;
			cout << "Введите объект для удаления";
			cin >> k;
			//cout << "удаление с индексом " << k;
			c.deli(k);
			break;
		}
		case 10:
		{
			c.clear();
			break;
		}
		case 11:
		{
			c.show_name_figures();
			break;
		}
		case 12:
		{
			system("cls");
			c.show(); // вывод графических примитивов на холст
			_getch();
			system("cls");
			cout << "Меню" << endl;
			cout << "1. Нарисовать точку" << endl;
			cout << "2. Нарисовать линию" << endl;
			cout << "3. Нарисовать четырехугольник незакрашенный" << endl;
			cout << "4. Нарисовать закрашенный четырехугольник" << endl;
			cout << "5. Нарисовать незакрашенный эллипс" << endl;
			cout << "6. Нарисовать закрашенный эллипс" << endl;
			cout << "7. Нарисовать незакрашенный шестиугольник" << endl;
			cout << "8. Нарисовать закрашенный шестиугольник" << endl;
			cout << "9. Удалить фигуру" << endl;
			cout << "10. Очистка списка" << endl;
			cout << "11. Вывод списка" << endl;
			cout << "12. Нарисовать" << endl;
			cout << "13. Выход" << endl;
			break;
		}
		}
	} while (choise != 13);
	return 0;
}