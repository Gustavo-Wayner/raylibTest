#include <raylib.h>

class GameObject
{
protected:
    Vector2 Position;
    Rectangle hitbox;
    Color color;

public:
    void Draw()
    {
        DrawRectangle(hitbox.x, hitbox.y, hitbox.width, hitbox.height, color);
    }
};

class Rect : public GameObject
{
public:
    double Width, Height;

    Rect(Vector2 _Position, double _Width, double _Height, Color _color = {255, 255, 255, 255}) : Width(_Width), Height(_Height)
    {
        color = _color;
        Position.x = _Position.x;
        Position.y = _Position.y;

        hitbox.x = Position.x;
        hitbox.y = Position.y;
        hitbox.height = Height;
        hitbox.width = Width;
    }

    Vector2 GetPosition() { return Position; }
    void SetPosition(Vector2 vec)
    {
        Position = vec;
        hitbox.x = Position.x;
        hitbox.y = Position.y;
    }
    void SetPosition(double x, double y)
    {
        Position.x = x;
        Position.y = y;
        hitbox.x = x;
        hitbox.y = y;
    }
};