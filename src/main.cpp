#include <raylib.h>
#include <iostream>
#include "Objects.h"

static constexpr int screenWidth = 900;
static constexpr int screenHeight = 600;

int main()
{
    const Color darkGreen = {20, 160, 133, 255};

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    Rect rect(gwe::Vector2{0, 0}, 30, 30);
    float speed = 300;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        gwe::Vector2 dir = {(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * speed * GetFrameTime(), (IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * speed * GetFrameTime()};

        rect.position += dir;

        rect.Draw();
        DrawText(TextFormat("%.1f, %.1f", rect.position.x, rect.position.y), 10, 10, 22, BLACK);

        EndDrawing();
    }

    CloseWindow();
}