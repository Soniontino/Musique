#include "musique.hpp"

int main(int argc, char* argv[])
{
    Musique musique;

    switch (argc)
    {
        CASE (1,
            ;
        );
        CASE (4,
            if (EQS(argv[1], "--window-size")) {
                config::win_width_ini = std::stoi(argv[2]);
                config::win_height_ini = std::stoi(argv[3]);
            }
        )
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::win_width_ini, config::win_height_ini, "Musique");
    SetTargetFPS(60);

    musique.start();
    while (!WindowShouldClose()) {
        rt::dt = GetFrameTime();
        rt::win_h = GetScreenWidth();
        rt::win_h = GetScreenHeight();
        if (IsKeyTriggered(KEY_SLASH)) {
            Mprint(
                "fps: ", 1.0f/rt::dt, "\n",
                "dur: ", musique.duration.now, "\n"
            "\n");
        }

        musique.input();
        musique.update();
        BeginDrawing();
        ClearBackground(BLACK);
        musique.render();
        EndDrawing();
    }

    musique.quit();
    CloseWindow();
}