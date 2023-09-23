#ifndef SDL_CLASSES_H
#define SDL_CLASSES_H

#include <iostream>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define PI (3.1415)
#define DEG_TO_RAD(deg) (deg * (2.0*PI/360))

#define RENDERCOLOR 0, 0, 0, 0xFF // black background
// #define render_color 255, 255, 255, 0xFF // white background

class win
{
public:
    int w;
    int h;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Color render_color = {RENDERCOLOR};

    win() {}
    win(int width, int height, const char* title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN)
    {
        w = width;
        h = height;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
    }

    void init(int width, int height, const char* title = "No Title", SDL_WindowFlags flag = SDL_WINDOW_SHOWN)
    {
        w = width;
        h = height;
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
    }

    void set_window_size(int width, int height)
    {
        w = width;
        h = height;
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
        int x_global_mouse_pos;
        int y_global_mouse_pos;
        int x_window_pos;
        int y_window_pos;

        SDL_GetGlobalMouseState(&x_global_mouse_pos, &y_global_mouse_pos);
        SDL_GetWindowPosition(window, &x_window_pos, &y_window_pos);

        int x_relative = x_global_mouse_pos - x_window_pos;
        int y_relative = y_global_mouse_pos - y_window_pos;

        if ((-1 < x_relative && x_relative < w) &&
            (-1 < y_relative && y_relative < h))
        {
            return true;
        }
        return false;
    }

