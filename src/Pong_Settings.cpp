#include "../include/Pong_Settings.hpp"

SettingsPage::SettingsPage()
{
    font.loadFromFile("Resources/Fonts/Cyberverse.otf");
}
SettingsPage::~SettingsPage(){}

void SettingsPage::create(sf::RenderWindow &window)
{
    sf::Vector2f winSize = sf::Vector2f(window.getSize());
    
    sf::Text t, t1 ,t2, t3;
    
    t.setFont(font);
    t.setString("SELECT OPPONENT:");
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

    t3.setFont(font);
    t3.setString("SETTINGS");
    t3.setCharacterSize(60);
    t3.setLetterSpacing(2);
    sf::FloatRect fr3 = t3.getGlobalBounds();
    t3.setOrigin(fr3.width/2,fr3.height/2);
    
    Title = t3;
    Title.setPosition(winSize.x/2, 40);
    Title.setFillColor(sf::Color::Blue);
    Title.setOutlineColor(sf::Color::White);
    Title.setOutlineThickness(5);

    OpponentText = t;
    OpponentText.setPosition(winSize.x/4, 150);
    
    OpponentText1 = t1;
    OpponentText1.setPosition(OpponentText.getPosition().x - fr.width/2, 200);
    
    OpponentText2 = t2;
    OpponentText2.setPosition(OpponentText.getPosition().x - fr.width/2, 250);
    
    Player_opponent.create(30, sf::Vector2f(OpponentText1.getPosition().x + fr1.width, OpponentText1.getPosition().y),vui::Style::Circle);
    
    Player_opponent.checkBox();
    AI_opponent.create(30, sf::Vector2f(OpponentText2.getPosition().x + fr2.width, OpponentText2.getPosition().y),vui::Style::Circle);
}

void SettingsPage::Update(bool &HumanOPSelected, bool &AIOPSelected)
{
    if(AI_opponent.isBoxChecked() && HumanOPSelected)
    {
        Player_opponent.uncheckBox();
    }
    if(Player_opponent.isBoxChecked() && AIOPSelected)
    {
        AI_opponent.uncheckBox();
    }
    if(HumanOPSelected != Player_opponent.isBoxChecked())
    {
        settingsChanged = true;
        HumanOPSelected = Player_opponent.isBoxChecked();
    }
    if(AIOPSelected != AI_opponent.isBoxChecked())
    {
        settingsChanged = true;
        AIOPSelected = AI_opponent.isBoxChecked();
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
    AI_opponent.displayTo(window);
    Player_opponent.displayTo(window);
    window.draw(OpponentText);
    window.draw(OpponentText1);
    window.draw(OpponentText2);
}

