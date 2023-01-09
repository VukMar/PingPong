#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "D:/VS Code Vuk/C++/SFMLUI/include/UI_Console.hpp"
#include "Pong_MainMenu.hpp"
#include "Pong_Game.hpp"
#include "Pong_Settings.hpp"

class Pong
{
public:

Pong();
~Pong();

void open();

private:

sf::Event ev;

float tick = 0;
sf::Clock clock;

bool debug = false;


sf::Music Music;

//Console Object
vui::Console console;

//Menu Object
bool MenuMusic = false;
Menu MainMenu;

//Game Object
bool GamePlayMusic = false;
GamePlay Game;

//Settings Object
bool HumanSelected = true;
bool AISelected = false;
SettingsPage Settings;

void handleEvents(sf::RenderWindow &Window);

void createConsole(sf::RenderWindow &Window);

void consoleCommands();

};