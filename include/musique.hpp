#pragma once
#include "maudio.hpp"

namespace config {
    inline f32 win_width_ini = 1280;
    inline f32 win_height_ini = 720;
}
namespace rt {  // rt = runtime
    inline f32 dt = 0;
    inline f32 win_w = config::win_width_ini;
    inline f32 win_h = config::win_height_ini;
}

struct Musique
{
    strview path;
    struct{bool prev,now;} playing = {true, true};
    bool muted = false;
    f64 volume = 100.0f;
    struct{f64 max,now;} duration = {0, 0};

    Maudio audio;

    Musique ();
    // load music file
    void loadFile(const strview& path, bool play=true);
    void start();
    void input();
    void update();
    void render();
    void quit();
};
