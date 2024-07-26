#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL_Util.h"
#include "SDL_CLasses.h"

#include <iostream>
#include <math.h>


#define PI (3.1415)
#define DEG_TO_RAD(deg) (deg * (2.0*PI/360))

// Window class functions
Window::Window() {}
Window::Window(int w, int h, const char *title, SDL_WindowFlags flag)
{
    this->w = w;
    this->h = h;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
}

void Window::init(int w, int h, const char *title, SDL_WindowFlags flag)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    this->w = w;
    this->h = h;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flag);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
}

void Window::set_window_size(int w, int h)
{
    this->w = w;
    this->h = h;
    SDL_SetWindowSize(window, w, h);
}

void Window::set_window_size(void)
{
    SDL_GetWindowSize(window, &w, &h);
}

void Window::set_window_pos(int x, int y)
{
    SDL_SetWindowPosition(window, x, y);
}

bool Window::mouse_in_window(void)
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

SDL_Texture *Window::create_surface_texture(int w, int h, SDL_Color color)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
    return texture;
}

void Window::clear_render(void)
{
    SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g, render_color.b, render_color.a);
    SDL_RenderClear(renderer);
}

void Window::render(void)
{
    SDL_RenderPresent(renderer);
}

void Window::draw_line(int x1, int y1, int x2, int y2, SDL_Color color, int xScale, int yScale)
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
void Window::draw_lines(SDL_Point *points, SDL_Color color, int num_points, int xScale, int yScale)
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

void Window::draw_rect(SDL_Color color, SDL_Rect rect, int xScale, int yScale)
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
void Window::draw_rect(SDL_Color color, int xScale, int yScale)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderSetScale(renderer, xScale, yScale);
    SDL_RenderDrawRect(renderer, NULL);
    SDL_RenderSetScale(renderer, 1, 1);
}

void Window::fill_rect(SDL_Color color, SDL_Rect rect, int xScale, int yScale)
{
    --xScale;
    --yScale;
    rect.x -= xScale;
    rect.y -= yScale;
    rect.w += 2*xScale;
    rect.h += 2*yScale;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}
void Window::fill_rect(SDL_Color color, float xScale, float yScale)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderSetScale(renderer, xScale, yScale);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderSetScale(renderer, 1, 1);
}

void Window::draw_circle(SDL_Point center, SDL_Color color, int radius, int scale, double increments)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int x;
    int y;

    SDL_Point previous_point = {radius, 0};
    for (double theta = 0; theta < 360; theta += increments)
    {
        x = round(radius*cos(DEG_TO_RAD(theta)));
        y = round(radius*sin(DEG_TO_RAD(theta)));

        draw_line(center.x + previous_point.x, center.y - previous_point.y, center.x + x, center.y - y, color, scale, scale);

        previous_point.x = x;
        previous_point.y = y;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}



// TextureImage class functions
TextureImage::TextureImage() {}
TextureImage::TextureImage(SDL_Renderer *renderer, const char *image_path, double scale_image, int x, int y)
{
    this->renderer = renderer;

    SDL_Surface *image_surface = IMG_Load(image_path);
    texture = SDL_CreateTextureFromSurface(renderer, image_surface);

    original_rect.x = 0;
    original_rect.y = 0;
    original_rect.w = image_surface->w;
    original_rect.h = image_surface->h;
    rect_make_dimensions(&original_rect);
    new_rect.x = x;
    new_rect.y = y;
    new_rect.w = image_surface->w * scale_image;
    new_rect.h = image_surface->h * scale_image;
    rect_make_dimensions(&new_rect);

    SDL_FreeSurface(image_surface);
}
TextureImage::TextureImage(SDL_Renderer *renderer, const char *image_path, int w, int h, int x, int y)
{
    this->renderer = renderer;
    
    SDL_Surface *image_surface = IMG_Load(image_path);
    texture = SDL_CreateTextureFromSurface(renderer, image_surface);

    original_rect.x = 0;
    original_rect.y = 0;
    original_rect.w = image_surface->w;
    original_rect.h = image_surface->h;
    rect_make_dimensions(&original_rect);
    new_rect.x = x;
    new_rect.y = y;
    new_rect.w = w;
    new_rect.h = h;
    rect_make_dimensions(&new_rect);

    SDL_FreeSurface(image_surface);
}
TextureImage::TextureImage(SDL_Renderer *renderer, SDL_Color color, int w, int h, int x, int y)
{
    this->renderer = renderer;
    
    SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    set_blend(SDL_BLENDMODE_BLEND);

    original_rect.x = 0;
    original_rect.y = 0;
    original_rect.w = surface->w;
    original_rect.h = surface->h;
    rect_make_dimensions(&original_rect);
    new_rect.x = x;
    new_rect.y = y;
    new_rect.w = w;
    new_rect.h = h;
    rect_make_dimensions(&new_rect);

    SDL_FreeSurface(surface);
}

