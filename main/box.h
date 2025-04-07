#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <windows.h>

// ������� ����� ��� ���� �����
class shape {
public:
    virtual void show(HDC hdc) = 0;  // ����� ����������� ����� ��� ����������� �����
    virtual ~shape() = default;
};

// ����� �����
class point : public shape {
public:
    int x, y;
    COLORREF color;

    point(int x, int y, COLORREF color = RGB(255, 255, 255));
    void show(HDC hdc) override;
};

// ����� �������
class line : public shape {
    point start;
    point end;
    COLORREF color;

public:
    line(int x1, int y1, int x2, int y2, COLORREF color = RGB(255, 255, 255));
    void show(HDC hdc) override;
};

// ����� �������
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

// ����� ��������������
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

// ����� �������������� (�������������)
class polygon : public shape {
    std::vector<point> vertices;
    COLORREF color;
    COLORREF background_color;
    bool filled;

public:
    polygon(const std::vector<point>& vertices, COLORREF color, bool filled = false, COLORREF background_color = 0);
    void show(HDC hdc) override;
};

// ����� Canvas ��� ���������� ��������
class canvas {
    std::vector<shape*> figures;
    HWND hWnd;
    HDC hdc;

public:
    canvas();
    ~canvas();

    void add(shape* s);      // ���������� ������
    void remove(int index);  // �������� ������
    void clear();            // ������� ������ �����
    void show();             // ����������� ���� �����
    void display_info();     // ����� ���������� � �������
};

#endif // CANVAS_H
