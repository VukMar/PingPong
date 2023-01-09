#include "../include/Pong_Settings.hpp"

SettingsPage::SettingsPage()
{
    font.loadFromFile("Resources/Fonts/Cyberverse.otf");
}
SettingsPage::~SettingsPage(){}

void SettingsPage::create(sf::RenderWindow &window)
{
    sf::Vector2f winSize = sf::Vector2f(window.getSize());
    sf::Text t, t1 ,t2;
    t.setFont(font);
    t.setString("SELECT OPPONENT:");
    t.setCharacterSize(30);
    sf::FloatRect fr = t.getGlobalBounds();
    t.setOrigin(fr.width/2,fr.height/2);
    t1.setFont(font);
    t1.setString("HUMAN >> ");
    t1.setCharacterSize(30);
    sf::FloatRect fr1 = t1.getGlobalBounds();
    t1.setOrigin(fr1.width/2,fr1.height/2);
    t2.setFont(font);
    t2.setString("AI >> ");
    t2.setCharacterSize(30);
    sf::FloatRect fr2 = t2.getGlobalBounds();
    t2.setOrigin(fr2.width/2,fr2.height/2);
    OpponentText = t;
    OpponentText1 = t1;
    OpponentText2 = t2;
    OpponentText.setPosition(winSize.x/2, winSize.y/2 - 120);
    OpponentText1.setPosition(winSize.x/2, winSize.y/2 - 60);
    OpponentText2.setPosition(winSize.x/2, winSize.y/2 - 0);
    Player_opponent.create(30, sf::Vector2f(winSize.x/2+fr1.width/2, OpponentText1.getPosition().y-fr1.height/2),vui::Style::Circle);
    Player_opponent.checkBox();
    AI_opponent.create(30, sf::Vector2f(winSize.x/2+fr2.width/2, OpponentText2.getPosition().y-fr2.height/2),vui::Style::Circle);
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
    AI_opponent.displayTo(window);
    Player_opponent.displayTo(window);
    window.draw(OpponentText);
    window.draw(OpponentText1);
    window.draw(OpponentText2);
}

