#include "framework.h"
#include "Vector2.h"

bool Vector2::IsBetween(Vector2 a, Vector2 b)
{
    float crossA = this->Cross(a);
    float crossB = this->Cross(b);

    return crossA * crossB < 0;
}

int Vector2::ManhattenDistance(const Vector2& other) const
{
    return abs(other.x - x) + abs(other.y - y);
}
