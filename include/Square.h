#pragma once
#include "Entity.h"
#include "globalVariables.h"
#include <vector>

class Square : public Entity
{
public:
    Square(Vector2f p_pos, Vector2f p_scale, SDL_Texture* p_tex, Vector2f p_velocity) 
    : Entity(p_pos, p_scale, p_tex), velocity(p_velocity)
    {}

    void move(float deltaTime, bool collide, std::vector<Entity> entities)
    {
        movePos(Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));

        if (!collide) { return; };

        if (getPos().y - getCurrentFrame().h / 2 <= 0 || getPos().y + getCurrentFrame().h / 2 >= SCR_HEIGHT)
        {
            velocity.y *= -1;
        }

        if ((getPos().x - getCurrentFrame().w <= entities[0].getPos().x + entities[0].getCurrentFrame().w * 2 && getPos().x - getCurrentFrame().w / 2 > entities[0].getPos().x - entities[0].getCurrentFrame().w * 2 && getPos().y + getCurrentFrame().h / 2 >= entities[0].getPos().y - entities[0].getCurrentFrame().h * 2 && getPos().y - getCurrentFrame().h / 2 <= entities[0].getPos().y + entities[0].getCurrentFrame().h * 2) || 
        (getPos().x + getCurrentFrame().w / 4 >= entities[1].getPos().x - entities[1].getCurrentFrame().w * 2 && getPos().x + getCurrentFrame().w / 2 < entities[1].getPos().x + entities[1].getCurrentFrame().w * 2 && getPos().y + getCurrentFrame().h / 2 >= entities[1].getPos().y - entities[1].getCurrentFrame().h * 2 && getPos().y - getCurrentFrame().h / 2 <= entities[1].getPos().y + entities[1].getCurrentFrame().h * 2))
        {
            velocity.x *= -1;
        }

        if (getPos().x - getCurrentFrame().w / 2 > SCR_WIDTH)
        {
            player1Score += 1;
            setPos(Vector2f(SCR_WIDTH / 2, SCR_HEIGHT / 2));
        }
        else if (getPos().x + getCurrentFrame().w / 2 < 0.0f)
        {
            player2Score += 1;
            int index = randomIndex(0, 3);
            setPos(Vector2f(SCR_WIDTH / 2, SCR_HEIGHT / 2));
            velocity = movements[index];
        }
    }

private:
    Vector2f velocity;    
};