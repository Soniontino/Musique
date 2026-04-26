#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "musique.h"

Music music;
bool paused = false;
bool muted = false;
f32 volume = 1.0f;

// Helper to get volume based on the mute state
float getAbsVol() {
    return muted ? 0.0f : volume;
}

void start()
{
    system("clear");
    SetTargetFPS(60);
    InitAudioDevice();

    music = LoadMusicStream(RESOURCES_D "/song.mp3");

    if (music.stream.buffer == NULL) {
        printf("Failed to load music file!\n");
    }

    PlayMusicStream(music);
}

void input()
{
    // Log info
    if (IsKeyPressed(KEY_L)) {
        printf("Time passed: %f\nVolume: %f\n\n", GetMusicTimePlayed(music), volume);
    }

    // Play/Pause toggle
    if (IsKeyTriggered(KEY_SPACE)) {
        paused = !paused;
        if (paused) PauseMusicStream(music);
        else ResumeMusicStream(music);
    }

    // Mute toggle
    if (IsKeyTriggered(KEY_M)) {
        muted = !muted;
    }

    // Volume Control
    if (IsKeyTriggered(KEY_UP)) {
        volume += 0.02f;
    }
    if (IsKeyTriggered(KEY_DOWN)) {
        volume -= 0.02f;
    }

    // Seek Controls
    if (IsKeyTriggered(KEY_LEFT)) {
        float amount = GetMusicTimePlayed(music) - 5.0f;
        SeekMusicStream(music, fmaxf(amount, 0.0f));
    }
    if (IsKeyTriggered(KEY_RIGHT)) {
        float amount = GetMusicTimePlayed(music) + 5.0f;
        float total = GetMusicTimeLength(music);
        SeekMusicStream(music, fminf(amount, total));
    }
}

void update()
{
    UpdateMusicStream(music);

    // Clamp volume between 0 and 1
    if (volume > 1.0f) volume = 1.0f;
    if (volume < 0.0f) volume = 0.0f;

    // Apply volume (considering mute state)
    SetMusicVolume(music, getAbsVol());
}

void render()
{
    float played = GetMusicTimePlayed(music);
    float total  = GetMusicTimeLength(music);
    float progress = (total > 0) ? (played / total) : 0;

    DrawText("SPACE = Play/Pause | M = Mute", 20, 20, 20, RAYWHITE);
    DrawText("UP/DOWN = Volume", 20, 50, 20, RAYWHITE);
    DrawText("LEFT/RIGHT = Seek", 20, 80, 20, RAYWHITE);

    // Audio duration bar
    float barX = 20, barY = 120, barW = 600, barH = 20;
    
    // Background bar
    DrawRectangleRounded((Rectangle){barX, barY, barW, barH}, 0.5f, 10, DARKGRAY);
    // Progress bar
    DrawRectangleRounded((Rectangle){barX, barY, barW * progress, barH}, 0.5f, 10, GREEN);

    DrawText(TextFormat("%.1f / %.1f sec", played, total), 20, 150, 20, RAYWHITE);
    DrawText(TextFormat("Volume: %.0f%% %s", volume * 100, muted ? "(MUTED)" : ""), 20, 180, 20, RAYWHITE);

    if (paused) DrawText("PAUSED", 20, 210, 20, YELLOW);
    else DrawText("PLAYING", 20, 210, 20, GREEN);
}

void quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}
