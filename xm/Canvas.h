
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

class shape {
public:
	virtual void show(HDC hdc) {} // ����������� �����, ����������� ������������ ����� show ����������� ������
}; // ������� ����� ��� �����

// ����� �����
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
// ����� �������������, ������������ ����� �����
class rectangle : shape
{
	point top_left;
	point bottom_right;
	COLORREF color;// ���� �������
	COLORREF background_color;
	bool filled;
public:
	rectangle(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0) : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
		SetDCPenColor(hdc, color); // ��������� ����� ������� ������
		SetDCBrushColor(hdc, background_color); // ��������� ����� ��������
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // ����� ����������� �����
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���������� ��������
		}
		Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}

};

class line : shape
{
	point start;
	point finish;
	COLORREF color;// ���� �������
public:
	line(int x1, int y1, int x2, int y2, COLORREF c) : start(x1, y1), finish(x2, y2), color(c) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
		SetDCPenColor(hdc, color); // ��������� ����� ������� ������

		SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���������� ��������
		LineTo(hdc, finish.x, finish.y);
	}
};

class ellipse : shape
{
	point top_left;
	point bottom_right;
	COLORREF color;// ���� �������
	COLORREF background_color;
	bool filled;
public:
	ellipse(int x1, int y1, int x2, int y2, COLORREF c, bool filled = false, COLORREF bc = 0) : top_left(x1, y1), bottom_right(x2, y2), color(c), background_color(bc), filled(filled) {}
	void show(HDC hdc) {
		SelectObject(hdc, GetStockObject(DC_PEN)); // ����� ������������ ����
		SetDCPenColor(hdc, color); // ��������� ����� ������� ������
		SetDCBrushColor(hdc, background_color); // ��������� ����� ��������
		if (filled)
		{
			SelectObject(hdc, GetStockObject(DC_BRUSH)); // ����� ����������� �����
		}
		else
		{
			SelectObject(hdc, GetStockObject(NULL_BRUSH)); // ���������� ��������
		}
		Ellipse(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
	}

};

// ����� ������������� 
class polygon : shape {
	POINT* lppt; // ��������� �� ������ �������� point, �������� lppt ��������� �� ������ �������� point, � ������� ������ ��������� ���������� ������ ��������������.
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
	vector <pair<shape*, string>> figures; // ������ ��� �������� �����
	HWND hWnd;
	HDC hdc;
public:
	canvas()
	{
		hWnd = GetConsoleWindow(); // ������ �� ����
		hdc = GetDC(hWnd);		// ������ �� �������� ���������� ������������ ������
	}
	~canvas()
	{
		ReleaseDC(hWnd, hdc);		// ������������ ��������� ���������� ������
	}
	void add(shape* s, string name)
	{
		figures.push_back(make_pair(s, name));
	}
	void clear() //������� ������
	{
		figures.clear();
	}
	void show() { // ����������� ����������� ���������� ������� ������ show()
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
			delete figures[index].first; // ������� ������ ������ 
			figures.erase(figures.begin() + index); // ������� ������� �� ������� 
		}
	}
};