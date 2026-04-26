#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <cstring>
// external
#include <raylib.h>

#define RESOURCES_D "resources"

#define CASE(_val, _stmt) \
    case _val: {_stmt}; break;

// equal-string check
#define EQS(_s1, _s2) \
    !strcmp(_s1, _s2)

using f32 = float;
