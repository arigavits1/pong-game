#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "math.h"

class Entity
{
public:
	Entity(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex) : pos(p_pos), scale(p_scale), tex(p_tex)
	{
		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = scale.x;
		currentFrame.h = scale.y;
	}

	Vector2f &getPos()
	{
		return pos;
	}

	SDL_Texture* getTex()
	{
		return tex;
	}

	void setTex(SDL_Texture* p_tex2)
	{
		tex = p_tex2;
	}

	SDL_Rect getCurrentFrame()
	{
		return currentFrame;
	}

	void movePos(Vector2f speed)
	{
		pos.x += speed.x;
		pos.y += speed.y;
	}

	void setPos(Vector2f position)
	{
		pos = position;
	}

private:
	Vector2f pos;
	Vector2f scale;
	SDL_Texture* tex;
	SDL_Rect currentFrame;
};