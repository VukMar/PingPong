#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_Button.hpp"
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_CheckBox.hpp"

class SettingsPage
{
private:

vui::CheckBox AI_opponent;
vui::CheckBox Player_opponent;
sf::Text OpponentText;
sf::Text OpponentText1;
sf::Text OpponentText2;
sf::Font font;

bool settingsChanged = false;

public:

SettingsPage();
~SettingsPage();

void create(sf::RenderWindow &window);

void Update(bool &HumanOPSelected, bool &AIOPSelected);

bool areSettingsChanged();

void ShowTo(sf::RenderWindow &window);

};

#endif