#include "utils.h"

bool KeyHadPressing(int key)
{
    return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}
