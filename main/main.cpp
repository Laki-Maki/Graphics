#include <iostream>
#include <conio.h>
#include "box.h"

int main() {
    canvas c;
    char choice;

    setlocale(LC_ALL, "ru");

    do {
        std::cout << "Выберите фигуру для добавления:\n";
        std::cout << "p - точка, l - отрезок, e - эллипс, r - прямоугольник, g - многоугольник, q - выход: ";
        std::cin >> choice;

        if (choice == 'p') {
            int x, y;
            std::cout << "Введите координаты точки (x y): ";
            std::cin >> x >> y;
            c.add(new point(x, y));
        }
        else if (choice == 'l') {
            int x1, y1, x2, y2;
            std::cout << "Введите координаты начала и конца отрезка (x1 y1 x2 y2): ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            c.add(new line(x1, y1, x2, y2));
        }
        else if (choice == 'e') {
            int x1, y1, x2, y2;
            bool filled;
            std::cout << "Введите координаты верхнего левого и нижнего правого углов эллипса (x1 y1 x2 y2): ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            std::cout << "Закрашен? (1 - да, 0 - нет): ";
            std::cin >> filled;
            c.add(new ellipse(x1, y1, x2, y2, RGB(255, 0, 0), filled, RGB(0, 255, 0)));
        }
        else if (choice == 'r') {
            int x1, y1, x2, y2;
            bool filled;
            std::cout << "Введите координаты верхнего левого и нижнего правого углов прямоугольника (x1 y1 x2 y2): ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            std::cout << "Закрашен? (1 - да, 0 - нет): ";
            std::cin >> filled;
            c.add(new rectangle(x1, y1, x2, y2, RGB(0, 0, 255), filled, RGB(0, 255, 255)));
        }
        else if (choice == 'g') {
            int n;
            std::cout << "Введите количество вершин многоугольника: ";
            std::cin >> n;
            std::vector<point> vertices;
            for (int i = 0; i < n; ++i) {
                int x, y;
                std::cout << "Введите координаты вершины " << i + 1 << " (x y): ";
                std::cin >> x >> y;
                vertices.push_back(point(x, y));
            }
            bool filled;
            std::cout << "Закрашен? (1 - да, 0 - нет): ";
            std::cin >> filled;
            c.add(new polygon(vertices, RGB(255, 0, 255), filled, RGB(255, 255, 0)));
        }

        c.display_info();
    } while (choice != 'q');

    std::cout << "Вывод фигур на экран...\n";
    c.show();
    _getch();  // Ожидание перед закрытием программы

    return 0;
}
