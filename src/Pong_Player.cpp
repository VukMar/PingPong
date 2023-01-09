#include "../include/Pong_Player.hpp"

PongPlayer::PongPlayer()
{

}

PongPlayer::~PongPlayer()
{

}

sf::Vector2f PongPlayer::getPos()
{
    return p.getPosition();
}

void PongPlayer::create(sf::Vector2f PlayerSize, sf::Color Color, Player::ID id, 
                        sf::Vector2f PlayFieldSize, 
                        sf::Vector2f PlayFieldStartPosition)
{
    PlayField = PlayFieldSize;
    PlayFiledPos = PlayFieldStartPosition;
    pID = id;
    Size = PlayerSize;
    p.setSize(Size);
    p.setOrigin(Size.x/2, Size.y/2);
    float posx=(pID == Player::ID::One)? PlayFieldStartPosition.x + 20 : PlayFieldStartPosition.x + PlayFieldSize.x - 20;
    p.setPosition(posx, PlayFieldStartPosition.y + PlayFieldSize.y/2);
    p.setFillColor(Color);
    UP = (pID == Player::ID::One)? sf::Keyboard::W : sf::Keyboard::Up;
    DOWN = (pID == Player::ID::One)? sf::Keyboard::S : sf::Keyboard::Down;
}

void PongPlayer::displayTo(sf::RenderWindow &Window)
{
    Window.draw(p);
}

void PongPlayer::playerUpdate(float tick)
{
    speed = velocity * tick;
    if((!isAI)? sf::Keyboard::isKeyPressed(UP) : ButtonUpPressed)
    {
        p.move(0.f, -speed);
        if(getPos().y - p.getSize().y/2 < PlayFiledPos.y){
            p.move(0.f, speed);
        }
        MovingUp = true;
    }
    else
        MovingUp = false;
    
    if((!isAI)? sf::Keyboard::isKeyPressed(DOWN) : ButtonDownPressed)
    {
        p.move(0.f, speed);
        if(getPos().y + p.getSize().y/2 > PlayFiledPos.y + PlayField.y)
        {
            p.move(0.f, -speed);
        }
        MovingDown = true;
        
    }
    else 
        MovingDown = false;
    
    if(hasSound)
    {
        (MovingUp || MovingDown)? MoveSound.setVolume(70) : MoveSound.setVolume(0);
    }
}

void PongPlayer::addTexture(sf::Texture &Texture)
{
    p.setTexture(&Texture);
}

void PongPlayer::setMovementSound(std::string FilePath)
{
    if(Soundbuf.loadFromFile(FilePath))
    {
        MoveSound.setBuffer(Soundbuf);
        MoveSound.setLoop(true);
        MoveSound.setVolume(0);
        MoveSound.play();
        hasSound = true;
    }
}

bool PongPlayer::IsMovingUp()
{
    return MovingUp;
}

bool PongPlayer::isMovingDown()
{
    return MovingDown;
}