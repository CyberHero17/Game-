#include "Structures.hpp"

// Перегруженный оператор - сравнение двух векторов на равенство
bool Vector2D::operator== (const Vector2D& v2) const {
    return x == v2.x && y == v2.y;
}

// Перегруженный оператор - неравенство векторов
bool Vector2D::operator!= (const Vector2D& v2) const {
    return !(*this == v2);
}

// Сумма двух векторов
Vector2D Vector2D::operator+ (const Vector2D& v2) const {
    return Vector2D(x + v2.x, y + v2.y);
}

// Вычитание векторов
Vector2D Vector2D::operator- (const Vector2D& v2) const {
    return Vector2D(x - v2.x, y - v2.y);
}

// Оператор умножения вектора на скаляр

Vector2D Vector2D::operator* (const float a) const {
    return Vector2D(x * a, y * a);
}

float Vector2D::ModuleQuadr()
{
    return x * x + y * y;
}

// Оператор умножения скаляра на вектор
Vector2D operator* (float a, const Vector2D& v) {
   return v * a;
}

// Вывод вектора
std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << "; " << v.y << ")";
    return os;
}

// Чтение вектора
std::istream& operator>>(std::istream &is, Vector2D &v) {
    int x, y;
    is >> x >> y;
    v.x = x;
    v.y = y;
    return is; 
}