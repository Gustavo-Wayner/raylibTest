#include <cmath>

namespace gwe
{
    struct Vector2;
    float Dot(Vector2 vecA, Vector2 vecB);

    struct Vector2
    {
        float x;
        float y;
        Vector2() = default;
        Vector2(float _x, float _y) : x(_x), y(_y) {}
        Vector2(float arr[2]) : x(arr[0]), y(arr[1]) {}

        float Magnitude() { return Dot(*this, *this); }

        Vector2 GetUnitVector() { return *this / Magnitude(); }

        void Normalize() { *this /= Magnitude(); }

        void SetMagnitude(float scalar)
        {
            Normalize();
            *this *= scalar;
        }

#pragma region operator=
        Vector2 &operator=(Vector2 &other)
        {
            this->x = other.x;
            this->y = other.y;

            return *this;
        }

        Vector2 &operator=(float (&other)[2])
        {
            this->x = other[0];
            this->y = other[1];

            return *this;
        }
#pragma endregion

#pragma region operator*
        Vector2 operator*(float scalar)
        {
            return {this->x * scalar, this->y * scalar};
        }

        friend Vector2 operator*(float &scalar, Vector2 &vec)
        {
            return {vec.x * scalar, vec.y * scalar};
        }

        Vector2 &operator*=(float scalar)
        {
            this->x *= scalar;
            this->y *= scalar;

            return *this;
        }
#pragma endregion

#pragma region operator/
        Vector2 operator/(float scalar)
        {
            return {this->x / scalar, this->y / scalar};
        }

        friend Vector2 operator/(float scalar, Vector2 vec)
        {
            return {vec.x / scalar, vec.y / scalar};
        }

        Vector2 &operator/=(float scalar)
        {
            this->x /= scalar;
            this->y /= scalar;

            return *this;
        }
#pragma endregion

#pragma region operator+
        Vector2 operator+(float other[2])
        {
            return {this->x + other[0], this->y + other[1]};
        }

        Vector2 operator+(Vector2 other)
        {
            return {this->x + other.x, this->y + other.y};
        }

        Vector2 &operator+=(Vector2 other)
        {
            this->x += other.x;
            this->y += other.y;

            return *this;
        }

        Vector2 &operator+=(float other[2])
        {
            this->x += other[0];
            this->y += other[1];

            return *this;
        }
#pragma endregion

#pragma region operator-
        Vector2 operator-(float other[2])
        {
            return {this->x - other[0], this->y - other[1]};
        }

        Vector2 operator-(Vector2 other)
        {
            return {this->x - other.x, this->y - other.y};
        }

        Vector2 &operator-=(Vector2 other)
        {
            this->x -= other.x;
            this->y -= other.y;

            return *this;
        }

        Vector2 &operator-=(float other[2])
        {
            this->x -= other[0];
            this->y -= other[1];

            return *this;
        }
#pragma endregion
    };

    float Dot(gwe::Vector2 vecA, gwe::Vector2 vecB)
    {
        return sqrt(vecA.x * vecB.x + vecA.y * vecB.y);
    }
    float Angle(gwe::Vector2 vecA, gwe::Vector2 vecB)
    {
        return acos(Dot(vecA, vecB) / (vecA.Magnitude() * vecB.Magnitude()));
    }
}