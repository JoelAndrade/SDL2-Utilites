#include "SDL_Util.h"

#include <SDL2/SDL.h>

//RGB
SDL_Color SDL_violet = {255,   0, 255};
SDL_Color SDL_green =  {  0, 255,   0};
SDL_Color SDL_red =    {255,   0,   0};
SDL_Color SDL_cyan =   {  0, 255, 255};
SDL_Color SDL_blue =   {  0,   0, 255};
SDL_Color SDL_black =  {  0,   0,   0};
SDL_Color SDL_white =  {255, 255, 255};
SDL_Color SDL_orange = {255, 100,   0};
SDL_Color SDL_yellow = {255, 255,   0};

void frame_cap(int fps, Uint32 starting_tick)
{
    if (1000/fps > SDL_GetTicks() - starting_tick)
    {
        SDL_Delay(1000/fps - (SDL_GetTicks() - starting_tick));
    }
}

void update_cursor_pos(SDL_Rect* rect, int xPos, int yPos)
{
    rect->x = xPos;
    rect->y = yPos;
}
