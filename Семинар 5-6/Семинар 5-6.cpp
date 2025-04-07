#include <conio.h> // для _getch
#include <windows.h>

// класс точка
class point {
	int x, y;
public:
	point(int x, int y) : x(x), y(y) {} // конструктор с инициализатором
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
};
// класс прямоугольник, использующий класс точка
class rectangle {
	point top_left;
	point bottom_right;
public:
	// конструктор
	rectangle(int x1, int y1, int x2, int y2) : top_left(x1, y1), bottom_right(x2, y2) {}
	int getX1()
	{
		return top_left.getY();
	}
	int getY1()
	{
		return top_left.getY();
	}
	int getX2()
	{
		return bottom_right.getX();
	}
	int getY2()
	{
		return bottom_right.getY();
	}
};

int main()
{
	rectangle* rec = new rectangle(10, 10, 100, 100); //создаем объект прямоугольник

	HWND hWnd = GetConsoleWindow(); // ссылка на окно
	HDC hdc = GetDC(hWnd);		// ссылка на контекст устройства графического вывода
	SelectObject(hdc, GetStockObject(DC_PEN)); // выбор стандартного пера
	SelectObject(hdc, GetStockObject(DC_BRUSH)); // выбор стандартной кисти

	SetDCPenColor(hdc, RGB(255, 0, 0)); // установка пера красного цвета
	SetDCBrushColor(hdc, RGB(0, 255, 0)); // установка кисти зеленого цвета
	Rectangle(hdc, rec->getX1(), rec->getY1(), rec->getX2(), rec->getY2());	// вывод прямоугольника цветом пера закрашенного цветом кисти
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); // отключение закраски кистью

	ReleaseDC(hWnd, hdc);		// освобождение контекста устройства вывода


	_getch();

	delete rec;

	return 0;
}
