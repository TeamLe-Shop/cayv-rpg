#pragma once

#include <cmath>
#include <limits>

namespace cayv {

const float VECTOR_NO_ARGUMENT = -1.f; // Can't find argument
const float CPI = acos(-1.f);
constexpr float CNAN = std::numeric_limits<float>::quiet_NaN();

class Vector2f {
public:
    Vector2f(float x, float y);

    Vector2f normalise();
    float length();
    float argument();

    Vector2f torect();
    Vector2f topolar();

    Vector2f operator+(float s);
    Vector2f operator-(float s);
    Vector2f operator*(float s);
    Vector2f operator/(float s);

    Vector2f operator+(Vector2f v);
    Vector2f operator-(Vector2f v);
    Vector2f operator*(Vector2f v);
    Vector2f operator/(Vector2f v);

    Vector2f rotateby(float radians);
    Vector2f exp(float exp);
    Vector2f conjugate();

public:
    float x, y;
};

}
