#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include<map>
#include<stack>
#include <chrono>
#include <thread>
#include<string.h>
#include<fstream>

#include"Button.h"
#include"GameState.h"
#include"Introduction.h"
#include"Start.h"
#include"TypeGame.h"
#include"Multiplayer.h"
#include "resources.h"
#include"Resolution.h"
#include"GameState.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::Font* font;
	sf::Sprite *background;
	sf::Texture *texture;
	std::fstream stream;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	short HEIGHT;
	short WIDTH;

	int screen_x;
	int	screen_y;
	int frame;
	bool vsync;


	std::string name;

	std::map<std::string, Button*> button;

	GameState gameState;
	Introduction *introduction;
	Start* start;
	TypeGame *gameType;
	Multiplayer* multiplayer;
	Resolution* resolution;


	sf::TcpSocket socket;

	bool isConnected;

	Online* online;


	//Constructor's functions
	void initVariables();
	void addWindow();
	void addBackground();
	void initFonts();
	void addButtons();

public:
	Game();
	virtual ~Game();

	//update functions
	void mousePosition();
	void keyboardUpdate();
	void buttonsUpdate();
	void update();
	
	//render functions
	void backgroundRender();
	void buttonsRender();
	void statusRender();
	void render();

	void run();
};

