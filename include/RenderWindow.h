#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.h"
#include "Square.h"
#include "Score.h"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h)
	{
		window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_BORDERLESS);

		if (window == NULL)
		{
			std::cout << "Window failed to init. SDL_ERROR: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

	SDL_Texture* loadTexture(const char* p_filePath)
	{
		SDL_Texture* texture;
		texture = IMG_LoadTexture(renderer, p_filePath);

		if (texture == NULL)
		{
			std::cout << "Failed to load texture. SDL_ERROR: " << SDL_GetError() << std::endl;
		}

		return texture;
	}

	int getRefreshRate()
	{
		int displayIndex = SDL_GetWindowDisplayIndex(window);

		SDL_DisplayMode mode;

		SDL_GetDisplayMode(displayIndex, 0, &mode);

		return mode.refresh_rate;
	}

	void cleanUp()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void clear()
	{
		SDL_RenderClear(renderer);
	}

	void render(Entity& p_entity)
	{
		SDL_Rect src;
		src.x = p_entity.getCurrentFrame().x * 32;
		src.y = p_entity.getCurrentFrame().y * 32;
		src.w = p_entity.getCurrentFrame().w * 32;
		src.h = p_entity.getCurrentFrame().h * 32;

		SDL_Rect dst;
		dst.x = p_entity.getPos().x - p_entity.getCurrentFrame().w * 2;
    	dst.y = p_entity.getPos().y - p_entity.getCurrentFrame().h * 2;
		dst.w = p_entity.getCurrentFrame().w * 4;
		dst.h = p_entity.getCurrentFrame().h * 4;

		SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
	}

	void render(Square& p_square)
	{
		SDL_Rect src;
		src.x = p_square.getCurrentFrame().x * 32;
		src.y = p_square.getCurrentFrame().y * 32;
		src.w = p_square.getCurrentFrame().w * 32;
		src.h = p_square.getCurrentFrame().h * 32;

		SDL_Rect dst;
		dst.x = p_square.getPos().x - p_square.getCurrentFrame().w / 2;
    	dst.y = p_square.getPos().y - p_square.getCurrentFrame().h / 2;
		dst.w = p_square.getCurrentFrame().w / 2;
		dst.h = p_square.getCurrentFrame().h / 2;

		SDL_RenderCopy(renderer, p_square.getTex(), &src, &dst);
	}

	void render(Score& p_score, int index)
	{
		SDL_Rect src;
		src.x = p_score.getCurrentFrame().x * 32;
		src.y = p_score.getCurrentFrame().y * 32;
		src.w = p_score.getCurrentFrame().w * 32;
		src.h = p_score.getCurrentFrame().h * 32;

		SDL_Rect dst;
		dst.x = p_score.getPos().x - p_score.getCurrentFrame().w / 2; // Adjust the x-coordinate
    	dst.y = p_score.getPos().y - p_score.getCurrentFrame().h / 2; // Adjust the y-coordinate
		dst.w = p_score.getCurrentFrame().w;
		dst.h = p_score.getCurrentFrame().h;

		std::string stringScore;
		if (index == 0)
		{
			stringScore = std::to_string(player1Score);
		}
		else
		{
			stringScore = std::to_string(player2Score);
		}

		SDL_Texture* playerTextTexture = SDL_CreateTextureFromSurface(renderer, p_score.loadFontSurface(stringScore));

		SDL_RenderCopy(renderer, playerTextTexture, &src, &dst);
	}

	SDL_Renderer* getRenderer()
	{
		return renderer;
	}

	void display()
	{
		SDL_RenderPresent(renderer);
	}

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};