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

void rect_make_dimensions(SDL_Rect *rect)
{
    rect->tlX = rect->x;
    rect->tlY = rect->y;
    rect->trX =  rect->x + rect->w;
    rect->trY = rect->y;
    rect->blX = rect->x;
    rect->blY = rect->y + rect->h;
    rect->brX = rect->x + rect->w;
    rect->brY = rect->y + rect->h;
    rect->cX = rect->x + rect->w/2;
    rect->cY = rect->y + rect->h/2;
    rect->topX = rect->x + rect->w/2;
    rect->topY = rect->y;
    rect->bottomX = rect->x + rect->w/2;
    rect->bottomY = rect->y + rect->h;
    rect->leftX = rect->x;
    rect->leftY = rect->y + rect->h/2;
    rect->rightX = rect->x + rect->w;
    rect->rightY = rect->y + rect->h/2;
} 

void rect_shiftX(SDL_Rect *rect, int multiplier)
{
    int shift = multiplier*(rect->topX - rect->x);
    rect->x -= shift;
    rect->tlX -= shift;
    rect->trX -=  shift;
    rect->blX -= shift;
    rect->brX -= shift;
    rect->cX -= shift;
    rect->topX -= shift;
    rect->bottomX -= shift;
    rect->leftX -= shift;
    rect->rightX -= shift;
}

void rect_shiftY(SDL_Rect *rect, int multiplier)
{
    int shift = multiplier*(rect->leftY - rect->y);
    rect->y -= shift;
    rect->tlY -= shift;
    rect->trY -=  shift;
    rect->blY -= shift;
    rect->brY -= shift;
    rect->cY -= shift;
    rect->topY -= shift;
    rect->bottomY -= shift;
    rect->leftY -= shift;
    rect->rightY -= shift;
}

void rect_shiftXY(SDL_Rect *rect, int multiplier_x, int multiplier_y)
{
    int xShift = multiplier_x*(rect->topX - rect->x);
    int yShift = multiplier_y*(rect->leftY - rect->y);

    rect->x -= xShift;
    rect->tlX -= xShift;
    rect->trX -=  xShift;
    rect->blX -= xShift;
    rect->brX -= xShift;
    rect->cX -= xShift;
    rect->topX -= xShift;
    rect->bottomX -= xShift;
    rect->leftX -= xShift;
    rect->rightX -= xShift;

    rect->y -= yShift;
    rect->tlY -= yShift;
    rect->trY -=  yShift;
    rect->blY -= yShift;
    rect->brY -= yShift;
    rect->cY -= yShift;
    rect->topY -= yShift;
    rect->bottomY -= yShift;
    rect->leftY -= yShift;
    rect->rightY -= yShift;
} // Joel ended here

