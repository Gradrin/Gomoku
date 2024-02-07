#pragma once
#include<fstream>
#include"Button.h"
#include"GameState.h"
#include"resources.h"

extern enum buttons;

class Resolution
{
private:
	sf::RenderWindow* window;
	sf::Texture* texture;
	sf::Sprite* background;

	sf::Vector2i &mousePosWindow;
	sf::Vector2f &mousePosView;

	sf::Font* font;
	sf::Text text;
	sf::Event ev;

	std::fstream strim;

	short &HEIGHT;
	short &WIDTH;

	std::map<std::string, Button*> button;

	GameState& gameState;

	//Constructor's functions
	void variables();
	void addButtons(sf::Font* font);

public:
	Resolution(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState,sf::Texture *texture, short& WIDTH, short& HEIGHT);
	~Resolution();

	//update functions
	void mousePosition();
	void keyboardUpdate();
	void buttonFunction(const int& width, const int& height);
	void buttonUpdate();
	void update();


	//render functions
	void render(sf::RenderTarget* target);
	void renderButton();

};