    SDL_Texture* create_surface_texture(int width, int height, int r = 255, int g = 255, int b = 255, int a = 0xFF)
    {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, r, g, b, a));
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
        return texture;
    }

    void clearRender(void)
    {
        SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
        SDL_RenderClear(renderer);
    }

    void drawLine(int x1, int y1, int x2, int y2, SDL_Color* color, int xScale = 1, int yScale = 1) // TODO: Might want to change the parameters to take to point types
    {
        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        if (xScale < 1)
        {
            xScale = 1;
        }
        if (yScale < 1)
        {
            yScale = 1;
        }

        xScale -= 1;
        yScale -= 1;

        x1 = x1 - xScale;
        y1 = y1 - yScale;
        x2 = x2 - xScale;
        y2 = y2 - yScale;

        for (int i = 0; x1 - xScale + i < x1 + xScale + 1; ++i)
        {
            for (int j = 0; y1 - yScale + j < y1 + yScale + 1; ++j)
            {
                SDL_RenderDrawLine(renderer, x1 + i, y1 + j, x2 + i, y2 + j);
            }
        }
    }
    void drawLines(SDL_Point* points, SDL_Color* color, int num_points, int xScale = 1, int yScale = 1)
    {
        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        if (xScale < 1)
        {
            xScale = 1;
        }
        if (yScale < 1)
        {
            yScale = 1;
        }

        xScale -= 1;
        yScale -= 1;

        for (int i = 0; i < num_points; ++i)
        {
            points[i].x -= xScale;
            points[i].y -= yScale;
        }

        for (int i = 0; points[0].x - xScale + i < points[0].x + xScale + 1; ++i)
        {
            for (int i = 0; points[0].y - yScale + i < points[0].y + yScale + 1; ++i)
            {
                SDL_RenderDrawLines(renderer, points, num_points);
                for (int j = 0; j < num_points; ++j)
                {
                    ++points[j].y;
                }
            }
            for (int j = 0; j < num_points; ++j)
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

    void drawRect(SDL_Color* color, SDL_Rect rect, int xScale = 1, int yScale = 1)
    {
        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        if (xScale < 1)
        {
            xScale = 1;
        }
        if (yScale < 1)
        {
            yScale = 1;
        }

        xScale -= 1;
        yScale -= 1;

        SDL_Rect temp_rect = rect;
        temp_rect.x = temp_rect.x - xScale;
        temp_rect.y = temp_rect.y - yScale;
        for (int i = 0; rect.x - xScale + i < rect.x + xScale + 1; ++i)
        {
            SDL_RenderDrawRect(renderer, &temp_rect);
            ++temp_rect.x;
        }
        temp_rect = rect;
        temp_rect.x = temp_rect.x - xScale;
        temp_rect.y = temp_rect.y - yScale;
        for (int i = 0; rect.y - yScale + i < rect.y + yScale + 1; ++i)
        {
            SDL_RenderDrawRect(renderer, &temp_rect);
            ++temp_rect.y;
        }
        temp_rect = rect;
        temp_rect.x = temp_rect.x + xScale;
        temp_rect.y = temp_rect.y + yScale;
        for (int i = 0; rect.y - yScale - 1 < rect.y + yScale + i; --i)
        {
            SDL_RenderDrawRect(renderer, &temp_rect);
            --temp_rect.y;
        }
    }
    void drawRect(SDL_Color* color, int xScale = 1, int yScale = 1)
    {
        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        if (xScale < 1)
        {
            xScale = 1;
        }
        if (yScale < 1)
        {
            yScale = 1;
        }

        SDL_RenderSetScale(renderer, xScale, yScale);
        SDL_RenderDrawRect(renderer, NULL);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void fillRect(SDL_Color* color, SDL_Rect rect, int xScale = 1, int yScale = 1)
    {
        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        rect.w = rect.w + 1;
        rect.h = rect.h + 1;
        SDL_RenderFillRect(renderer, &rect);
    }
    void fillRect(SDL_Color* color, float xScale = 1, float yScale = 1)
    {
        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        SDL_RenderSetScale(renderer, xScale, yScale);
        SDL_RenderFillRect(renderer, NULL);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    void drawCircle(SDL_Point center, SDL_Color* color, int radius, int scale = 1, double increments = 1)
    {

        if (color == NULL)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
        }
        if (scale < 1)
        {
            scale = 1;
        }

        int x;
        int y;

        SDL_Point previous_point = {radius, 0};
        for (double theta = 0; theta < 360; theta = theta + increments)
        {
            x = round(radius*cos(DEG_TO_RAD(theta)));
            y = round(radius*sin(DEG_TO_RAD(theta)));

            drawLine(center.x + previous_point.x, center.y - previous_point.y, center.x + x, center.y - y, color, scale, scale);

            previous_point.x = x;
            previous_point.y = y;
        }
    }
};

class texture_image
{
public:
    SDL_Texture* texture = NULL;
    SDL_Rect original_rect;
    SDL_Rect new_rect;

    texture_image() {}
    texture_image(SDL_Renderer* renderer, const char* path, double scale_image = 1.0, int xPos = 1, int yPos = 1)
    {
        SDL_Surface* image_surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = xPos;
        new_rect.w = image_surface->w * scale_image;
        new_rect.h = image_surface->h * scale_image;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    texture_image(SDL_Renderer* renderer, const char* path, int width, int height, int xPos = 0, int yPos = 0)
    {
        SDL_Surface* image_surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = width;
        new_rect.h = height;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    texture_image(SDL_Renderer* renderer, SDL_Color color, int width, int height, int xPos = 0, int yPos = 0)
    {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        blend(SDL_BLENDMODE_BLEND);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = surface->w;
        original_rect.h = surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = width;
        new_rect.h = height;
        new_rect.makeDimensions();

        SDL_FreeSurface(surface);
    }

    void init(SDL_Renderer* renderer, const char* path, double scale_image = 1.0, int xPos = 0, int yPos = 0)
    {
        SDL_Surface* image_surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = image_surface->w * scale_image;
        new_rect.h = image_surface->h * scale_image;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    void init(SDL_Renderer* renderer, const char* path, int width, int height, int xPos = 0, int yPos = 0)
    {
        SDL_Surface* image_surface = IMG_Load(path);
        texture = SDL_CreateTextureFromSurface(renderer, image_surface);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = image_surface->w;
        original_rect.h = image_surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = width;
        new_rect.h = height;
        new_rect.makeDimensions();

        SDL_FreeSurface(image_surface);
    }
    void init(SDL_Renderer* renderer, SDL_Color color, int width, int height, int xPos = 0, int yPos = 0)
    {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        blend(SDL_BLENDMODE_BLEND);

        original_rect.x = 0;
        original_rect.y = 0;
        original_rect.w = surface->w;
        original_rect.h = surface->h;
        original_rect.makeDimensions();
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = width;
        new_rect.h = height;
        new_rect.makeDimensions();

        SDL_FreeSurface(surface);
    }

    void resize(int w, int h)
    {
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();
    }

    void change_pos(int xPos, int yPos)
    {
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.makeDimensions();
    }

    void change_pos_and_size(int w, int h, int xPos, int yPos)
    {
        new_rect.x = xPos;
        new_rect.y = yPos;
        new_rect.w = w;
        new_rect.h = h;
        new_rect.makeDimensions();
    }

    void render(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, texture, &original_rect, &new_rect);
    }

    void render_rotate(SDL_Renderer* renderer, double angle, SDL_Point* center = NULL)
    {
        SDL_RenderCopyEx(renderer, texture, &original_rect, &new_rect, angle, center, SDL_FLIP_NONE);
    }

    void render_flip(SDL_Renderer* renderer, SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx(renderer, texture, &original_rect, &new_rect, 0.0, NULL, flip);
    }

    void set_alpha(Uint8 alpha)
    {
        SDL_SetTextureAlphaMod(texture, alpha);
    }

    void blend(SDL_BlendMode blendMode)
    {
        SDL_SetTextureBlendMode(texture, blendMode);
    }

    void destroy(void)
    {
        SDL_DestroyTexture(texture);
    }
};

class texture_text
{
public:
    TTF_Font* font = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect rect;
    SDL_Color color = {0, 0, 0, 0xFF};
    int font_size = 10;
    const char* path = NULL;
    std::string text = "";

    texture_text() {}
    texture_text(SDL_Renderer* renderer, const char* path_input, const char* text_input, int font_size_val, int xPos = 0, int yPos = 0)
    {
        text = text_input;
        font_size = font_size_val;
        path = path_input;
        font = TTF_OpenFont(path, font_size);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        rect.x = xPos;
        rect.y = yPos;
        if (text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void init(SDL_Renderer* renderer, const char* path_input, const char* text_input, int font_size_val, int xPos = 0, int yPos = 0)
    {
        text = text_input;
        font_size = font_size_val;
        path = path_input;
        font = TTF_OpenFont(path, font_size);
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(renderer, text_surface);

        rect.x = xPos;
        rect.y = yPos;
        if (text != "")
        {
            rect.w = text_surface->w;
            rect.h = text_surface->h;
            rect.makeDimensions();
        }

        SDL_FreeSurface(text_surface);
    }

    void resize(int font_size_val)
    {
        if (font != NULL)
        {
            font_size = font_size_val;
            font = TTF_OpenFont(path, font_size);
            SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

            if (text != "")
            {
                rect.w = text_surface->w;
                rect.h = text_surface->h;
                rect.makeDimensions();
            }

            SDL_FreeSurface(text_surface);
        }
        else
        {
            std::cout << "Font is NULL" << std::endl;
        }
    }

    void change_pos(int xPos, int yPos)
    {
        rect.x = xPos;
        rect.y = yPos;
        rect.makeDimensions();
    }

    void change_pos_and_size(int font_size_val, int xPos, int yPos)
    {
        if (font != NULL)
        {
            font_size = font_size_val;
            font = TTF_OpenFont(path, font_size);
            SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

            rect.x = xPos;
            rect.y = yPos;
            if (text != "")
            {
                rect.w = text_surface->w;
                rect.h = text_surface->h;
                rect.makeDimensions();
            }

            SDL_FreeSurface(text_surface);
        }
        else
        {
            std::cout << "Font is NULL" << std::endl;
        }
    }

    void render(SDL_Renderer* renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void create_texture(SDL_Renderer* renderer)
    {
        if (font != NULL)
        {
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
        else
        {
            std::cout << "Font is NULL" << std::endl;
        }
    }

    void change_color(SDL_Color* colorVal)
    {
        color.r = colorVal->r;
        color.g = colorVal->g;
        color.b = colorVal->b;
        color.a = colorVal->a;
    }

    void change_font(const char* pathVal)
    {
        font = NULL;
        path = pathVal;
        font = TTF_OpenFont(path, font_size);
    }

    void destroy(void)
    {
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
};

#endif // SDL_CLASSES_H
