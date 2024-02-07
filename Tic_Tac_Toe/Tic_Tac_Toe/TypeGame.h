#pragma once

#include<map>

#include"Button.h"
#include"Start.h"
#include"Online.h"

extern enum type;
extern enum buttons;

class TypeGame
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::Font* font;
	sf::Sprite* background;
	sf::Texture* texture;

	sf::Vector2i &mousePosWindow;
	sf::Vector2f &mousePosView;

	std::map<std::string,Button*> button;
	std::map<int, Start*> start;

	int* variable;

	GameState& gameState;
	Online* online;

	short &HEIGHT;
	short &WIDTH;

	//Constructor's functions
	void addVariables();
	void addButtons(sf::Font* font);

public:
	TypeGame(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, sf::Texture* texture, short &WIDTH,short &HEIGHT, Online* online);
	virtual ~TypeGame();

	//update functions
	void mousePosition();
	void keyUptade();
	void buttonUpdate();
	void startGame(int* variable);
	void update();

	//render functions
	void render(sf::RenderTarget *target);
	void buttonsRender();
};

