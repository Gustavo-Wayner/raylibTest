#pragma once

#include <raylib.h>
#include "Structs.h"

class GameObject
{
protected:
    gwe::Vector2 Pos;
    Color color;
    gwe::Rectangle hitbox;

public:
    void Draw()
    {
        DrawRectangle(hitbox.x + GetScreenWidth() * 0.5, hitbox.y + GetScreenHeight() * 0.5, hitbox.width, hitbox.height, color);
    }

    gwe::Rectangle Hitbox()
    {
        return hitbox;
    }
};

class Rect : public GameObject
{
private:
    struct Position
    {
        Rect *parent;
        float x;
        float y;

        Position() = default;
        Position(Rect *r)
        {
            parent = r;
            x = parent->Pos.x;
            y = parent->Pos.y;
        }

        operator gwe::Vector2() const
        {
            return parent->Pos;
        }

        Position &operator=(gwe::Vector2 other)
        {
            parent->Pos = other;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }

        Position &operator*=(float &scalar)
        {
            parent->Pos *= scalar;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }
        Position &operator/=(float scalar)
        {
            parent->Pos /= scalar;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }
        Position &operator+=(gwe::Vector2 other)
        {
            parent->Pos += other;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }
        Position &operator-=(gwe::Vector2 other)
        {
            parent->Pos -= other;
            x = parent->Pos.x;
            y = parent->Pos.y;
            parent->UpdateHitbox();

            return *this;
        }

        gwe::Vector2 operator-(float other[2])
        {
            return {this->x - other[0], this->y - other[1]};
        }

        gwe::Vector2 operator-(gwe::Vector2 other)
        {
            return {this->x - other.x, this->y - other.y};
        }
    };

public:
    double Width, Height;
    Position position;

    Rect(gwe::Vector2 _position, double _Width, double _Height, Color _color = {255, 255, 255, 255}) : Width(_Width), Height(_Height)
    {
        color = _color;
        Pos = _position;
        position = Position(this);

        hitbox.x = position.x + Width * 0.5;
        hitbox.y = position.y + Height * 0.5;
        hitbox.height = Height;
        hitbox.width = Width;
    }

    void UpdateHitbox()
    {
        hitbox.x = position.x - Width * 0.5;
        hitbox.y = position.y - Height * 0.5;
    }

    Rect &operator=(const Rect &other)
    {
        Width = other.Width;
        Height = other.Height;
        color = other.color;
        Pos = other.Pos;
        hitbox = other.hitbox;
        position = Position(this);
        return *this;
    }
};