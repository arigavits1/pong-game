#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "../include/RenderWindow.h"
#include "../include/Entity.h"
#include "../include/Square.h"
#include "../include/globalVariables.h"
#include "../include/Score.h"

int main(int argc, char* argv[])
{
    int index = randomIndex(0, 3);

	if(SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
	{
		std::cout << "TTF_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
	}

	RenderWindow window(NULL, SCR_WIDTH, SCR_HEIGHT);
	
	std::string player1ScoreString = std::to_string(player1Score);
	std::string player2ScoreString = std::to_string(player2Score);

	Score scores[] = { Score(Vector2f(100, 100), Vector2f(32, 32), nullptr, "res/dev/font.ttf", 50, player1ScoreString, textColor), 
								Score(Vector2f(SCR_WIDTH - 100, 100), Vector2f(32, 32), nullptr, "res/dev/font.ttf", 50, player2ScoreString, textColor)};

	SDL_Texture* playerTexture = window.loadTexture("res/images/texture.png");
	SDL_Texture* boxTexture = window.loadTexture("res/images/Wooden_Crate.png");
	
	SDL_Texture* playerTextTexture = SDL_CreateTextureFromSurface(window.getRenderer(), scores[0].loadFontSurface(player1ScoreString));
	scores[0].setTex(playerTextTexture);
	scores[1].setTex(playerTextTexture);

	std::vector<Entity> entities = {Entity(Vector2f(100, SCR_HEIGHT / 2), Vector2f(4, 40), playerTexture),
									Entity(Vector2f(SCR_WIDTH - 100, SCR_HEIGHT / 2), Vector2f(4, 40), playerTexture),};

	Square square(Vector2f(SCR_WIDTH / 2, SCR_HEIGHT / 2), Vector2f(32, 32), boxTexture, movements[index]);

	bool gameRunning = true;
	SDL_Event event;

	Uint32 prevTicks = SDL_GetTicks();

	while (gameRunning)
	{
		Uint32 currentTicks = SDL_GetTicks();
		float deltaTime = (currentTicks - prevTicks) / 1000.0f;
		prevTicks = currentTicks;
		int startTicks = SDL_GetTicks();
		
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					gameRunning = false;
				}
			}
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP] && entities[1].getPos().y - entities[1].getCurrentFrame().h * 2 >= 0)
		{
			entities[1].setPos(Vector2f(entities[1].getPos().x, entities[1].getPos().y + -speed * deltaTime));
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN] && entities[1].getPos().y + entities[1].getCurrentFrame().h * 2 <= SCR_HEIGHT)
		{
			entities[1].setPos(Vector2f(entities[1].getPos().x, entities[1].getPos().y + speed * deltaTime));
		}
		if (currentKeyStates[SDL_SCANCODE_W] && entities[0].getPos().y - entities[0].getCurrentFrame().h * 2 >= 0)
		{
			entities[0].setPos(Vector2f(entities[0].getPos().x, entities[0].getPos().y + -speed * deltaTime));
		}
		if (currentKeyStates[SDL_SCANCODE_S] && entities[0].getPos().y + entities[0].getCurrentFrame().h * 2 <= SCR_HEIGHT) 
		{
			entities[0].setPos(Vector2f(entities[0].getPos().x, entities[0].getPos().y + speed * deltaTime));
		}

		window.clear();

		window.render(square);
		square.move(deltaTime, true, entities);

		for (Entity &e : entities)
		{
			window.render(e);
		}

		for (int i = 0; i < 2; i++)
		{
			window.render(scores[i], i);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < window.getRefreshRate())
		{
			SDL_Delay(window.getRefreshRate() - frameTicks);
		}
	}

	window.cleanUp();
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	return 0;
}