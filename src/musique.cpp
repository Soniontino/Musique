#include "musique.hpp"

Musique::Musique()
{
    ;
}

void Musique::loadAudio(const strview& path, bool play)
{
    auto build_str = std::format("{}/{}", RESOURCES_D, path);
    audio.load(build_str.data());
    audio.setPlaying(play);
}

void Musique::renderText(const char* text, Vec2 pos, Color color, f32 size)
{
    DrawTextEx(font, text, pos, size, 0.1, color);
}


void Musique::start()
{
    audio.init();
    font = LoadFontEx(FONT_UI, 145, nullptr, 0);
    if (font.baseSize == 0) {
        Mprint("Musique: Font could not loaded!\n");
        CloseWindow(); exit(1);
    }

    try { loadAudio("audio/song.mp3"); }
    catch (std::exception&) { audio.destroy(); throw; }
}

void Musique::input()
{
    const auto& mouseX = GetMouseX();
    // const auto mouseY = GetMouseY();

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
    f32 progress = (duration.max > 0.0) ? (duration.now / duration.max) : 0.f;

    struct ProgressBar {
        f32 x, y, w, h;
        ProgressBar(f32 x, f32 y, f32 w, f32 h)
        : x(x), y(y), w(w), h(h)
        {}
        void draw(Color c, f32 fill=1.f) {
            DrawRectangleRounded({x, y, w*fill, h}, 0.4f, 20, c);
        }
    };

    const Vec2 size = {840, 25};
    const Vec2 pos  = WinCenter(size.x, size.y);
    ProgressBar pb(pos.x, pos.y*1.625f, size.x, size.y);
    // background
    pb.draw(DARKGRAY);
    // progress
    pb.draw(BLUE, progress);


    renderText(TextFormat("%.1f / %.1f", duration.now, duration.max), {20, 90}, RAYWHITE);
    renderText(TextFormat("Vol: %.0f%% %s", volume, muted ? "(MUTED)":""), {20, 120}, RAYWHITE);

    struct Display { Vec2 pos; f32 size; const char* txt; } display;
    display.size = 20;
    display.txt  = playing.now ? "PLAYING" : "PAUSED";
    display.pos  = WinCenter(MeasureText(display.txt, display.size), display.size);

    renderText(display.txt, {display.pos.x, display.pos.y*1.525f}, (playing.now)?GREEN:YELLOW);
}

void Musique::quit()
{
    UnloadFont(font);
    audio.destroy();
}
