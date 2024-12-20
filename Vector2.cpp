#include "Vector2.h"

Vector2 operator+(const Vector2 &left, const Vector2 &right)
{
    return Vector2{left.x + right.x, left.y + right.y};
}

bool operator==(const Vector2 &left, const Vector2 &right)
{
    return (left.x == right.x && left.y == right.y);
}