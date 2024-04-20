#ifndef SDL_CLASSES_H
#define SDL_CLASSES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL_Util.h"

#include <iostream>
#include <string.h>
#include <math.h>

#define PI (3.1415)
#define DEG_TO_RAD(deg) (deg * (2.0*PI/360))

#define RENDER_COLOR 0, 0, 0, 0xFF // black background
// #define render_color 255, 255, 255, 0xFF // white background

class Window
{
public:
    int w;
    int h;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Color render_color = {RENDER_COLOR};

    Window() {}
    Window(int w, int h, const char* title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN)
    {
        this->w = w;
        this->h = h;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
    }

    void init(int w, int h, const char* title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        
        this->w = w;
        this->h = h;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
    }

    void set_window_size(int w, int h)
    {
        this->w = w;
        this->h = h;
        SDL_SetWindowSize(window, w, h);
    }

    void get_window_size(void)
    {
        SDL_GetWindowSize(window, &w, &h);
    }

    void set_window_pos(int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED)
    {
        SDL_SetWindowPosition(window, x, y);
    }

    bool mouse_in_window(void)
    {
        SDL_Point global_mouse_pos;
        SDL_Point window_pos;
        SDL_Point relative;

        SDL_GetGlobalMouseState(&global_mouse_pos.x, &global_mouse_pos.y);
        SDL_GetWindowPosition(window, &window_pos.x, &window_pos.y);

        relative.x = global_mouse_pos.x - window_pos.x;
        relative.x = global_mouse_pos.y - window_pos.y;

        if (LIMITS(0, relative.x, w) &&
            LIMITS(0, relative.y, h))
        {
            return true;
        }

        return false;
    }

    SDL_Texture* create_surface_texture(int w, int h, SDL_Color color) // TODO: Doesnt the texture class allredy do this
    {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
        return texture;
    }

    void clear_render(void)
    {
        SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
        SDL_RenderClear(renderer);
    }

    void render(void)
    {
        SDL_RenderPresent(renderer);
    }

    void draw_line(int x1, int y1, int x2, int y2, SDL_Color color, int xScale = 1, int yScale = 1) // TODO: Add another functions that takes in points
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        xScale--;
        yScale--;

        x1 -= xScale;
        y1 -= yScale;
        x2 -= xScale;
        y2 -= yScale;

        for (int i = 0; x1 - xScale + i < x1 + xScale + 1; ++i)
        {
            for (int j = 0; y1 - yScale + j < y1 + yScale + 1; ++j)
            {
                SDL_RenderDrawLine(renderer, x1 + i, y1 + j, x2 + i, y2 + j);
            }
        }
    }
    void draw_lines(SDL_Point* points, SDL_Color color, int num_points, int xScale = 1, int yScale = 1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        xScale--;
        yScale--;

        for (int i = 0; i < num_points; i++)
        {
            points[i].x -= xScale;
            points[i].y -= yScale;
        }

        for (int i = 0; points[0].x - xScale + i < points[0].x + xScale + 1; i++)
        {
            for (int i = 0; points[0].y - yScale + i < points[0].y + yScale + 1; i++)
            {
                SDL_RenderDrawLines(renderer, points, num_points);
                for (int j = 0; j < num_points; j++)
                {
                    points[j].y++;
                }
            }
            for (int j = 0; j < num_points; j++)
            {
                points[j].y -= (2*yScale) + 1;
                ++points[j].x;
            }
        }

        for (int i = 0; i < num_points; ++i)
        {
            points[i].x -= xScale + 1;
            points[i].y += yScale;
        }
    }

    void draw_rect(SDL_Color color, SDL_Rect rect, int xScale = 1, int yScale = 1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        xScale--;
        yScale--;

        SDL_Rect temp_rect = rect;
        temp_rect.x = temp_rect.x - xScale;
        temp_rect.y = temp_rect.y - yScale;
        for (int i = 0; rect.x - xScale + i < rect.x + xScale + 1; i++)
        {
            SDL_RenderDrawRect(renderer, &temp_rect);
            temp_rect.x++;
        }
        temp_rect = rect;
        temp_rect.x = temp_rect.x - xScale;
        temp_rect.y = temp_rect.y - yScale;
        for (int i = 0; rect.y - yScale + i < rect.y + yScale + 1; i++)
        {
            SDL_RenderDrawRect(renderer, &temp_rect);
            temp_rect.y++;
        }
        temp_rect = rect;
        temp_rect.x = temp_rect.x + xScale;
        temp_rect.y = temp_rect.y + yScale;
        for (int i = 0; rect.y - yScale - 1 < rect.y + yScale + i; i--)
        {
            SDL_RenderDrawRect(renderer, &temp_rect);
            temp_rect.y--;
        }
    }
    void draw_rect(SDL_Color color, int xScale = 1, int yScale = 1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_RenderSetScale(renderer, xScale, yScale);
        SDL_RenderDrawRect(renderer, NULL);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void fill_rect(SDL_Color color, SDL_Rect rect, int xScale = 1, int yScale = 1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        rect.w++;
        rect.h++;
        SDL_RenderFillRect(renderer, &rect);
    }
    void fill_rect(SDL_Color color, float xScale = 1, float yScale = 1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderSetScale(renderer, xScale, yScale);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void draw_circle(SDL_Point center, SDL_Color color, int radius, int scale = 1, double increments = 1)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        int x;
        int y;

        SDL_Point previous_point = {(int)radius, 0};
        for (double theta = 0; theta < 360; theta += increments)
        {
            x = round(radius*cos(DEG_TO_RAD(theta)));
            y = round(radius*sin(DEG_TO_RAD(theta)));

            draw_line(center.x + previous_point.x, center.y - previous_point.y, center.x + x, center.y - y, color, scale, scale);

            previous_point.x = x;
            previous_point.y = y;
        }
    }

    ~Window()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
};

