#include "raylib.h"

Music music;
bool paused = false;

void start()
{
    printf("START\n");
}

void update()
{
    UpdateMusicStream(music);

    if (IsKeyPressed(KEY_SPACE)) {
        if (paused) ResumeMusicStream(music);
        else PauseMusicStream(music);
        paused = !paused;
    }
}

void render()
{
    DrawText("SPACE = Play/Pause", 20, 20, 20, RAYWHITE);
}

int main()
{
    InitWindow(1280, 720, "Music Player");
    InitAudioDevice();

    music = LoadMusicStream("song.mp3");
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        render();
        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}
