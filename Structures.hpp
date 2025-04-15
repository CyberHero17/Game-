#pragma once
#include <iostream>
struct point // возможно не нужен
{
    float x;
    float y;
};

class Vector2D
{
public:
    float x, y;
    // Конструкторы
    Vector2D() : x(0), y(0) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    // Деструктор
    ~Vector2D() {}




    // Перегруженный оператор - сравнение двух векторов на равенство
    bool operator== (const Vector2D& v2) const;

    // Перегруженный оператор - неравенство векторов
    bool operator!= (const Vector2D& v2) const;

    // Сумма двух векторов
    Vector2D operator+ (const Vector2D& v2) const;

    // Вычитание векторов
    Vector2D operator- (const Vector2D& v2) const;

    // Оператор умножения вектора на скаляр

    Vector2D operator* (const float a) const;

    float ModuleQuadr();
};


// Оператор умножения скаляра на вектор
Vector2D operator* (float a, const Vector2D& v);



// Вывод вектора
std::ostream& operator<<(std::ostream& os, const Vector2D& v);

// Чтение вектора
std::istream& operator>>(std::istream &is, Vector2D &v);
