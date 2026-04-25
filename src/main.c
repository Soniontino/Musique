// musiqe application entry point
#include "musique.h"

int main(void)
{
    InitWindow(660, 260, "Musique");
    SetTargetFPS(60);

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
    return 0;
}

