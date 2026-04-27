#pragma once
#include "core.h"

inline bool PerNFrame(f64 n)
{
    return fmod(GetTime(), n) < GetFrameTime();
}

inline bool IsKeyTriggered(int key)
{
    return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}

template <class... T>
inline void Mprint(T... stream)
{
    (std::cerr << ... << stream) << std::flush;
}
