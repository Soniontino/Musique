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

float getAbsVol() {
    return muted ? 0.0f : volume;
}

int cmd_fd = -1;
char cmd_buf[64];

void start()
{
    system("clear");
    SetTargetFPS(60);
    InitAudioDevice();

    mkfifo(CMD_PIPE, 0666);

    cmd_fd = open(CMD_PIPE, O_RDONLY | O_NONBLOCK);

    music = LoadMusicStream(RESOURCES_D "/song.mp3");

    if (music.stream.buffer == NULL) {
        printf("Failed to load music file!\n");
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
    int n = read(cmd_fd, cmd_buf, sizeof(cmd_buf)-1);

    if (n > 0) {
        cmd_buf[n] = '\0';
        handle_cmd(cmd_buf);
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
    float played = GetMusicTimePlayed(music);
    float total  = GetMusicTimeLength(music);
    float progress = (total > 0) ? (played / total) : 0;

    DrawText("RUST TUI CONTROLLING THIS", 20, 20, 20, RAYWHITE);
    DrawRectangle(20, 60, 300 * progress, 20, GREEN);
}

void quit()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
    close(cmd_fd);
}