#pragma once

#include<map>

#include"Button.h"
#include"resources.h"
#include"GameState.h"

class StatsWindow
{
private:
	sf::RenderWindow* window;
	sf::Sprite *backgroundSign;
	sf::Sprite* background;
	sf::Texture sign;
	sf::Font* font;
	sf::Text text;
	std::string std_text;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	sf::Event ev;

	std::map<std::string,Button*>button;

	int circlePoints;
	int crossPoints;
	int* variable;

	short& WIDTH;
	short& HEIGHT;

	GameState& gameState;

	//Constructor's functions
	void initText();
	void addButtons();

public:
	StatsWindow(sf::RenderWindow* window, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, int* variable, int& circlePoints, int& crossPoints, GameState& gameState, short& WIDTH, short& HEIGHT);
	~StatsWindow();

	//update functions
	void updateKeyboard();
	void mousePosition();
	void buttonsUpdate();
	void update();

	//render functions
	void render(sf::RenderTarget* target);
	void buttonsRender();
};

