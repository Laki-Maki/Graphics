#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <windows.h>

// Базовый класс для всех фигур
class shape {
public:
    virtual void show(HDC hdc) = 0;  // Чисто виртуальный метод для отображения фигур
    virtual ~shape() = default;
};

// Класс точки
class point : public shape {
public:
    int x, y;
    COLORREF color;

    point(int x, int y, COLORREF color = RGB(255, 255, 255));
    void show(HDC hdc) override;
};

// Класс отрезка
class line : public shape {
    point start;
    point end;
    COLORREF color;

public:
    line(int x1, int y1, int x2, int y2, COLORREF color = RGB(255, 255, 255));
    void show(HDC hdc) override;
};

// Класс эллипса
class ellipse : public shape {
    point top_left;
    point bottom_right;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    ellipse(int x1, int y1, int x2, int y2, COLORREF color, bool filled = false, COLORREF background_color = 0);
    void show(HDC hdc) override;
};

// Класс прямоугольника
class rectangle : public shape {
    point top_left;
    point bottom_right;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    rectangle(int x1, int y1, int x2, int y2, COLORREF color, bool filled = false, COLORREF background_color = 0);
    void show(HDC hdc) override;
};

// Класс многоугольника (шестиугольник)
class polygon : public shape {
    std::vector<point> vertices;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    polygon(const std::vector<point>& vertices, COLORREF color, bool filled = false, COLORREF background_color = 0);
    void show(HDC hdc) override;
};

// Класс Canvas для управления фигурами
class canvas {
    std::vector<shape*> figures;
    HWND hWnd;
    HDC hdc;

public:
    canvas();
    ~canvas();

    void add(shape* s);      // Добавление фигуры
    void remove(int index);  // Удаление фигуры
    void clear();            // Очистка списка фигур
    void show();             // Отображение всех фигур
    void display_info();     // Вывод информации о фигурах
};

#endif // CANVAS_H
