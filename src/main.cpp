#include "musique.h"

int main(int argc, char* argv[])
{
    switch (argc)
    {
        CASE (1,
            ;
        );
        CASE (2,
            if (EQS(argv[1], "--window-size")) {
                config::win_width_ini = std::stoi(argv[2]);
                config::win_height_ini = std::stoi(argv[3]);
            }
        )
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::win_width_ini, config::win_height_ini, "Musique");
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