
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

class shape {
public:
	virtual void show(HDC hdc) {} // виртуальный метод, позволяющий использовать метод show конкретного класса
}; // базовый класс для фигур

// класс точка
class point : shape {
public:
	int x, y;
	COLORREF color;
	point(int x, int y, COLORREF c = RGB(255, 255, 255)) : x(x), y(y), color(c) {}
	void show(HDC hdc)
	{
		SetPixel(hdc, x, y, color);
	}
};
// класс прямоугольник, использующий класс точка
class rectangle : shape
{
	point top_left;
	point bottom_right;
	COLORREF color;// цвет границы
	COLORREF background_color;
	bool filled;
public:
	rectangle(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0) : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
		SetDCPenColor(hdc, color); // установка цвета контура фигуры
		SetDCBrushColor(hdc, background_color); // установка цвета закраски
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
		}
		Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}

};

class line : shape
{
	point start;
	point finish;
	COLORREF color;// цвет границы
public:
	line(int x1, int y1, int x2, int y2, COLORREF c) : start(x1, y1), finish(x2, y2), color(c) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
		SetDCPenColor(hdc, color); // установка цвета контура фигуры

		SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
		LineTo(hdc, finish.x, finish.y);
	}
};

class ellipse : shape
{
	point top_left;
	point bottom_right;
	COLORREF color;// цвет границы
	COLORREF background_color;
	bool filled;
public:
	ellipse(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0) : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
		SetDCPenColor(hdc, color); // установка цвета контура фигуры
		SetDCBrushColor(hdc, background_color); // установка цвета закраски
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски
		}
		Ellipse(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}

};

// Класс многоугольник 
class polygon : shape {
	POINT* lppt; // указатель на массив структур point, Параметр lppt указывает на массив структур point, в котором должны находится координаты вершин многоугольника.
	COLORREF color;
	COLORREF background_color;
	bool filled;
public:
	polygon(const POINT top[], COLORREF c, bool filled = false, COLORREF bc = RGB(255, 255, 255)) : color(bc), background_color(bc), filled(filled) {
		lppt = new POINT[6];
		for (int i = 0; i < 6; i++) {
			lppt[i] = top[i];
		}
	}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetDCPenColor(hdc, color);
		if (filled) {
			SelectObject(hdc, GetStockObject(DC_BRUSH));
			SetDCBrushColor(hdc, color);
		}
		else {
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
		}
		Polygon(hdc, lppt, 6);
	}
};

class canvas
{
	vector <pair<shape*, string>> figures; // вектор для хранения фигур
	HWND hWnd;
	HDC hdc;
public:
	canvas()
	{
		hWnd = GetConsoleWindow(); // ссылка на окно
		hdc = GetDC(hWnd);		// ссылка на контекст устройства графического вывода
	}
	~canvas()
	{
		ReleaseDC(hWnd, hdc);		// освобождение контекста устройства вывода
	}
	void add(shape* s, string name)
	{
		figures.push_back(make_pair(s, name));
	}
	void clear() //очистка холста
	{
		figures.clear();
	}
	void show() { // отображение графических примитивов вызовом метода show()
		for (size_t i = 0; i < figures.size(); i++)
			figures[i].first->show(hdc);
	}
	void show_name_figures()
	{
		int j = 0;
		for (size_t i = 0; i < figures.size(); i++, j++)
			cout << j << ". " << figures[i].second << endl;
	}
	void deli(int index)
	{
		if (index >= 0 && index < figures.size())
		{
			delete figures[index].first; // Удаляем объект фигуры 
			figures.erase(figures.begin() + index); // Удаляем элемент из вектора 
		}
	}
};