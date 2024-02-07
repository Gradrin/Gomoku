#pragma once
#include"Button.h"
#include"GameState.h"

extern enum buttons;

class Introduction
{
private:
	sf::RenderWindow* window;
	sf::Sprite* background;
	sf::Font* font;

	sf::Vector2i &mousePosWindow;
	sf::Vector2f &mousePosView;

	sf::Event ev;
	sf::Text text;
	std::string std_text;

	Button* button;
	GameState& gameState;

	short& HEIGHT;
	short& WIDTH;

	//Constructor's functions
	void initText(sf::Font* font);
	void addButtons(sf::Font* font);

public:
	Introduction(sf::RenderWindow* window,sf::Sprite *background, sf::Vector2i &mousePosWindow, sf::Vector2f &mousePosView, sf::Font* font, GameState& gameState, short& WIDTH, short& HEIGHT);
	~Introduction();

	//introduction update
	void mousePosition();
	void keyboardUpdate();
	void buttonUpdate();
	void update();


	//introduction render
	void render(sf::RenderTarget *target);
	void renderButton();
};

