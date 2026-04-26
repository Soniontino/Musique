#pragma once
#include "core.h"

bool IsKeyTriggered(int key);

// template fn-ler .hpp-de olmali bu arada
template <class... T>
void mprint(T... stream)
{
    (std::cerr << (..., stream) << std::flush);
}
