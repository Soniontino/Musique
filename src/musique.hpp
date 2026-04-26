#pragma once
#include "utils.hpp"

namespace config {
    inline f32 win_width_ini = 1280;
    inline f32 win_height_ini = 720;
};

struct Musique
{
    strview path;
    Music music;
    bool playing = true;
    bool muted = false;
    f32 volume = 1.0f;

    // load music file
    void loadFile(const strview& path);
    // get absolute volume
    f32 AbsVol();

    void start();
    void input();
    void update();
    void render();
    void quit();
};
