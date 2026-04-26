#include <math.h>
#include <stdio.h>
#include <cstdlib>
// #include <cstring>
#include "musique.hpp"

void Musique::loadFile(const strview& path)
{
    auto build_str = string(RESOURCES_D) + string(path.data());
    music = LoadMusicStream(build_str.data());
}

f32 Musique::AbsVol()
{
    return (muted)? (0.0f):(volume);
}

void Musique::start()
{
    system("clear");
    InitAudioDevice();

    loadFile("song.mp3");

    if (music.frameCount == 0) {
        printf("Failed to load music file!\n");
        exit(1);
    }

    PlayMusicStream(music);
}

void Musique::input()
{
    if (IsKeyTriggered(KEY_SPACE)) {
        playing = !playing;
    }
    else if (IsKeyTriggered(KEY_M)) {
        muted = !muted;
    }
}

void Musique::update()
{
    UpdateMusicStream(music);

    volume = std::min(volume, 1.0f);
    volume = std::max(volume, 0.0f);

    SetMusicVolume(music, AbsVol());

    if (playing) {
        if (!IsMusicStreamPlaying(music)) {
            ResumeMusicStream(music);
        }
    } else {
        if (IsMusicStreamPlaying(music)) {
            PauseMusicStream(music);
        }
    }

    if (muted) {
        SetMusicVolume(music, AbsVol());
    }
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

    if (playing) DrawText("PLAYING", 20, 150, 20, YELLOW);
    else DrawText("PAUSED", 20, 150, 20, GREEN);
}

void Musique::quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}
