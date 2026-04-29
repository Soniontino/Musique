#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
// #include <cstdint>
#include <cmath>
#include <algorithm>
#include <format>
// external
#include <raylib.h>

#define RESOURCES_D "resources/"
#define FONT_UI RESOURCES_D "fonts/InterVariable.ttf"

#define CASE(_val, _stmt) \
    case _val: {_stmt}; break;

// equal-string check
#define EQS(_s1, _s2) \
    !strcmp(_s1, _s2)

#define M_TRY(_stmt_expr, _else_exec) \
    if(!(_stmt_expr)) {_else_exec}

using f32 = float;
using f64 = double;
using strview = std::string_view;
using string = std::string;
using Vec2 = Vector2;
