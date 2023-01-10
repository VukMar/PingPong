#include "../include/Pong_MainMenu.hpp"

Menu::Menu()
{
    font.loadFromFile("Resources\\Fonts\\Cyberverse.otf");
}
Menu::~Menu(){}

void Menu::create(float Window_Width, float Window_Height)
{
    sf::Vector2f winCenter = sf::Vector2f(Window_Width/2, Window_Height/2);
    
    sf::Text t;
    t.setCharacterSize(180);
    t.setFont(font);
    t.setString("PONG");
    t.setLetterSpacing(3);
    sf::FloatRect fr = t.getGlobalBounds();
    t.setOrigin(fr.width/2,fr.height/2);
    Title = t;
    Title.setFillColor(sf::Color::Blue);
    Title.setOutlineThickness(5);
    Title.setOutlineColor(sf::Color::White);
    Title.setPosition(winCenter.x, 90);


    NewGame.loadFontFromFile("Resources/Fonts/Cyberverse.otf");
    NewGame.create("NEW GAME", 30, sf::Vector2f(300, 50), sf::Vector2f(winCenter.x-150, winCenter.y-100), sf::Color::Transparent, sf::Color::Blue);

    Play.loadFontFromFile("Resources/Fonts/Cyberverse.otf");
    Play.create("PLAY", 30, sf::Vector2f(300, 50), sf::Vector2f(winCenter.x-150, winCenter.y), sf::Color::Transparent, sf::Color::Blue);
    Play.changeButtonOutlineColor(sf::Color::Blue);

    Settings.loadFontFromFile("Resources/Fonts/Cyberverse.otf");
    Settings.create("SETINGS", 30, sf::Vector2f(300, 50), sf::Vector2f(winCenter.x-150, winCenter.y + 100), sf::Color::Transparent, sf::Color::Blue);
    Settings.changeButtonOutlineColor(sf::Color::Blue);

    Quit.loadFontFromFile("Resources/Fonts/Cyberverse.otf");
    Quit.create("QUIT", 30, sf::Vector2f(300, 50), sf::Vector2f(winCenter.x-150, winCenter.y + 200), sf::Color::Transparent, sf::Color::Blue);
    Quit.changeButtonOutlineColor(sf::Color::Blue);

}

void Menu::Update(sf::RenderWindow &Window)
{
    //Change new game button visuals based on Pause
    if(!Pause)
    {
        NewGame.changeButtonHoverColor(sf::Color::Transparent);
        NewGame.changeButtonColor(sf::Color::Transparent);
        NewGame.changeButtonOutlineColor(sf::Color::Transparent);
        NewGame.changeButtonTextColor(sf::Color(107,107,107));
    }
    else if(Pause)
    {
        NewGame.changeButtonHoverColor(sf::Color::Blue);
        NewGame.changeButtonColor(sf::Color::Transparent);
        NewGame.changeButtonOutlineColor(sf::Color::Blue);
        NewGame.changeButtonTextColor(sf::Color::White);
    }
    if(NewGame.isButtonPressed(Window))
    {
        if(Pause)
        {
            MenuShown = false;
            GamePlayShown = true;
            SettingsShown = false;
            NewGameRequested = true;
        }
    }
    else if(Play.isButtonPressed(Window))
    {
        MenuShown = false;
        GamePlayShown = true;
        SettingsShown = false;
    }
    else if(Settings.isButtonPressed(Window))
    {
        MenuShown = false;
        GamePlayShown = false;
        SettingsShown = true;
    }
    else if(Quit.isButtonPressed(Window))
    {
        Window.close();
    }
}

void Menu::showTo(sf::RenderWindow &Window)
{
    Window.draw(Title);
    NewGame.displayTo(Window);
    Play.displayTo(Window);
    Settings.displayTo(Window);
    Quit.displayTo(Window);
}