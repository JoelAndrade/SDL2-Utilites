#ifndef SDL_CLASSES_H
#define SDL_CLASSES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL_Util.h"

#include <iostream>

#define RENDER_COLOR {0, 0, 0, 0xFF} // black background
// #define render_color 255, 255, 255, 0xFF // white background

class Window
{
public:
    int w;
    int h;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Color render_color = RENDER_COLOR;

    Window();
    Window(int w, int h, const char *title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN);

    void init(int w, int h, const char *title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN);

    void set_window_size(int w, int h);

    void set_window_size(void);

    void set_window_pos(int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED);

    SDL_Texture *create_surface_texture(int w, int h, SDL_Color color); // TODO: Doesnt the texture class already do this?

    void clear_render(void);

    void render(void);

    void draw_line(int x1, int y1, int x2, int y2, SDL_Color color, int xScale = 1, int yScale = 1); // TODO: Add another functions that takes in points
    void draw_lines(SDL_Point *points, SDL_Color color, int num_points, int xScale = 1, int yScale = 1);

    void draw_rect(SDL_Color color, SDL_Rect rect, int xScale = 1, int yScale = 1);
    void draw_rect(SDL_Color color, int xScale = 1, int yScale = 1);

    void fill_rect(SDL_Color color, SDL_Rect rect, int xScale = 1, int yScale = 1);
    void fill_rect(SDL_Color color, float xScale = 1, float yScale = 1);

    void draw_circle(SDL_Point center, SDL_Color color, int radius, int scale = 1, double increments = 1);

    ~Window();
};

class TextureImage
{
public:
    SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect original_rect;
    SDL_Rect new_rect;

    TextureImage();
    TextureImage(SDL_Renderer *renderer, const char *image_path, double scale_image = 1.0, int x = 1, int y = 1);
    TextureImage(SDL_Renderer *renderer, const char *image_path, int w, int h, int x = 0, int y = 0);
    TextureImage(SDL_Renderer *renderer, SDL_Color color, int w, int h, int x = 0, int y = 0);

    void init(SDL_Renderer *renderer, const char *image_path, double scale_image = 1.0, int x = 0, int y = 0);
    void init(SDL_Renderer *renderer, const char *image_path, int w, int h, int x = 0, int y = 0);
    void init(SDL_Renderer *renderer, SDL_Color color, int w, int h, int xPos = 0, int yPos = 0);

    void resize(int w, int h);
    void change_pos(int x, int y);

    void render(void);
    void render_rotate(double angle, SDL_Point *center = NULL);
    void render_flip(SDL_RendererFlip flip);

    void set_alpha(Uint8 alpha);
    void set_blend(SDL_BlendMode blendMode);

    ~TextureImage();
};

class TextureText
{
public:
    TTF_Font *font = NULL;
    SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect rect;
    SDL_Color color = {0, 0, 0, 0xFF};
    int font_size = 10;
    const char *font_path = NULL;
    std::string text = "";

    TextureText();
    TextureText(SDL_Renderer *renderer, const char *font_path, const char *text, int font_size, int x = 0, int y = 0);

    void init(SDL_Renderer *renderer, const char *font_path, const char *text, int font_size, int x = 0, int y = 0);

    void resize(int font_size);
    void change_pos(int x, int y);
    void change_pos_and_size(int font_size, int x, int y);

    void render(void);

    void create_texture(void);

    void change_color(SDL_Color color);
    void change_font(const char *font_path);

    ~TextureText();
};

class MouseCursor
{
public:
    SDL_Texture *texture = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect original_rect;
    SDL_Rect new_rect;
    SDL_Point mouse_pos;
    bool hold = false;

    MouseCursor(SDL_Renderer *renderer = NULL, const char *image_path = NULL, double scale_image = 1.0);

    void init(SDL_Renderer *renderer = NULL, const char *image_path = NULL, double scale_image = 1.0);

    void update_cursor_pos(SDL_Window *window);

    void resize(int w, int h);

    void render(void);

    void set_alpha(Uint8 alpha);
    void set_blend(SDL_BlendMode blendMode);

    ~MouseCursor();
};

#endif // SDL_CLASSES_H
