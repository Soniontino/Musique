#pragma once
#include "utils.h"

// get volume based on the mute state
f32 getVol();
// set volume to new value
void setVol(f32);

void start();
void input();
void update();
void render();
void quit();
