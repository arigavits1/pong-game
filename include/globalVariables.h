#pragma once

unsigned int SCR_WIDTH = 1400;
unsigned int SCR_HEIGHT = 600;

int player1Score = 0;
int player2Score = 0;

SDL_Color textColor = {255, 255, 255, 255};

int randomIndex(int min, int max)
{

    std::chrono::_V2::system_clock::rep seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    int index = distribution(generator);
    return index;
}

float speed = 250.0f;
Vector2f movements[] = { Vector2f(speed - 50.0f, speed), Vector2f(-speed, speed - 50.0f), Vector2f(speed - 50.0f, -speed), Vector2f(-speed - 50.0f, -speed) };