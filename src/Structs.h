#pragma once

#include <cmath>
#include "Objects.h"

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

        float Magnitude() { return sqrt(Dot(*this, *this)); }

        gwe::Vector2 GetUnitVector() { return *this / Magnitude(); }

        void Normalize() { *this /= Magnitude(); }

        void SetMagnitude(float scalar)
        {
            Normalize();
            *this *= scalar;
        }

#pragma region operator=
        Vector2 &operator=(Vector2 other)
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

    inline float Dot(gwe::Vector2 vecA, gwe::Vector2 vecB)
    {
        return vecA.x * vecB.x + vecA.y * vecB.y;
    }
    inline float Angle(gwe::Vector2 vecA, gwe::Vector2 vecB)
    {
        return acos(Dot(vecA, vecB) / (vecA.Magnitude() * vecB.Magnitude()));
    }
    inline void LimitMagnitude(Vector2 &vec, float max, float min = 0)
    {
        if (vec.Magnitude() > max)
            vec.SetMagnitude(max);
        else if (vec.Magnitude() < min)
            vec.SetMagnitude(min);
    }

    struct Rectangle
    {
        float x, y;
        float width, height;

        Rectangle() = default;
        Rectangle(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height) {}

        float left() { return x; }
        float right() { return x + width; }
        float top() { return y; }
        float bottom() { return y + height; }
    };

    inline int sign(float num) { return ((num > 1) - (num < 1)); }
    inline float abs(float num) { return num * sign(num); }
}