void TextureImage::init(SDL_Renderer *renderer, const char *image_path, double scale_image, int x, int y)
{
    SDL_DestroyTexture(texture);
    this->renderer = renderer;
    
    SDL_Surface *image_surface = IMG_Load(image_path);
    texture = SDL_CreateTextureFromSurface(renderer, image_surface);

    original_rect.x = 0;
    original_rect.y = 0;
    original_rect.w = image_surface->w;
    original_rect.h = image_surface->h;
    rect_make_dimensions(&original_rect);
    new_rect.x = x;
    new_rect.y = y;
    new_rect.w = image_surface->w * scale_image;
    new_rect.h = image_surface->h * scale_image;
    rect_make_dimensions(&new_rect);

    SDL_FreeSurface(image_surface);
}
void TextureImage::init(SDL_Renderer *renderer, const char *image_path, int w, int h, int x, int y)
{
    SDL_DestroyTexture(texture);
    this->renderer = renderer;
    
    SDL_Surface *image_surface = IMG_Load(image_path);
    texture = SDL_CreateTextureFromSurface(renderer, image_surface);

    original_rect.x = 0;
    original_rect.y = 0;
    original_rect.w = image_surface->w;
    original_rect.h = image_surface->h;
    rect_make_dimensions(&original_rect);
    new_rect.x = x;
    new_rect.y = y;
    new_rect.w = w;
    new_rect.h = h;
    rect_make_dimensions(&new_rect);

    SDL_FreeSurface(image_surface);
}
void TextureImage::init(SDL_Renderer *renderer, SDL_Color color, int w, int h, int xPos, int yPos)
{
    SDL_DestroyTexture(texture);
    this->renderer = renderer;
    
    SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    set_blend(SDL_BLENDMODE_BLEND);

    original_rect.x = 0;
    original_rect.y = 0;
    original_rect.w = surface->w;
    original_rect.h = surface->h;
    rect_make_dimensions(&original_rect);
    new_rect.x = xPos;
    new_rect.y = yPos;
    new_rect.w = w;
    new_rect.h = h;
    rect_make_dimensions(&new_rect);

    SDL_FreeSurface(surface);
}

void TextureImage::resize(int w, int h)
{
    new_rect.w = w;
    new_rect.h = h;
    rect_make_dimensions(&new_rect);
}

void TextureImage::change_pos(int x, int y)
{
    new_rect.x = x;
    new_rect.y = y;
    rect_make_dimensions(&new_rect);
}

void TextureImage::render()
{
    SDL_RenderCopy(renderer, texture, &original_rect, &new_rect);
}

void TextureImage::render_rotate(double angle, SDL_Point *center)
{
    SDL_RenderCopyEx(renderer, texture, &original_rect, &new_rect, angle, center, SDL_FLIP_NONE);
}

void TextureImage::render_flip(SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(renderer, texture, &original_rect, &new_rect, 0.0, NULL, flip);
}

void TextureImage::set_alpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}

void TextureImage::set_blend(SDL_BlendMode blendMode)
{
    SDL_SetTextureBlendMode(texture, blendMode);
}

TextureImage::~TextureImage()
{
    SDL_DestroyTexture(texture);
}



// TextureText class functions
TextureText::TextureText() {}
TextureText::TextureText(SDL_Renderer *renderer, const char *font_path, const char *text, int font_size, int x, int y)
{
    this->renderer  = renderer;
    this->font_path = font_path;
    this->text      = text;
    this->font_size = font_size;
    font = TTF_OpenFont(font_path, font_size);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, this->text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    rect.x = x;
    rect.y = y;
    if (this->text != "")
    {
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        rect_make_dimensions(&rect);
    }

    SDL_FreeSurface(text_surface);
}

void TextureText::init(SDL_Renderer *renderer, const char *font_path, const char *text, int font_size, int x, int y)
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);

    this->renderer  = renderer;
    this->font_path = font_path;
    this->text      = text;
    this->font_size = font_size;
    font = TTF_OpenFont(font_path, font_size);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, this->text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    rect.x = x;
    rect.y = y;
    if (this->text != "")
    {
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        rect_make_dimensions(&rect);
    }

    SDL_FreeSurface(text_surface);
}

void TextureText::resize(int font_size)
{
    if (font == NULL)
        return;

    TTF_CloseFont(font);
    this->font_size = font_size;
    font = TTF_OpenFont(font_path, font_size);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (text != "")
    {
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        rect_make_dimensions(&rect);
    }

    SDL_FreeSurface(text_surface);
}

void TextureText::change_pos(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect_make_dimensions(&rect);
}

void TextureText::change_pos_and_size(int font_size, int x, int y)
{
    if (font == NULL)
        return;

    TTF_CloseFont(font);
    this->font_size = font_size;
    font = TTF_OpenFont(font_path, font_size);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

    rect.x = x;
    rect.y = y;
    if (text != "")
    {
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        rect_make_dimensions(&rect);
    }

    SDL_FreeSurface(text_surface);
}

void TextureText::render(void)
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void TextureText::create_texture(void)
{
    if (font == NULL)
        return;

    SDL_DestroyTexture(texture);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    if (text != "")
    {
        rect.w = text_surface->w;
        rect.h = text_surface->h;
        rect_make_dimensions(&rect);
    }

    SDL_FreeSurface(text_surface);
}

void TextureText::change_color(SDL_Color color)
{
    this->color = color;
}

void TextureText::change_font(const char *font_path)
{
    TTF_CloseFont(font);
    this->font_path = font_path;
    font = TTF_OpenFont(font_path, font_size);
}

TextureText::~TextureText()
{
    SDL_DestroyTexture(texture);
    
    if (TTF_WasInit())
        TTF_CloseFont(font);
}
