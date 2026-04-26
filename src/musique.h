#pragma once
#include "utils.h"

namespace config {
    inline f32 win_width_ini = 1280;
    inline f32 win_height_ini = 720;
};

struct Musique
{
    void start();
    void input();
    void update();
    void render();
    void quit();
};
