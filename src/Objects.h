#include <raylib.h>
#include "Structs.h"

class GameObject
{
protected:
    gwe::Vector2 Pos;
    Rectangle hitbox;
    Color color;

public:
    void Draw()
    {
        DrawRectangle(hitbox.x + GetScreenWidth() * 0.5, hitbox.y + GetScreenHeight() * 0.5, hitbox.width, hitbox.height, color);
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
    };
    double Width, Height;

public:
    Position position;

    Rect(gwe::Vector2 _position, double _Width, double _Height, Color _color = {255, 255, 255, 255}) : Width(_Width), Height(_Height)
    {
        color = _color;
        Pos = _position;
        position = Position(this);

        hitbox.x = position.x;
        hitbox.y = position.y;
        hitbox.height = Height;
        hitbox.width = Width;
    }

    void UpdateHitbox()
    {
        hitbox.x = position.x;
        hitbox.y = position.y;
    }
};