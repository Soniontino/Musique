#pragma once
#include "maudio.hpp"

namespace config {
    inline f32 win_width_ini = 1280;
    inline f32 win_height_ini = 720;
}
namespace rt {  // rt = runtime
    inline f32 dt = 0;
    inline f32 prev_win_w = config::win_width_ini;
    inline f32 prev_win_h = config::win_height_ini;
    inline f32 win_w = prev_win_w;
    inline f32 win_h = prev_win_h;
    inline enum Mode{NORM, DEV} MODE = NORM; // for debugging shi visually
}

struct Musique
{
    Maudio audio;

    strview path;
    struct{bool prev,now;} playing = {true, true};
    bool muted = false;
    f64 volume = 100.0f;
    struct{f64 max,now;} duration = {0, 0};

    static inline Font font;

    Musique ();
    // load music file
    void loadAudio(const strview& path, bool play=true);
    // void renderText(const char* text, Vec2 pos, Color color, f32 size=27.f);
    void start();
    void input();
    void update();
    void render();
    void quit();

    static inline void renderText(const char* text, Vec2 pos, Color color, f32 size)
    {
        DrawTextEx(font, text, pos, size, 0.1, color);
    }
};
