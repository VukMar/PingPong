#ifndef PONGGAME_HPP
#define PONGGAME_HPP

#include "Pong_ball.hpp"
#include "Pong_Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

namespace pong
{
    enum Player{one = 1, two = 2};
}

class GamePlay
{
public:

bool GameInProgress = false;

GamePlay();
~GamePlay();

void create(sf::Vector2f PlayfieldSize, sf::Vector2f PlayfieldPosition);

void Update(sf::RenderWindow &window, float tick);

void ShowTo(sf::RenderWindow &Window);

void LaunchBall();

void changePlayerOneToAI();

void changePlayerTwoToAI();

void changePlayerOneToHuman();

void changePlayerTwoToHuman();

void ResetGame();

bool isGameOver();

private:

bool PlayerOneisAI = false;
bool PlayerTwoisAI = false;

bool GameOver = false;

sf::Vector2f PlayField;
sf::Vector2f PlayFieldPos;

int pOneScore = 0;
int pTwoScore = 0;

sf::Font font;
sf::Text Score;
std::string ScoreText;

sf::Text GameOverText;

PongBall ball;
PongPlayer pOne;
PongPlayer pTwo;

void HandleScore();

void UpdateGameOver();

};

#endif