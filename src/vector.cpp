#include "vector.hpp"

#include <cmath>

namespace cayv {

Vector2f::Vector2f(float a, float b) : x(a), y(b) {}

Vector2f Vector2f::normalise()
{
    float l = length();
    if (l == 0.f) return Vector2f(0, 0);
    return Vector2f(x/l, y/l);
}

float Vector2f::length()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector2f::argument()
{
    if (x == 0 && y == 0) return VECTOR_NO_ARGUMENT;

    if (y == 0) {
        if (x > 0) return 0;
        if (x < 0) return CPI;
    }

    if (x == 0) {
        if (y < 0) return (3/2) * CPI;
        if (y > 0) return (1/2) * CPI;
    }

    float at = atanf(y/x);

    if (x > 0 && y > 0) return at; // First quadrant
    if (x < 0 && y > 0) return CPI - at; // Second quadrant
    if (x < 0 && y < 0) return CPI + at; // Third quadrant
    if (x > 0 && y < 0) return 2 * CPI - at; // Fourth quadrant

    return VECTOR_NO_ARGUMENT;
}

Vector2f Vector2f::torect()
{
    return Vector2f(x * cosf(y), x * sinf(y));
}

Vector2f Vector2f::topolar()
{
    return Vector2f(length(), argument());
}

Vector2f Vector2f::operator+(float s)
{
    return Vector2f(x + s, y);
}

Vector2f Vector2f::operator-(float s)
{
    return Vector2f(x - s, y);
}

Vector2f Vector2f::operator*(float s)
{
    return Vector2f(s * x, s * y);
}

Vector2f Vector2f::operator/(float s)
{
    if (s == 0) return Vector2f(CNAN, CNAN);
    return Vector2f(x / s, y / s);
}

Vector2f Vector2f::operator+(Vector2f v)
{
    return Vector2f(x + v.x, y + v.y);
}

Vector2f Vector2f::operator-(Vector2f v)
{
    return Vector2f(x - v.x, y - v.y);
}

Vector2f Vector2f::operator*(Vector2f v)
{
    return Vector2f(x * v.x - y * v.y, x * v.y + y * v.x);
}

Vector2f Vector2f::operator/(Vector2f w)
{
    Vector2f v(x, y);
    return (v * w.conjugate()) / (w * w.conjugate()).x;
}

Vector2f Vector2f::rotateby(float radians)
{
    return Vector2f(x, y) * Vector2f(0, -1).exp(radians / CPI);
}

Vector2f Vector2f::exp(float exp)
{
    Vector2f w = topolar();
    w.x = pow(w.x, exp);
    w.y = exp * w.y;
    return w.torect();
}

Vector2f Vector2f::conjugate()
{
    return Vector2f(x, -y);
}

}
