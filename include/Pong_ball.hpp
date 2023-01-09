#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "Pong_Player.hpp"

class PongBall
{
public:

PongBall();
~PongBall();

float velocity = 500.f;

bool leftGoal = false;
bool rightGoal = false;

//////////////////////////////////////////////////////////////////////////////////////
/// @brief Creates ball for pong.
/// @param radius radius of ball.
/// @param Color color of ball.
/// @param PlayFieldSize size of playfield.
/// @param PlayFieldStartPosition top left corner position of playfield.
//////////////////////////////////////////////////////////////////////////////////////
void create(float radius, sf::Color Color, sf::Vector2f PlayFieldSize, 
                sf::Vector2f PlayFieldStartPosition);

void launchBall();

void pause();

void displayTo(sf::RenderWindow &Window);

void Update(PongPlayer p1, PongPlayer p2, float tick);

bool addBouceSound(std::string FilePath);

sf::Vector2f getPosition();

void resetBall();

private:

sf::Vector2f BallStartingPos;

sf::Vector2f dirVec;
sf::Vector2f reflectedDir;

sf::Vector2f PlayField;
sf::Vector2f PlayFieldStartPos;

bool hasSound = false;
bool moving = false;
bool startingPos = true;

float r;
int Angle;
int nAngle;

sf::CircleShape ball;
sf::Color BallColor;
sf::Sound BounceSound;
sf::SoundBuffer bsBuf;
sf::Sound Goal;
sf::SoundBuffer GsBuff;

bool BorderColision(float tick);

bool TestColison(PongPlayer &p, float tick);

float rad(int angle);

float dotProduct(sf::Vector2f a, sf::Vector2f b);

sf::Vector2f CreateReflectedVector(sf::Vector2f d, sf::Vector2f n);

};



#endif