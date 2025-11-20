#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Objects.h"
#include "Rooms.h"

bool collide(Rect a, Rect b)
{
    gwe::Rectangle aHitbox = a.Hitbox();

    gwe::Rectangle bHitbox = b.Hitbox();

    bool collideX = (aHitbox.left() <= bHitbox.right()) && (aHitbox.right() >= bHitbox.left());
    bool collideY = (aHitbox.top() <= bHitbox.bottom()) && (aHitbox.bottom() >= bHitbox.top());

    return collideX && collideY;
}

int main()
{
    InitWindow(900, 600, "Pong");
    SetTargetFPS(60);

    global::manager.SwitchTo<Room1>();
    while (!WindowShouldClose())
    {
        global::manager.Update();
    }

    CloseWindow();
}