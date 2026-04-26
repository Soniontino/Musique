#pragma once
#include "utils.h"

namespace config {
    inline f32 win_width_ini = 1280;
    inline f32 win_height_ini = 720;
};

// get volume based on the mute state
f32 getVol();
// set volume to new value
void setVol(f32);

void start();
void input();
void update();
void render();
void quit();
