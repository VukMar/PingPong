#include "../include/Pong_Settings.hpp"

SettingsPage::SettingsPage()
{
    font.loadFromFile("Resources/Fonts/Cyberverse.otf");
}
SettingsPage::~SettingsPage(){}

void SettingsPage::create(sf::RenderWindow &window)
{
    sf::Vector2f winSize = sf::Vector2f(window.getSize());
    
    sf::Text t;
    t.setFont(font);
    t.setString("SETTINGS");
    t.setCharacterSize(60);
    t.setLetterSpacing(2);
    sf::FloatRect fr3 = t.getGlobalBounds();
    t.setOrigin(fr3.width/2,fr3.height/2);
    
    Title = t;
    Title.setPosition(winSize.x/2, 40);
    Title.setFillColor(sf::Color::Blue);
    Title.setOutlineColor(sf::Color::White);
    Title.setOutlineThickness(5);

    playerOneSettingsCreate(winSize);
    playerTwoSettingsCreate(winSize);
    
}

void SettingsPage::playerOneSettingsCreate(sf::Vector2f winSize)
{
    sf::Text t, t1 ,t2;
    
    t.setFont(font);
    t.setString("Player One Settings:");
    t.setCharacterSize(30);
    sf::FloatRect fr = t.getGlobalBounds();
    t.setOrigin(fr.width/2,fr.height/2);
    
    t1.setFont(font);
    t1.setString("HUMAN >> ");
    t1.setCharacterSize(30);
    sf::FloatRect fr1 = t1.getGlobalBounds();
    
    t2.setFont(font);
    t2.setString("   AI    >> ");
    t2.setCharacterSize(30);
    sf::FloatRect fr2 = t2.getGlobalBounds();

    OpponentText[0] = t;
    OpponentText[0].setPosition(winSize.x/4, 150);
    
    OpponentText1[0] = t1;
    OpponentText1[0].setPosition(OpponentText[0].getPosition().x - fr.width/2, 200);
    
    OpponentText2[0] = t2;
    OpponentText2[0].setPosition(OpponentText[0].getPosition().x - fr.width/2, 250);
    
    Player_opponent[0].create(30, sf::Vector2f(OpponentText1[0].getPosition().x + fr1.width, OpponentText1[0].getPosition().y),vui::Style::Circle);
    
    Player_opponent[0].checkBox();
    AI_opponent[0].create(30, sf::Vector2f(OpponentText2[0].getPosition().x + fr2.width, OpponentText2[0].getPosition().y),vui::Style::Circle);
}

void SettingsPage::playerTwoSettingsCreate(sf::Vector2f winSize)
{
    sf::Text t, t1 ,t2;
    
    t.setFont(font);
    t.setString("Player Two Settings:");
    t.setCharacterSize(30);
    sf::FloatRect fr = t.getGlobalBounds();
    t.setOrigin(fr.width/2,fr.height/2);
    
    t1.setFont(font);
    t1.setString("HUMAN >> ");
    t1.setCharacterSize(30);
    sf::FloatRect fr1 = t1.getGlobalBounds();
    
    t2.setFont(font);
    t2.setString("   AI    >> ");
    t2.setCharacterSize(30);
    sf::FloatRect fr2 = t2.getGlobalBounds();

    OpponentText[1] = t;
    OpponentText[1].setPosition(winSize.x - winSize.x/4, 150);
    
    OpponentText1[1] = t1;
    OpponentText1[1].setPosition(OpponentText[1].getPosition().x - fr.width/2, 200);
    
    OpponentText2[1] = t2;
    OpponentText2[1].setPosition(OpponentText[1].getPosition().x - fr.width/2, 250);
    
    Player_opponent[1].create(30, sf::Vector2f(OpponentText1[1].getPosition().x + fr1.width, OpponentText1[1].getPosition().y),vui::Style::Circle);
    
    Player_opponent[1].checkBox();
    AI_opponent[1].create(30, sf::Vector2f(OpponentText2[1].getPosition().x + fr2.width, OpponentText2[1].getPosition().y),vui::Style::Circle);
}

void SettingsPage::Update(bool &Human_Selected, bool &AI_Selected, Settings::Player player)
{
    int i = player;
    if(AI_opponent[i].isBoxChecked() && Human_Selected)
    {
        Player_opponent[i].uncheckBox();
    }
    if(Player_opponent[i].isBoxChecked() && AI_Selected)
    {
        AI_opponent[i].uncheckBox();
    }
    if(Human_Selected != Player_opponent[i].isBoxChecked())
    {
        settingsChanged = true;
        Human_Selected = Player_opponent[i].isBoxChecked();
    }
    if(AI_Selected != AI_opponent[i].isBoxChecked())
    {
        settingsChanged = true;
        AI_Selected = AI_opponent[i].isBoxChecked();
    }
}

bool SettingsPage::areSettingsChanged()
{
    if(settingsChanged)
    {
        settingsChanged = false;
        return true;
    }
    return false;
}

void SettingsPage::ShowTo(sf::RenderWindow &window)
{
    window.draw(Title);
    for(int i = 0; i < 2; i++)
    {
        AI_opponent[i].displayTo(window);
        Player_opponent[i].displayTo(window);
        window.draw(OpponentText[i]);
        window.draw(OpponentText1[i]);
        window.draw(OpponentText2[i]);
    }
}

