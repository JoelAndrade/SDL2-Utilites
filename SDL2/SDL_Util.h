#ifndef SDL_UTIL_H
#define SDL_UTIL_H

#include <SDL2/SDL.h>

#define EXPAND_COLOR(color) color.r, color.g, color.b
#define LIMITS(a, param, b) (a <= param && param <= b)

//RGB
extern SDL_Color violet;
extern SDL_Color green;
extern SDL_Color red;
extern SDL_Color cyan;
extern SDL_Color blue;
extern SDL_Color black;
extern SDL_Color white;
extern SDL_Color orange;
extern SDL_Color yellow;

void frame_cap(int fps, Uint32 starting_tick);
void update_cursor_pos(SDL_Rect* rect, int xPos, int yPos);

#endif // SDL_UTIL_H