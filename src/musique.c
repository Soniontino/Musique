#include "musique.h"

Music music;
bool paused = false;
const float default_volume = 1.0f;
float volume = default_volume;


void start()
{
    SetTargetFPS(60);
    InitAudioDevice();
    music = LoadMusicStream("song.mp3");
    SetMusicVolume(music, volume);
    PlayMusicStream(music);
}

void input()
{
    if (IsKeyPressed(KEY_L)) {
        printf(
            "Time passed: %f\nVolume: %f\n\n",
            GetMusicTimePlayed(music), volume
        );
    }

    if (IsKeyPressed(KEY_SPACE)) {
        if (paused) ResumeMusicStream(music);
        else PauseMusicStream(music);
        paused = !paused;
    }

    if (IsKeyDown(KEY_UP)) volume += 0.01f;
    if (IsKeyDown(KEY_DOWN)) volume -= 0.01f;

    if (IsKeyPressed(KEY_RIGHT)) {
        f32 amount = GetMusicTimePlayed(music) + 5;
        float total = GetMusicTimeLength(music);
        amount = fmin(amount, total);
        SeekMusicStream(music, amount);
    }
    if (IsKeyPressed(KEY_LEFT)) {
        f32 amount = GetMusicTimePlayed(music) - 5;
        amount = fmax(amount, 0.0f);
        SeekMusicStream(music, amount);
    }
}

void update()
{
    UpdateMusicStream(music);

    volume = fmax(0.0f, volume);
    volume = fmin(1.0f, volume);

    SetMusicVolume(music, volume);
}

void render()
{
    float played = GetMusicTimePlayed(music);
    float total  = GetMusicTimeLength(music);
    float progress = (total > 0) ? played / total : 0;

    DrawText("SPACE = Play/Pause", 20, 20, 20, RAYWHITE);
    DrawText("UP/DOWN = Volume", 20, 50, 20, RAYWHITE);
    DrawText("LEFT/RIGHT = Seek", 20, 80, 20, RAYWHITE);

    int barX = 20, barY = 120, barW = 600;
    DrawRectangle(barX, barY, barW, 20, DARKGRAY);
    DrawRectangle(barX, barY, (int)(barW * progress), 20, GREEN);

    DrawText(TextFormat("%.1f / %.1f sec", played, total), 20, 150, 20, RAYWHITE);

    DrawText(TextFormat("Volume: %.0f%%", volume * 100), 20, 180, 20, RAYWHITE);

    DrawText(paused ? "PAUSED" : "PLAYING", 20, 210, 20, YELLOW);
}

void quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}
