#include <stdio.h>
#include <string.h>
#include <argp.h>
#include "raylib.h"
#include "logo.h"

#define ACCEL 1
#define DECEL 0.01
#define LIMIT 100


#ifndef VERSION
#define VERSION "DEV"
#endif


int main(int argc, char** argv) {
    char version_text[255];
    snprintf(version_text, 255, "Woo v%s", VERSION);
    printf("uwu world\n");


    Vector2 window_size = {800, 600};
    Vector2 size = {100, 60};
    Vector2 pos = {0};
    Vector2 spd = {1};
    float logo_tint = 0;

    InitWindow(window_size.x, window_size.y, version_text);
    SetTargetFPS(60);

    SetWindowMinSize(size.x, size.y);

    SetWindowState(
        FLAG_VSYNC_HINT |
        FLAG_WINDOW_RESIZABLE
    );

    // Image logo = LoadImage("pngegg.png");

    Image logo = LoadImageFromMemory(".png", FILE_LOGO, FILE_LOGO_size);  
    ImageResize(&logo, 100, 60);

    Texture2D logo_tx = LoadTextureFromImage(logo);
    UnloadImage(logo);

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(BLACK);

            window_size.x = GetScreenWidth();
            window_size.y = GetScreenHeight();

            if (pos.x <= 0) {
                float res = (0 - pos.x);
                printf("dx = %f\n", res);
                spd.x += res;
                // spd.x += ACCEL; //+ (-pos.x) / 50;
            } else
            if ((pos.x + size.x) >= window_size.x) {
                spd.x -= ((pos.x + size.x) - window_size.x);
                // spd.x -= ACCEL; //+ pos.x / 50;
            }
            if (pos.y <= 0) {
                float res = (0 - pos.y);
                printf("dy = %f\n", res);
                spd.y += res;
                // spd.y += ACCEL;// + (-spd.y) / 50;
            } else
            if ((pos.y + size.y) >= window_size.y) {
                spd.y -= ((pos.y + size.y) - window_size.y);
                // spd.y -= ACCEL; // + spd.y / 50;
            }
            

            //? Deceleration
            if (spd.x > ACCEL) spd.x -= DECEL + spd.x / 100;
            if (spd.x < -ACCEL) spd.x += DECEL - spd.x / 100;
            if (spd.y > ACCEL) spd.y -= DECEL + spd.y / 100;
            if (spd.y < -ACCEL) spd.y += DECEL - spd.y / 100;

            //? MAX speed
            if (spd.x > LIMIT) spd.x = LIMIT;
            if (spd.x < -LIMIT) spd.x = -LIMIT;
            if (spd.y > LIMIT) spd.y = LIMIT;
            if (spd.y < -LIMIT) spd.y = -LIMIT;

            //? MIN speed
            if (spd.x < ACCEL && spd.x >= 0) spd.x += ACCEL;
            if (spd.x > -ACCEL && spd.x < 0) spd.x += -ACCEL;
            if (spd.y < ACCEL && spd.y >= 0) spd.y += ACCEL;
            if (spd.y > -ACCEL && spd.y < 0) spd.y += -ACCEL;


            pos.x += spd.x;
            pos.y += spd.y;

            if (argc > 1 && *argv[1] == 'v')
                printf("spd = (%f, %f) pos = (%f, %f)\n", spd.x, spd.y, pos.x, pos.y);

            logo_tint += 1;
            if (logo_tint > 360.0) logo_tint = 0.0;

            DrawTextureV(logo_tx, pos, ColorFromHSV(logo_tint, 100, 100));
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}