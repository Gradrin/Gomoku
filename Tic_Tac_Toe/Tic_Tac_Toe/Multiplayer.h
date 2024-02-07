#pragma once
#include"Button.h"
#include"Online.h"
#include"GameState.h"

class Multiplayer
{
private:

	sf::RenderWindow* window;
	sf::Sprite* background;

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	enum LineEdit { IP, PORT };

	struct
	{
		bool isClicked;
		float x_position;
		float y_position;
		float x_size;
		float y_size;
		sf::Text text;
		sf::Text textName;
		std::string characters;
		std::string name;
		sf::String textInput;
		sf::RectangleShape shape;
	}lineEdit[2];

	unsigned short mn;

	sf::Event ev;

	Online* online;

	GameState& gameState;

	sf::Font* font;

	bool isClicked;

	short& WIDTH;
	short& HEIGHT;

	std::map<std::string, Button*> button;

	//Constructor's functions
	void variables();
	void addLineEdits(sf::Font* font);
	void addButtons(sf::Font* font);

public:
	Multiplayer(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, short& WIDTH, short& HEIGHT, Online* online);
	~Multiplayer();

	//update functions
	void mousePosition();
	void keyboardUpdate();
	void buttonUpdate();
	void lineEditsUpdate();
	void update();

	//render functions
	void render(sf::RenderTarget* target);
	void renderButton();

};

