#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include "musique.h"

Music music;
bool paused = false;
bool muted = false;
f32 volume = 1.0f;

void Musique::start()
{
    system("clear");
    InitAudioDevice();

    music = LoadMusicStream(RESOURCES_D "/song.mp3");

    if (music.frameCount == 0) {
        printf("Failed to load music file!\n");
        exit(1);
    }

    PlayMusicStream(music);
}

void Musique::input()
{
    
}

void Musique::update()
{
    UpdateMusicStream(music);

    if (volume > 1.0f) volume = 1.0f;
    if (volume < 0.0f) volume = 0.0f;

    SetMusicVolume(music, 10);
}

void Musique::render()
{
    float played = GetMusicTimePlayed(music);
    float total  = GetMusicTimeLength(music);
    float progress = (total > 0) ? (played / total) : 0;

    DrawText("RUST AINT CONTROLLING SHI", 20, 20, 20, RAYWHITE);

    // ben yapiyom bunu amk degistirme. guzel gozukuyo hep sunu kullaniyom
    DrawRectangleRounded({20, 60, 300, 20}, 0.75, 20, DARKGRAY);
    DrawRectangleRounded({20, 60, (300*progress), 20}, 0.75, 20, GREEN);

    DrawText(TextFormat("%.1f / %.1f", played, total), 20, 90, 20, RAYWHITE);
    DrawText(TextFormat("Vol: %.0f%% %s", volume * 100, muted ? "(MUTED)" : ""), 20, 120, 20, RAYWHITE);

    if (paused) DrawText("PAUSED", 20, 150, 20, YELLOW);
    else DrawText("PLAYING", 20, 150, 20, GREEN);
}

void Musique::quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}
