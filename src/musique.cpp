#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include "musique.h"

Music music;
bool paused = false;
bool muted = false;
f32 volume = 1.0f;

#define CMD_PIPE "/tmp/musique_cmd"

int cmd_fd = -1;
char cmd_buf[64];

float getAbsVol() {
    return muted ? 0.0f : volume;
}

void start()
{
    system("clear");

    InitWindow(800, 200, "musique");
    SetTargetFPS(60);
    InitAudioDevice();

    if (mkfifo(CMD_PIPE, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(1);
    }

    cmd_fd = open(CMD_PIPE, O_RDONLY | O_NONBLOCK);
    if (cmd_fd < 0) {
        perror("open fifo");
    }

    music = LoadMusicStream(RESOURCES_D "/song.mp3");

    if (music.frameCount == 0) {
        printf("Failed to load music file!\n");
        exit(1);
    }

    PlayMusicStream(music);
}

void handle_cmd(char *cmd)
{
    if (strncmp(cmd, "space", 5) == 0) {
        paused = !paused;
        if (paused) PauseMusicStream(music);
        else ResumeMusicStream(music);
    }
    else if (strncmp(cmd, "mute", 4) == 0) {
        muted = !muted;
    }
    else if (strncmp(cmd, "up", 2) == 0) {
        volume += 0.02f;
    }
    else if (strncmp(cmd, "down", 4) == 0) {
        volume -= 0.02f;
    }
    else if (strncmp(cmd, "left", 4) == 0) {
        float amount = GetMusicTimePlayed(music) - 5.0f;
        SeekMusicStream(music, fmaxf(amount, 0.0f));
    }
    else if (strncmp(cmd, "right", 5) == 0) {
        float amount = GetMusicTimePlayed(music) + 5.0f;
        float total = GetMusicTimeLength(music);
        SeekMusicStream(music, fminf(amount, total));
    }
}

void input()
{
    if (cmd_fd < 0) return;

    int n = read(cmd_fd, cmd_buf, sizeof(cmd_buf) - 1);

    if (n > 0) {
        cmd_buf[n] = '\0';
        handle_cmd(cmd_buf);
    }
    else if (n == 0) {
        close(cmd_fd);
        cmd_fd = open(CMD_PIPE, O_RDONLY | O_NONBLOCK);
    }
    else {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            close(cmd_fd);
            cmd_fd = open(CMD_PIPE, O_RDONLY | O_NONBLOCK);
        }
    }
}

void update()
{
    UpdateMusicStream(music);

    if (volume > 1.0f) volume = 1.0f;
    if (volume < 0.0f) volume = 0.0f;

    SetMusicVolume(music, getAbsVol());
}

void render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    float played = GetMusicTimePlayed(music);
    float total  = GetMusicTimeLength(music);
    float progress = (total > 0) ? (played / total) : 0;

    DrawText("RUST TUI CONTROLLING THIS", 20, 20, 20, RAYWHITE);

    DrawRectangle(20, 60, 300, 20, DARKGRAY);
    DrawRectangle(20, 60, (int)(300 * progress), 20, GREEN);

    DrawText(TextFormat("%.1f / %.1f", played, total), 20, 90, 20, RAYWHITE);
    DrawText(TextFormat("Vol: %.0f%% %s", volume * 100, muted ? "(MUTED)" : ""), 20, 120, 20, RAYWHITE);

    if (paused) DrawText("PAUSED", 20, 150, 20, YELLOW);
    else DrawText("PLAYING", 20, 150, 20, GREEN);

    EndDrawing();
}

void quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();

    if (cmd_fd >= 0) close(cmd_fd);

    CloseWindow();
}