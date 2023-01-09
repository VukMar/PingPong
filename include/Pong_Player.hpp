#ifndef PONG_PLAYER_HPP
#define PONG_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Player
{
    enum ID
    {
        One = 1,
        Two = 2 
    };

}

class PongPlayer
{
public:

bool isAI = false;
bool ButtonUpPressed = false;
bool ButtonDownPressed = false;

float velocity;

sf::Vector2f Size;
sf::Vector2f getPos();

int NormalAngle;

PongPlayer();
~PongPlayer();

void create(sf::Vector2f PlayerSize, sf::Color Color, Player::ID id, 
            sf::Vector2f PlayFieldSize, 
            sf::Vector2f PlayFieldStartPosition);

void displayTo(sf::RenderWindow &Window);

void playerUpdate(float tick);

void addTexture(sf::Texture &Texture);

void setMovementSound(std::string FilePath);

bool IsMovingUp();

bool isMovingDown();

private:

int pID;

bool hasSound = false;
bool soundPlayed = false;

bool MovingUp = false;
bool MovingDown = false;

float speed;

sf::Vector2f PlayField;
sf::Vector2f PlayFiledPos;

sf::Keyboard::Key UP;
sf::Keyboard::Key DOWN;

sf::Sound MoveSound;
sf::SoundBuffer Soundbuf;

sf::RectangleShape p;



};

#endif