class TextureImage
{
public:
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect original_rect;
    SDL_Rect new_rect;

    TextureImage() {}
    TextureImage(SDL_Renderer* renderer, const char* image_path, double scale_image = 1.0, int x = 1, int y = 1)
    {
        this->renderer = renderer;

        SDL_Surface* image_surface = IMG_Load(image_path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = x;
        new_rect.y = y;
        new_rect.w = image_surface->w * scale_image;
        new_rect.h = image_surface->h * scale_image;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    TextureImage(SDL_Renderer* renderer, const char* image_path, int w, int h, int x = 0, int y = 0)
    {
        this->renderer = renderer;
        
        SDL_Surface* image_surface = IMG_Load(image_path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = x;
        new_rect.y = y;
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    TextureImage(SDL_Renderer* renderer, SDL_Color color, int w, int h, int x = 0, int y = 0)
    {
        this->renderer = renderer;
        
        SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        set_blend(SDL_BLENDMODE_BLEND);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = surface->w;
        original_rect.h = surface->h;
        original_rect.makeDimensions();
        new_rect.x = x;
        new_rect.y = y;
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();

        SDL_FreeSurface(surface);
    }

    void init(SDL_Renderer* renderer, const char* image_path, double scale_image = 1.0, int x = 0, int y = 0)
    {
        SDL_DestroyTexture(texture);
        this->renderer = renderer;
        
        SDL_Surface* image_surface = IMG_Load(image_path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = x;
        new_rect.y = y;
        new_rect.w = image_surface->w * scale_image;
        new_rect.h = image_surface->h * scale_image;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    void init(SDL_Renderer* renderer, const char* image_path, int w, int h, int x = 0, int y = 0)
    {
        SDL_DestroyTexture(texture);
        this->renderer = renderer;
        
        SDL_Surface* image_surface = IMG_Load(image_path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = x;
        new_rect.y = y;
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    void init(SDL_Renderer* renderer, SDL_Color color, int w, int h, int xPos = 0, int yPos = 0)
    {
        SDL_DestroyTexture(texture);
        this->renderer = renderer;
        
        SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        set_blend(SDL_BLENDMODE_BLEND);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = surface->w;
        original_rect.h = surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();

        SDL_FreeSurface(surface);
    }

    void resize(int w, int h)
    {
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();
    }

    void change_pos(int x, int y)
    {
        new_rect.x = x;
        new_rect.y = y;
        new_rect.makeDimensions();
    }

    void render()
    {
        SDL_RenderCopy(renderer, texture, &original_rect, &new_rect);
    }

    void render_rotate(double angle, SDL_Point* center = NULL)
    {
        SDL_RenderCopyEx(renderer, texture, &original_rect, &new_rect, angle, center, SDL_FLIP_NONE);
    }

    void render_flip(SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx(renderer, texture, &original_rect, &new_rect, 0.0, NULL, flip);
    }

    void set_alpha(Uint8 alpha)
    {
        SDL_SetTextureAlphaMod(texture, alpha);
    }

    void set_blend(SDL_BlendMode blendMode)
    {
        SDL_SetTextureBlendMode(texture, blendMode);
    }

    ~TextureImage()
    {
        SDL_DestroyTexture(texture);
    }
};

class TextureText
{
public:
    TTF_Font* font = NULL;
    SDL_Texture* texture = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Rect rect;
    SDL_Color color = {0, 0, 0, 0xFF};
    int font_size = 10;
    const char* font_path = NULL;
    std::string text = "";

    TextureText() {}
    TextureText(SDL_Renderer* renderer, const char* font_path, const char* text, int font_size, int x = 0, int y = 0)
    {
        this->renderer  = renderer;
        this->font_path = font_path;
        this->text      = text;
        this->font_size = font_size;
        font = TTF_OpenFont(font_path, font_size);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, this->text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        rect.x = x;
        rect.y = y;
        if (this->text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void init(SDL_Renderer* renderer, const char* font_path, const char* text, int font_size, int x = 0, int y = 0)
    {
        TTF_CloseFont(font);

        this->renderer  = renderer;
        this->font_path = font_path;
        this->text      = text;
        this->font_size = font_size;
        font = TTF_OpenFont(font_path, font_size);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, this->text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        rect.x = x;
        rect.y = y;
        if (this->text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void resize(int font_size)
    {
        if (font == NULL)
            return;

        TTF_CloseFont(font);
        this->font_size = font_size;
        font = TTF_OpenFont(font_path, font_size);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

        if (text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void change_pos(int x, int y)
    {
        rect.x = x;
        rect.y = y;
        rect.makeDimensions();
    }

    void change_pos_and_size(int font_size, int x, int y)
    {
        if (font == NULL)
            return;

        TTF_CloseFont(font);
        this->font_size = font_size;
        font = TTF_OpenFont(font_path, font_size);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

        rect.x = x;
        rect.y = y;
        if (text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void render(void)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void create_texture(void)
    {
        if (font == NULL)
            return;

        SDL_DestroyTexture(texture);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        if (text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void change_color(SDL_Color color)
    {
        this->color = color;
    }

    void change_font(const char* font_path)
    {
        TTF_CloseFont(font);
        this->font_path = font_path;
        font = TTF_OpenFont(font_path, font_size);
    }

    ~TextureText()
    {
        SDL_DestroyTexture(texture);
        
        if (TTF_WasInit())
            TTF_CloseFont(font);
    }
};

#endif // SDL_CLASSES_H
