#include "../include/Pong.hpp"

Pong::Pong()
{
    Music.setVolume(20);
}

Pong::~Pong(){}

void Pong::open()
{

    //create window
    sf::RenderWindow Window(sf::VideoMode(1280,720), "Pong", sf::Style::None);
    
    //Create Console
    createConsole(Window);
    
    //Create GamePlay
    Game.create(sf::Vector2f(Window.getSize()), sf::Vector2f(0.f,0.f));
    
    //Create Main Menu
    MainMenu.create(Window.getSize().x, Window.getSize().y);

    //Create Settings
    Settings.create(Window);

    while(Window.isOpen())
    {

        handleEvents(Window);

        //Cerate delta time
        tick = clock.restart().asSeconds();
        
        //Logic
        console.Update(Window);

        if(MainMenu.MenuShown)
        {
            if(!MenuMusic)
            {
                GamePlayMusic = false;
                Music.openFromFile("Resources/Sounds/MainMenuMusic.wav");
                Music.play();
                MenuMusic = true;
            }
            MainMenu.Pause = Game.GameInProgress;
            MainMenu.Update(Window);
        }
        else if(MainMenu.GamePlayShown)
        {
            if(!GamePlayMusic)
            {
                MenuMusic = false;
                Music.openFromFile("Resources/Sounds/GamePlayMusic.wav");
                Music.play();
                GamePlayMusic = true;
            }
            if(MainMenu.NewGameRequested)
            {
                Game.ResetGame();
                MainMenu.NewGameRequested = false;
            }
            Game.Update(Window, tick);
        }
        else if(MainMenu.SettingsShown)
        {
            Settings.Update(HumanSelected,AISelected);
            
            if(Settings.areSettingsChanged())
            {
                if(HumanSelected)
                    Game.changePlayerTwoToHuman();
                if(AISelected)
                    Game.changePlayerTwoToAI();

                Game.ResetGame();
            }
            
        }
        
        //Window display
        Window.clear();
        
        if(MainMenu.MenuShown)
            MainMenu.showTo(Window);
        else if(MainMenu.GamePlayShown)
            Game.ShowTo(Window);
        else if(MainMenu.SettingsShown)
        {
            Settings.ShowTo(Window);
        }
        
        //Console allways drawn last
        console.DisplayTo(Window);
        consoleCommands();
        Window.display();
    }
}

void Pong::handleEvents(sf::RenderWindow &Window)
{
    while(Window.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
                Window.close();
        if(ev.type == sf::Event::KeyReleased)
        {
            if(ev.key.code == sf::Keyboard::Tilde)
                console.ShowConsole();
            if(ev.key.code == sf::Keyboard::Escape)
            {
                MainMenu.MenuShown = true;
                MainMenu.GamePlayShown = false;
                MainMenu.SettingsShown = false;
                if(Game.isGameOver())
                {
                    Game.ResetGame();
                }
            }
            if(ev.key.code == sf::Keyboard::Space)
            {
                if(MainMenu.GamePlayShown)
                {
                    Game.LaunchBall();
                }
            }
        }
        console.typedOn(ev);
        console.CheckWheelMovement(ev);
    }
}  

void Pong::createConsole(sf::RenderWindow &Window)
{
    console.loadFontFromFile("Resources/Fonts/Cyberverse.otf");
    console.create(sf::Vector2f(5,5), sf::Vector2f(Window.getSize().x/2, Window.getSize().y*0.9), 30);
    console.setBoxColor(sf::Color(115,194,251));
    console.setTextColor(sf::Color::Black);
}

void Pong::consoleCommands()
{
    std::string commandLine = console.getCommand();
    if(!commandLine.empty())
    {
        std::string CommandName, ValueOne, ValueTwo;
        int i = 0;
        for(auto c: commandLine)
        {
            if(c == ' ')
            {
                i++;
                continue;
            }
            switch(i)
            {
            case 0:
                CommandName += c;
                break;
            case 1:
                ValueOne += c;
                break;
            case 2:
                ValueTwo += c;
                break;
            default:
                break;
            }
        }
        if(CommandName == "debug")
        {
            if(debug)
            {
                console << "Debug INACTIVE!";
                debug = false;
            }
            else
            {
                console << "Debug ACTIVE!";
                debug = true;
            }
        }
        else if(CommandName == "music" && debug)
        {
            if(ValueOne == "off")
            {
                console << "Music OFF!";
                Music.setVolume(0);
            }
            else if(ValueOne == "on")
            {
                console << "Music ON!";
                Music.setVolume(20);
            }
            else if(ValueOne == "setVolume")
            {
                bool valuefound = false;
                std::string value[11] = {"0","10","20","30","40","50","60","70","80","90","100"};
                for(auto v : value)
                {
                    if(ValueTwo == v)
                    {
                        int val;
                        std::stringstream ss;
                        ss << v;
                        ss >> val;
                        Music.setVolume(val);
                        console << "Music volume set to: " << v;
                        valuefound = true;
                    }
                }
                if(!valuefound)
                    console << "Invalid Volume value!";
            }
            else 
                console << "Enter a VALID music command!";
        }
        else
        {
            console << "Command NOT FOUND!";
        }
    }
    console.clearCommand();
}