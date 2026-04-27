#pragma once
#include "utils.hpp"

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
    struct MusicDuration { f32 max=0, now=0; };

    strview path;
    Music music;
    bool playing = true;
    bool muted = false;
    f32 volume = 1.0f;
    MusicDuration duration = {};

    // load music file
    void loadFile(const strview& path, bool play=true);
    // get absolute volume
    f32 AbsVol();
    // seek audio
    void seek(f32 seconds);

    void start();
    void input();
    void update();
    void render();
    void quit();
};
