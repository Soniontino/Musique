#include "musique.hpp"

int main(int argc, char* argv[])
{
    Musique musique = Musique();

    switch (argc)
    {
        CASE (4,
            if (EQS(argv[1], "--window-size")) {
                config::win_width_ini = std::stoi(argv[2]);
                config::win_height_ini = std::stoi(argv[3]);
            }
        )

        default: {
            ;
        }
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(config::win_width_ini, config::win_height_ini, "Musique");
    // SetExitKey(0); unset exit key from esc
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));

    musique.start();
    while (!WindowShouldClose()) {
        rt::dt = GetFrameTime();
        rt::win_w = GetScreenWidth();
        rt::win_h = GetScreenHeight();

        if (IsKeyTriggered(KEY_SLASH)) {
            Mprint(
                "fps: ", 1.0f/rt::dt, "\n",
                "mouse: ", GetMouseX(), " : ", GetMouseY(), "\n",
                "dur: ", musique.duration.now, "\n",
            "\n");
        }

        musique.input();
        musique.update();
        BeginDrawing();
        ClearBackground(BLACK);
        musique.render();
        EndDrawing();

        rt::prev_win_w = rt::win_w;
        rt::prev_win_h = rt::win_h;
    }

    musique.quit();
    CloseWindow();
}
