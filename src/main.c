#include "musique.h"

int main()
{
    SetConfigFlags(
        FLAG_WINDOW_RESIZABLE
    );
    InitWindow(1280, 720, "Music Player");

    start();
    while (!WindowShouldClose()) {
        input();
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        render();
        EndDrawing();
    }

    quit();
    CloseWindow();
}
