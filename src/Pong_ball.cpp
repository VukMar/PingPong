#include "../include/Pong_ball.hpp"

PongBall::PongBall()
{
    GsBuff.loadFromFile("Resources/Sounds/PlayerScores.wav");
    Goal.setBuffer(GsBuff);
}

PongBall::~PongBall(){}

 
void PongBall::create(float radius, sf::Color Color, sf::Vector2f PlayFieldSize, 
                sf::Vector2f PlayFieldStartPosition)
{
    r = radius;
    ball.setRadius(radius);
    ball.setFillColor(Color);
    ball.setOrigin(radius,radius);
    BallStartingPos = sf::Vector2f(PlayFieldStartPosition.x + (PlayFieldSize.x/2), PlayFieldStartPosition.y + (PlayFieldSize.y/2));
    ball.setPosition(BallStartingPos);
    PlayField = PlayFieldSize;
    PlayFieldStartPos = PlayFieldStartPosition;
}

void PongBall::launchBall()
{
    if(startingPos)
    {
        int dirAng[4] = {45, 135, 225, 315};
        srand(time(0));
        Angle = dirAng[rand()%4];
        dirVec.x = cos(rad(Angle));
        dirVec.y = sin(rad(Angle));
        startingPos = false;
    }
    moving = true;
}

void PongBall::pause()
{
    moving = false;
}

void PongBall::displayTo(sf::RenderWindow &Window)
{
    Window.draw(ball);
}

void PongBall::Update(PongPlayer p1, PongPlayer p2, float tick)
{
    if(moving)
    {
        ball.move(dirVec.x * tick * velocity, dirVec.y * tick * velocity);
    }
    if(BorderColision(tick) || TestColison(p1, tick) || TestColison(p2, tick))
    {
        dirVec = reflectedDir;
        if(hasSound)BounceSound.play();
    }
}

bool PongBall::addBouceSound(std::string FilePath)
{
    if(bsBuf.loadFromFile(FilePath))
    {
        BounceSound.setBuffer(bsBuf);
        BounceSound.setVolume(50);
        hasSound = true;
        return true;
    }
    return false;
}

sf::Vector2f PongBall::getPosition()
{
    return ball.getPosition();
}

bool PongBall::BorderColision(float tick)
{
    sf::Vector2f b = ball.getPosition();
    if(b.x + r >= PlayFieldStartPos.x + PlayField.x || b.x - r <= PlayFieldStartPos.x)
    {
        resetBall();
        (b.x - r <= PlayFieldStartPos.x)? leftGoal = true : rightGoal = true;
        ball.move(-(dirVec.x * tick * velocity), (dirVec.y * tick * velocity));
        Goal.play();
    }
    else if(b.y + r >= PlayFieldStartPos.y + PlayField.y || b.y - r <= PlayFieldStartPos.y)
    {  
        ball.move((dirVec.x * tick * velocity), -(dirVec.y * tick * velocity));
        nAngle = (b.y - r <= PlayFieldStartPos.y)? 90 : 270;
        sf::Vector2f nVec = sf::Vector2f(cos(rad(nAngle)), sin(rad(nAngle)));
        reflectedDir = CreateReflectedVector(dirVec, nVec);
        return true;   
    }
    return false;
}

bool PongBall::TestColison(PongPlayer &p, float tick)
{
    sf::Vector2f pointPos;
    sf::Vector2f pFirstPoint = sf::Vector2f(p.getPos().x - p.Size.x/2, p.getPos().y - p.Size.y/2);
    sf::Vector2f pLastPoint = sf::Vector2f(p.getPos().x + p.Size.x/2, p.getPos().y + p.Size.y/2);
    sf::Vector2f b = ball.getPosition();
    b.x += dirVec.x * velocity * tick;
    b.y += dirVec.y * velocity * tick;
    if(b.x > pFirstPoint.x - r && b.x < pFirstPoint.x && b.y > pFirstPoint.y - r && b.y < pLastPoint.y + r)
    {
        if(p.IsMovingUp())
            nAngle = 170;
        else if(p.isMovingDown())
            nAngle = 190;
        else
            nAngle = 180;
    } 
    else if(b.x > pLastPoint.x && b.x < pLastPoint.x + r && b.y > pFirstPoint.y - r && b.y < pLastPoint.y + r)
    {
        if(p.IsMovingUp())
            nAngle = 10;
        else if(p.isMovingDown())
            nAngle = 350;
        else
            nAngle = 360;
    } 
    else if(b.y < pFirstPoint.y && b.y > pFirstPoint.y - r && b.x > pFirstPoint.x - r && b.x < pLastPoint.x + r) 
    {
        nAngle = 270;
    }
    else if(b.y > pLastPoint.y && b.y < pLastPoint.y + r && b.x > pFirstPoint.x - r && b.x < pLastPoint.x + r)
    {
        nAngle = 90;
    }
    
    sf::Vector2f nVec = sf::Vector2f(cos(rad(nAngle)), sin(rad(nAngle)));
    reflectedDir = CreateReflectedVector(dirVec,nVec);
    
    if(b.x + r > pFirstPoint.x && b.x - r < pLastPoint.x && b.y + r > pFirstPoint.y && b.y - r < pLastPoint.y)
    {
        p.velocity += 20.f;
        velocity += 50.f;
        return true;
    }
    
    return false;
}

float PongBall::rad(int angle)
{
    return angle * M_PI/180;
}

float PongBall::dotProduct(sf::Vector2f a, sf::Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}

sf::Vector2f PongBall::CreateReflectedVector(sf::Vector2f d, sf::Vector2f n)
{
    return sf::Vector2f(d.x - 2*dotProduct(d, n) * n.x, d.y - 2*dotProduct(d, n) * n.y);
}

void PongBall::resetBall()
{
    velocity = 500.f;
    moving = false;
    ball.setPosition(BallStartingPos);
    startingPos = true;
}