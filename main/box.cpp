#include "box.h"
#include <iostream>
#include <locale>


point::point(int x, int y, COLORREF color) : x(x), y(y), color(color) {}

void point::show(HDC hdc) {
    SetPixel(hdc, x, y, color);
}

line::line(int x1, int y1, int x2, int y2, COLORREF color)
    : start(x1, y1, color), end(x2, y2, color), color(color) {}

void line::show(HDC hdc) {
    MoveToEx(hdc, start.x, start.y, NULL);
    LineTo(hdc, end.x, end.y);
}

ellipse::ellipse(int x1, int y1, int x2, int y2, COLORREF color, bool filled, COLORREF background_color)
    : top_left(x1, y1), bottom_right(x2, y2), color(color), filled(filled), background_color(background_color) {}

void ellipse::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    SetDCBrushColor(hdc, filled ? background_color : RGB(255, 255, 255));
    Ellipse(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

rectangle::rectangle(int x1, int y1, int x2, int y2, COLORREF color, bool filled, COLORREF background_color)
    : top_left(x1, y1), bottom_right(x2, y2), color(color), filled(filled), background_color(background_color) {}

void rectangle::show(HDC hdc) {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    SetDCBrushColor(hdc, filled ? background_color : RGB(255, 255, 255));
    Rectangle(hdc, top_left.x, top_left.y, bottom_right.x, bottom_right.y);
}

polygon::polygon(const std::vector<point>& vertices, COLORREF color, bool filled, COLORREF background_color)
    : vertices(vertices), color(color), filled(filled), background_color(background_color) {}

void polygon::show(HDC hdc) {
    POINT* pts = new POINT[vertices.size()];
    for (size_t i = 0; i < vertices.size(); ++i) {
        pts[i].x = vertices[i].x;
        pts[i].y = vertices[i].y;
    }

    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    SetDCBrushColor(hdc, filled ? background_color : RGB(255, 255, 255));

    Polygon(hdc, pts, vertices.size());
    delete[] pts;
}

// Реализация методов класса Canvas
canvas::canvas() {
    hWnd = GetConsoleWindow();  // получение окна консоли
    hdc = GetDC(hWnd);  // получение контекста устройства
}

canvas::~canvas() {
    ReleaseDC(hWnd, hdc);  // освобождение контекста устройства
    clear();  // очистка списка фигур
}

void canvas::add(shape* s) {
    figures.push_back(s);
}

void canvas::remove(int index) {
    if (index >= 0 && index < figures.size()) {
        delete figures[index];
        figures.erase(figures.begin() + index);
    }
}

void canvas::clear() {
    for (auto& figure : figures) {
        delete figure;
    }
    figures.clear();
}

void canvas::show() {
    for (auto& figure : figures) {
        figure->show(hdc);
    }
}

void canvas::display_info() {
    setlocale(LC_ALL, "ru");
    std::cout << "Количество фигур: " << figures.size() << std::endl;
}
