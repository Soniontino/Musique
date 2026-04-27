#include "musique.hpp"

void Musique::loadFile(const strview& path, bool play)
{
    auto build_str = string(RESOURCES_D) + string(path.data());
    music = LoadMusicStream(build_str.data());
    if (music.stream.buffer == nullptr) {
        throw std::runtime_error("Failed to load music file!");
    }
    duration.now = 0;
    duration.max = GetMusicTimeLength(music);

    if (play) PlayMusicStream(music);
}

f32 Musique::AbsVol()
{
    return (muted)? (0.0f):(volume);
}

void Musique::seek(f32 seconds)
{
    duration.now = std::clamp(duration.now + seconds, 0.0f, duration.max);
    SeekMusicStream(music, duration.now);
}


void Musique::start()
{
    system("clear");
    InitAudioDevice();

    try {loadFile("song.mp3");} catch(std::exception&){CloseAudioDevice(); throw;}
}

void Musique::input()
{
    if (IsKeyTriggered(KEY_SPACE)) {
        playing = !playing;
    }
    else if (IsKeyTriggered(KEY_M)) {
        muted = !muted;
    }

    else if (IsKeyTriggered(KEY_LEFT)) {
        seek(-5);
    } else if (IsKeyTriggered(KEY_RIGHT)) {
        seek(+5);
    }

    else if (IsKeyTriggered(KEY_DOWN)) {
        volume += -0.02;
    } else if (IsKeyTriggered(KEY_UP)) {
        volume += +0.02;
    }
}

void Musique::update()
{
    UpdateMusicStream(music);
    volume = std::clamp(volume, 0.0f, 1.0f);

    if (playing && !IsMusicStreamPlaying(music)) {
        ResumeMusicStream(music);
    } else if (!playing && IsMusicStreamPlaying(music)) {
        PauseMusicStream(music);
    }

    duration.now = GetMusicTimePlayed(music);
    SetMusicVolume(music, AbsVol());
}

void Musique::render()
{
    float progress = (duration.max > 0) ? (duration.now / duration.max) : 0;

    // ben yapiyom bunu amk degistirme guzel gozukuyo hep sunu kullaniyom
    DrawRectangleRounded({20, 60, 300, 20}, 0.75, 20, DARKGRAY);
    DrawRectangleRounded({20, 60, (300*progress), 20}, 0.75, 20, GREEN);

    DrawText("RUST AINT CONTROLLING SHI", 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("%.1f / %.1f", duration.now, duration.max), 20, 90, 20, RAYWHITE);
    DrawText(TextFormat("Vol: %.0f%% %s", volume * 100, muted ? "(MUTED)" : ""), 20, 120, 20, RAYWHITE);

    if (playing) DrawText("PLAYING", 20, 150, 20, YELLOW);
    else DrawText("PAUSED", 20, 150, 20, GREEN);
}

void Musique::quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}
