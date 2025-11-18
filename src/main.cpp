#include <raylib.h>
#include "Objects.h"

Vector2 vecAdd(Vector2 a, Vector2 b)
{
    a.x += b.x;
    a.y += b.y;

    return a;
}

int main()
{
    const Color darkGreen = {20, 160, 133, 255};

    constexpr int screenWidth = 900;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    Vector2 p = {450, 300};
    Rect rect(p, 30, 30);
    float speed = 2;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        Vector2 dir = {(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * speed, (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * speed};

        rect.SetPosition(vecAdd(rect.GetPosition(), dir));

        rect.Draw();

        EndDrawing();
    }

    CloseWindow();
}