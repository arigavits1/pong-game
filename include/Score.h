#pragma once
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "globalVariables.h"
#include "Entity.h"

class Score : public Entity
{
public:
    Score(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, const char* p_font_path, int p_font_size, std::string p_text, const SDL_Color &p_color) : Entity(p_pos, p_scale, p_tex), font_path(p_font_path), font_size(p_font_size), text(p_text), color(p_color)
    {
        font = TTF_OpenFont(font_path, font_size);
        if (!font)
        {
            std::cout << "Failed to load font" << std::endl;
        }
    }
    SDL_Surface* loadFontSurface(std::string p_text)
    {
        SDL_Surface* text_surface = TTF_RenderText_Solid(font, p_text.c_str(), color);
        if (!text_surface)
        {
            std::cout << "Failed to create text surface" << std::endl;
        }

        return text_surface;
    }

    void setTexture(SDL_Texture* p_tex2)
    {
        setTex(p_tex2);
    }

    TTF_Font* getFont()
    {
        return font;
    }

private:
    SDL_Texture* text_texture;
    SDL_Rect text_rect;
    const char* &font_path;
    int font_size;
    std::string text;
    const SDL_Color &color;
    TTF_Font* font;
};