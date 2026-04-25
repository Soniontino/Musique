#include "core.h"

void update()
{
    
}

void render()
{
    
}

int main()
{
    InitWindow(1280, 720, "");

    printf("Hello!\n");
    while (!WindowShouldClose()) {
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        render();
        EndDrawing();
    }
    CloseWindow();
}
