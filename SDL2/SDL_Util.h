#ifndef SDL_UTIL_H
#define SDL_UTIL_H

#include <SDL2/SDL.h>

#define EXPAND_COLOR(color) color.r, color.g, color.b
#define LIMITS(a, param, b) (((a) <= (param)) && ((param) <= (b)))

typedef uint32_t uint;

//RGB
extern SDL_Color SDL_violet;
extern SDL_Color SDL_green;
extern SDL_Color SDL_red;
extern SDL_Color SDL_cyan;
extern SDL_Color SDL_blue;
extern SDL_Color SDL_black;
extern SDL_Color SDL_white;
extern SDL_Color SDL_orange;
extern SDL_Color SDL_yellow;

void frame_cap(int fps, Uint32 starting_tick);
void update_cursor_pos(SDL_Rect* rect, int xPos, int yPos);

void rect_make_dimensions(SDL_Rect *rect);
void rect_shiftX(SDL_Rect *rect, int multiplier = 1);
void rect_shiftY(SDL_Rect *rect, int multiplier = 1);
void rect_shiftXY(SDL_Rect *rect, int multiplier_x = 1, int multiplier_y = 1);

#endif // SDL_UTIL_H