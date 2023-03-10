#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_Button.hpp"
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_CheckBox.hpp"
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_Slider.hpp"

namespace Settings
{
    enum Player{ One = 0, Two = 1};
}


class SettingsPage
{
private:

sf::Font font;

sf::Text Title;

vui::CheckBox AI_opponent[2];
vui::CheckBox Player_opponent[2];

sf::Text OpponentText[2];
sf::Text OpponentText1[2];
sf::Text OpponentText2[2];

int iMusicVolume = 60;
sf::Text MusicSettings;
sf::Text MusicVolumeText;
vui::Slider MusicVolume;

bool settingsChanged = false;

public:

SettingsPage();
~SettingsPage();

void create(sf::RenderWindow &window);

void playerOneSettingsCreate(sf::Vector2f winSize);

void playerTwoSettingsCreate(sf::Vector2f winSize);

void musicSetingsCreate(sf::Vector2f winSize);

void UpdatePlayer(bool &Human_Selected, bool &AI_Selected, Settings::Player player);

void UpdateMusic(sf::Music &Music, sf::RenderWindow &window);

bool areSettingsChanged();

void ShowTo(sf::RenderWindow &window);

};

#endif