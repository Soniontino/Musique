#include "utils.h"

bool IsKeyTriggered(int key)
{
    return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}
