#include "utils.hpp"

bool IsKeyTriggered(int key)
{
    return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}
