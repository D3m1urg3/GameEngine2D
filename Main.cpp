#include "SDL.h"
#include <windows.h>
#include "Globals.h"
#include "Game.h"

#define MS_PER_FRAME 33 // 30 frames/sec

long getCurrentTime();
void sleep(long ms);

int main(int argc, char* argv[])
{
    Game game;
    if (game.init())
    {
        while (GAME_FINISHED != game.getStatus())
        {
            long frame_start_time = getCurrentTime();
            game.update();
            sleep(frame_start_time + MS_PER_FRAME - getCurrentTime());
        }
    }

    return 0;
}

long getCurrentTime()
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    LONG timems = (time.wSecond * 1000) + time.wMilliseconds;

    return timems;
}

void sleep(long ms)
{
    SDL_PumpEvents();
    SDL_Delay(ms);
    //Sleep(ms); old code. Had to use SDL functions to avoid freezing
}