#pragma once
#include "core.h"


template <class... T>
inline void Mprint(T... stream)
{
    (std::cerr << ... << stream) << std::flush;
}

inline bool PerNFrame(f64 n)
{
    return fmod(GetTime(), n) < GetFrameTime();
}

inline bool IsKeyTriggered(int key)
{
    return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}

inline bool IsMouseDoubleClicked(MouseButton button=MOUSE_BUTTON_LEFT, f32 interval_ms=400)
{
    static f64 lastClick = 0.0;

    if (!IsMouseButtonPressed(button)) return false;

    f64 now  = GetTime();
    bool hit = (now - lastClick) < interval_ms*0.1;
    lastClick = hit ? -1.0 : now;
    return hit;
}

inline Vec2 WinCenter(f32 width, f32 height)
{
    return {
        GetScreenWidth()/2.0f - width/2.0f,
        GetScreenHeight()/2.0f + height/2.0f
    };
}
