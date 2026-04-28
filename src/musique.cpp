#include "musique.hpp"

Musique::Musique()
{
    ;
}

void Musique::loadFile(const strview& path, bool play)
{
    auto build_str = std::format("{}/{}", RESOURCES_D, path);
    audio.load(build_str.data());
    audio.setPlaying(play);
}

void Musique::start()
{
    audio.init();

    try { loadFile("song.mp3"); }
    catch (std::exception&) { audio.destroy(); throw; }
}

void Musique::input()
{
    const auto& mouseX = GetMouseX();
    const auto mouseY = GetMouseY();

    if (IsKeyTriggered(KEY_SPACE)
        || (IsMouseButtonPressed(0) && (mouseX<(rt::win_w*0.75) && mouseX>(rt::win_w*0.25)))
    ){
        playing.now = !playing.now;
    }

    else if (IsKeyTriggered(KEY_M)) {
        muted = !muted;
    }

    else if (IsKeyTriggered(KEY_LEFT) || (IsMouseDoubleClicked() && mouseX<rt::win_w*0.75)) {
        audio.seek(-5);
    }
    else if (IsKeyTriggered(KEY_RIGHT) || (IsMouseDoubleClicked() && mouseX>rt::win_w*0.25)) {
        audio.seek(+5);
    }

    else if (IsKeyTriggered(KEY_DOWN)) {
        volume += -2;
    }
    else if (IsKeyTriggered(KEY_UP)) {
        volume += +2;
    }
}

void Musique::update()
{
    duration.max = audio.getDuration();
    duration.now = std::clamp(audio.getTimePoint(), 0.0, duration.max);

    volume = std::clamp(volume, 0.0, 100.0);
    audio.setVolume(muted? 0.0:volume);

    if (playing.now != playing.prev) {
        audio.setPlaying(playing.now);
        playing.prev = playing.now;
    }

    if (duration.now>duration.max*0.9 && audio.isEnded()) {
        playing.now = false;
        playing.prev = false;
        duration.now = 0;
    }
}

void Musique::render()
{
    f64 progress = (duration.max > 0) ? (duration.now / duration.max) : 0;

    // ben yapiyom bunu amk degistirme guzel gozukuyo hep sunu kullaniyom
    DrawRectangleRounded({20, 60, 300, 20}, 0.75, 20, DARKGRAY);
    DrawRectangleRounded({20, 60, (300*(f32)progress), 20}, 0.75, 20, GREEN);

    DrawText("RUST AINT CONTROLLING SHI", 20, 20, 20, RAYWHITE);
    DrawText(TextFormat("%.1f / %.1f", duration.now, duration.max), 20, 90, 20, RAYWHITE);
    DrawText(TextFormat("Vol: %.0f%% %s", volume, muted ? "(MUTED)" : ""), 20, 120, 20, RAYWHITE);

    if (playing.now) DrawText("PLAYING", 20, 150, 20, YELLOW);
    else DrawText("PAUSED", 20, 150, 20, GREEN);
}

void Musique::quit()
{
    audio.destroy();
}
