#pragma once

#include <ctime>
#include <cstdlib>

#include "Objects.h"
#include "Static.h"

bool collide(Rect a, Rect b);

struct Room
{
    virtual void Setup() {}
    virtual void Step() {}
};

struct RoomManager
{
    Room *current = nullptr;

    template <typename T>
    void SwitchTo()
    {
        static T roomInstance;
        roomInstance.Setup();
        current = &roomInstance;
    }

    void Update()
    {
        if (current)
            current->Step();
    }
};

struct Room1;

struct Room2 : public Room
{
    void Setup() override {}
    void Step() override
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
};

struct Room1 : public Room
{
    int player_score;
    int other_score;
    Rect player;
    Rect other;
    Rect ball;
    gwe::Vector2 ballSpeed;
    gwe::Vector2 ballDir;
    const Color backgroundColor = {20, 160, 133, 255};

    const unsigned max = 9;
    static const int screenWidth = 900;
    static constexpr int screenHeight = 600;

    Room1() : player(gwe::Vector2{0, 0}, 0, 0), other(gwe::Vector2{0, 0}, 0, 0), ball(gwe::Vector2{0, 0}, 0, 0) {}

    void Setup() override
    {
        SetRandomSeed(time(0));
        player_score = 0;
        other_score = 0;

        player = Rect(gwe::Vector2{-400, 0}, 20, 80);
        other = Rect(gwe::Vector2{400, 0}, 20, 80);
        ball = Rect(gwe::Vector2{0, 0}, 20, 20);

        ballSpeed = {-4.0, (float)GetRandomValue(-4, 4)};

        ballDir = {ballSpeed.x, ballSpeed.y};
    }

    void Step() override
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        gwe::Vector2 botdir = {0, (ball.position.y - other.position.y)};
        gwe::LimitMagnitude(botdir, 4);
        Rect nextPos = player;
        nextPos.position = {-400.0, (float)GetMouseY() - (float)screenHeight * 0.5f};
        if (nextPos.position.y > screenHeight * 0.5)
        {
            nextPos.position = {-400, screenHeight * 0.5};
        }
        else if (nextPos.position.y < -screenHeight * 0.5)
        {
            nextPos.position = {-400, -screenHeight * 0.5};
        }

        Rect nextBotPos = other;
        nextBotPos.position += botdir;
        Rect nextBallPos = ball;
        if (collide(player, nextBallPos))
        {
            ballSpeed.SetMagnitude(ballSpeed.Magnitude() + 0.3);
            if (ballSpeed.Magnitude() > max)
            {
                ballSpeed.SetMagnitude(max);
            }
            ballDir = (ball.position - player.position).GetUnitVector();
            ballDir.SetMagnitude(ballSpeed.Magnitude());
        }
        else if (collide(other, nextBallPos))
        {
            ballSpeed.SetMagnitude(ballSpeed.Magnitude() + 0.5);
            if (ballSpeed.Magnitude() > max)
            {
                ballSpeed.SetMagnitude(max);
            }
            ballDir = (ball.position - other.position).GetUnitVector();
            ballDir.SetMagnitude(ballSpeed.Magnitude());
        }

        if (abs(ball.position.y) > abs(float(screenHeight * 0.5)))
        {
            ballDir.y = -ballDir.y;
        }
        if (abs(ball.position.x) > abs(float(screenWidth * 0.5)))
        {
            if (ball.position.x >= screenWidth * 0.5)
                player_score++;
            else
                other_score++;

            ball.position = {0, 0};
            ballSpeed = {-3.0, (float)GetRandomValue(-3, 3)};
            ballDir = ballSpeed;
        }

        nextBallPos.position += ballDir;

        player.position = nextPos.position;
        other.position = nextBotPos.position;
        ball.position = nextBallPos.position;

        ball.Draw();

        other.Draw();
        player.Draw();

        DrawText(TextFormat("%d : %d\n", player_score, other_score), 450, 10, 21, BLACK);

        EndDrawing();

        if (IsKeyDown(KEY_A))
        {
            global::manager.SwitchTo<Room2>();
        }
    }
};
