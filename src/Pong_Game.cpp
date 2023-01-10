#include "../include/Pong_Game.hpp"

GamePlay::GamePlay()
{
    font.loadFromFile("Resources/Fonts/Cyberverse.otf");
    Score.setFont(font);
}
GamePlay::~GamePlay(){}

void GamePlay::create(sf::Vector2f PlayfieldSize, sf::Vector2f PlayfieldPosition)
{
    PlayField = PlayfieldSize;
    PlayFieldPos = PlayfieldPosition;
    
    pOne.create(sf::Vector2f(20,200), sf::Color::Blue, Player::ID::One, PlayfieldSize, PlayfieldPosition);
    pOne.velocity = 700.f;
    
    pTwo.create(sf::Vector2f(20,200), sf::Color::Blue, Player::ID::Two, PlayfieldSize, PlayfieldPosition);
    pTwo.velocity = 700.f;
    
    ball.create(10,sf::Color::Blue, PlayfieldSize, PlayfieldPosition);
    ball.resetBall();
}

void GamePlay::Update(sf::RenderWindow &window, float tick)
{
    if(GameOver)
    {
        UpdateGameOver();
    }
    else
    {
        if(pTwo.isAI)
        {
            if(ball.getPosition().y > pTwo.getPos().y)
                pTwo.ButtonDownPressed = true;
            else
                pTwo.ButtonDownPressed = false;
            if(ball.getPosition().y < pTwo.getPos().y)
                pTwo.ButtonUpPressed = true;
            else
                pTwo.ButtonUpPressed = false;
        }
        if(pOne.isAI)
        {
            if(ball.getPosition().y > pOne.getPos().y)
                pOne.ButtonDownPressed = true;
            else
                pOne.ButtonDownPressed = false;
            if(ball.getPosition().y < pOne.getPos().y)
                pOne.ButtonUpPressed = true;
            else
                pOne.ButtonUpPressed = false;
        }
        pOne.playerUpdate(tick);
        pTwo.playerUpdate(tick);
        ball.Update(pOne, pTwo, tick);
        HandleScore();
    }
}

void GamePlay::ShowTo(sf::RenderWindow &Window)
{
    if(GameOver)
    {
        Window.draw(GameOverText);
    }
    else
    {
        pOne.displayTo(Window);
        pTwo.displayTo(Window);
        ball.displayTo(Window);
        Window.draw(Score);
    }
}

void GamePlay::LaunchBall()
{
    if(!GameInProgress)
    {
        GameInProgress = true;
    }
    ball.launchBall();
}

void GamePlay::changePlayerOneToAI()
{
    pOne.isAI = true;
}

void GamePlay::changePlayerTwoToAI()
{
    pTwo.isAI = true;
}

void GamePlay::changePlayerOneToHuman()
{
    pOne.isAI = false;
}

void GamePlay::changePlayerTwoToHuman()
{
    pTwo.isAI = false;
}

void GamePlay::ResetGame()
{
    pOneScore = 0;
    pTwoScore = 0;
    GameInProgress = false;
    GameOver = false;
    create(PlayField, PlayFieldPos);
}

bool GamePlay::isGameOver()
{
    return GameOver;
}

void GamePlay::HandleScore()
{
    std::stringstream ss;
    if(ball.leftGoal)
    {
        pTwoScore += 1;
        ball.leftGoal = false;
    }
    else if(ball.rightGoal)
    {
        pOneScore += 1;
        ball.rightGoal = false;
    }
    ss << pOneScore << " : " << pTwoScore;
    ScoreText = ss.str();
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(50);
    t.setString(ScoreText);
    sf::FloatRect fr = t.getGlobalBounds();
    t.setOrigin(fr.width/2,fr.top/2);
    t.setPosition(PlayField.x/2 + PlayFieldPos.x, PlayFieldPos.y + 60);
    Score = t;
    if(pOneScore >= 3 && pOneScore - pTwoScore > 1)
    {
        GameOver = true;
    }
    else if(pTwoScore >= 3 && pTwoScore - pOneScore > 1)
    {
        GameOver = true;
    }
}

void GamePlay::UpdateGameOver()
{
    std::string GameOverString;
    if(pOneScore > pTwoScore)
        GameOverString = "GAME OVER!\nPLAYER ONE WINS!\nPress ESC to Return to MAIN MENU!";
    else if(pOneScore < pTwoScore)
        GameOverString = "GAME OVER!\nPLAYER TWO WINS!\nPress ESC to Return to MAIN MENU!";
    else
        GameOverString = "GAME OVER!\nIT'S A DRAW!\nPress ESC to Return to MAIN MENU!";
    sf::Text t;
    t.setFont(font);
    t.setCharacterSize(30);
    t.setString(GameOverString);
    sf::FloatRect fr = t.getGlobalBounds();
    t.setOrigin(fr.width/2,fr.top/2);
    t.setPosition(PlayField.x/2 + PlayFieldPos.x, PlayField.y/2 + PlayFieldPos.y);
    GameOverText = t;
}