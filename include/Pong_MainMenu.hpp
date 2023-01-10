#ifndef PONGMENU_HPP
#define PONGMENU_HPP

#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_Button.hpp"
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_CheckBox.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Menu
{
public:

Menu();
~Menu();

void create(float Window_Width, float Window_Height);

void Update(sf::RenderWindow &Window);

void showTo(sf::RenderWindow &Window);

bool MenuShown = true;
bool GamePlayShown = false;
bool SettingsShown = false;
bool NewGameRequested = false;

bool Pause = false;

private:

sf::Text Title;
sf::Font font;

vui::Button NewGame;
vui::Button Play;
vui::Button Settings;
vui::Button Quit;


};

#endif