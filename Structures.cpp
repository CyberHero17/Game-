#pragma once
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
    Vector2D(int x, int y) : x(x), y(y) {}
    // Деструктор
    ~Vector2D() {}

    // Перегруженный оператор - сравнение двух векторов на равенство
    bool operator== (const Vector2D& v2) const {
        return x == v2.x && y == v2.y;
    }

    // Перегруженный оператор - неравенство векторов
    bool operator!= (const Vector2D& v2) const {
        return !(*this == v2);
    }

    // Сумма двух векторов
    Vector2D operator+ (const Vector2D& v2) const {
        return Vector2D(x + v2.x, y + v2.y);
    }

    // Вычитание векторов
    Vector2D operator- (const Vector2D& v2) const {
        return Vector2D(x - v2.x, y - v2.y);
    }

    // Оператор умножения вектора на скаляр

    Vector2D operator* (const float a) const {
        return Vector2D(x * a, y * a);
    }
};

// Оператор умножения скаляра на вектор
inline Vector2D operator* (const float a, const Vector2D& v) {
   return v * a;
}

// Вывод вектора
inline std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << "; " << v.y << ")";
    return os;
}

// Чтение вектора
inline std::istream& operator>>(std::istream &is, Vector2D &v) {
    int x, y;
    is >> x >> y;
    v.x = x;
    v.y = y;
    return is; 
} 