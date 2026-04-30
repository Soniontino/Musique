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

void Musique::start()
{
    audio.init();
    font = LoadFontEx(FONT_UI, FONT_UI_SIZE*10, nullptr, 0);
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
    Vec2 win_delta = {rt::win_w/rt::prev_win_w, rt::win_h/rt::prev_win_h};

    f32 progress = {
        (duration.max > 0.0)? f32(duration.now/duration.max) : 0.f
    };

    struct ProgressBar {
        f32 x, y, w, h;
        ProgressBar(f32 x, f32 y, f32 w, f32 h)
        : x(x), y(y), w(w), h(h) {}

        void draw(Color c, f32 fill=1.f) {
            DrawRectangleRounded(
                {x, y, w*fill, h},
                w*0.00075f, 20, c
            );
        }
    };

    struct Label {
        Vec2 pos; f32 fsize=FONT_UI_SIZE; const char* txt;

        void render(Color color) {
            renderText(txt, {pos.x, pos.y}, color, fsize);
        }
    };


    // LAYOUT

    Vec2 pb_size = {.x= rt::win_w*0.56f, .y= rt::win_w*0.018f};
    Vec2 pb_pos = WinCenter(pb_size.x, pb_size.y);
    pb_pos.y *= 1.625f;

    ProgressBar pb(pb_pos.x, pb_pos.y, pb_size.x*win_delta.x, pb_size.y*win_delta.y*0.8);
    pb.draw(DARKGRAY);
    pb.draw(BLUE, progress);


    Label lplaystat;
    lplaystat.txt = playing.now ? "PLAYING":"PAUSED";
    lplaystat.pos = {
        pb_pos.x + pb_size.x/2 - MeasureText(lplaystat.txt, 20)/2,
        pb_pos.y * 0.95f
    };

    Label lduration;
    lduration.txt = TextFormat("%.1f / %.1f", duration.now, duration.max);
    lduration.pos = {
        pb_pos.x + pb_size.x + 15,
        pb_pos.y
    };

    Label lvolume;
    lvolume.txt  = TextFormat("Vol: %.0f%% %s", volume, muted ? "(MUTED)":"");
    lvolume.pos  = {
        pb_pos.x - MeasureText(lvolume.txt, 20) - 15,
        pb_pos.y
    };


    // RENDER LABELS
    lplaystat.render(playing.now ? GREEN:YELLOW);
    lduration.render(WHITE);
    lvolume.render(WHITE);
}

void Musique::quit()
{
    UnloadFont(font);
    audio.destroy();
}
