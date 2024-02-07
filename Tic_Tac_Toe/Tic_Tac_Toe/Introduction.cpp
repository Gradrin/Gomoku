#include "Introduction.h"

void Introduction::initText(sf::Font* font)
{
	this->std_text = "\nWelcome in Gomoku game.\n The game's rules are very simple. In game is two players:\n - First player play as O,\n - Second player as X.\n Everyone has self round and can put only his one sign on empty\n place in board. You have to put five sign in one line to win.\n If no one does this and the board will be full then is draw. ";
	
	this->text.setFont(*font);
	this->text.setString(std_text);
	this->text.setCharacterSize(34);
	this->text.setPosition(sf::Vector2f(WIDTH*0.1, HEIGHT*0.1));
}

void Introduction::addButtons(sf::Font* font)
{
	this->button = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.7, WIDTH * 0.3, HEIGHT * 0.1, "BACK", 26);

}

Introduction::Introduction(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i &mousePosWindow, sf::Vector2f &mousePosView, sf::Font* font, GameState& gameState, short& WIDTH, short& HEIGHT)
	:window(window),background(background),mousePosWindow(mousePosWindow),mousePosView(mousePosView),font(font), gameState(gameState), WIDTH(WIDTH), HEIGHT(HEIGHT)
{
	this->initText(font);
	this->addButtons(font);
}

Introduction::~Introduction()
{
	delete this->button;
}

void Introduction::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Introduction::keyboardUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			this->gameState = MAIN_MENU;
		}
	}
}

void Introduction::buttonUpdate()
{
	if (!button->getBounds().contains(this->mousePosView))
		button->setColor(button->getBasic());

	if (button->getBounds().contains(this->mousePosView))
		button->setColor(button->getIntersect());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (button->getBounds().contains(this->mousePosView))
			button->setColor(button->getClick());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button->getBounds().contains(this->mousePosView))
			this->gameState = MAIN_MENU;

	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
	}
}

void Introduction::update()
{
	this->mousePosition();
	this->keyboardUpdate();
	this->buttonUpdate();
}

void Introduction::render(sf::RenderTarget* target)
{
	target->draw(*background);
	target->draw(text);
	renderButton();
}

void Introduction::renderButton()
{

	this->button->render(window);
}
