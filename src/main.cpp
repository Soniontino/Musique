#include "musique.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {
        
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1080, 640, "Musique");
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