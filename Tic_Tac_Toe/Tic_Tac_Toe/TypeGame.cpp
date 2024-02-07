#include "TypeGame.h"


void TypeGame::addVariables()
{
	this->variable = new int(0);
}

void TypeGame::addButtons(sf::Font* font)
{
	this->button["BASIC"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.15, WIDTH * 0.3, HEIGHT * 0.1, "BASIC", 26);
	this->button["BEST OF THREE"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.3, WIDTH * 0.3, HEIGHT * 0.1, "BEST OF THREE", 26);
	this->button["BEST OF FIVE"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.45, WIDTH * 0.3, HEIGHT * 0.1, "BEST OF FIVE", 26);
	this->button["BEST OF SEVEN"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.6, WIDTH * 0.3, HEIGHT * 0.1, "BEST OF SEVEN", 26);
	this->button["BACK"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.75, WIDTH * 0.3, HEIGHT * 0.1, "BACK", 26);

}

TypeGame::TypeGame(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, sf::Texture* texture, short& WIDTH, short& HEIGHT, Online* online)
	:window(window), background(background), mousePosWindow(mousePosWindow), mousePosView(mousePosView), font(font), gameState(gameState), texture(texture), WIDTH(WIDTH), HEIGHT(HEIGHT), online(online)
{
	this->addVariables();
	this->addButtons(font);
}

TypeGame::~TypeGame()
{
	for (auto i : this->button)
	{
		delete i.second;
	}
	delete this->variable;
}

void TypeGame::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void TypeGame::keyUptade()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
	}
}

void TypeGame::buttonUpdate()
{
	for (auto i : this->button)
	{
		if (!i.second->getBounds().contains(this->mousePosView))
			i.second->setColor(i.second->getBasic());

		if (i.second->getBounds().contains(this->mousePosView))
			i.second->setColor(i.second->getIntersect());

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			if (i.second->getBounds().contains(this->mousePosView))
				i.second->setColor(i.second->getClick());
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["BASIC"]->getBounds().contains(this->mousePosView))
		{
			*this->variable = BASIC;
			this->gameState = START;
			online->packet << 1;
			online->hostSocket.send(online->packet);			
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["BEST OF THREE"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				*this->variable = BEST_OF_THREE;
				this->gameState = START;
				online->packet << 1;
				sf::Socket::Status sendStatus=online->hostSocket.send(online->packet);
				if (sendStatus != sf::Socket::Done) {
					std::cerr << "Failed to send data: " << sendStatus << std::endl;
				}
				else {
					std::cout << "Data sent successfully" << std::endl;
				}
				
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["BEST OF FIVE"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				*this->variable = BEST_OF_FIVE;
				this->gameState = START;
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["BEST OF SEVEN"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				*this->variable = BEST_OF_SEVEN;
				this->gameState = START;
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["BACK"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
			this->gameState = MAIN_MENU;
			}
		}
}

void TypeGame::update()
{
	this->mousePosition();
	this->keyUptade();
	this->buttonUpdate();
}

void TypeGame::startGame(int *variable)
{
	this->start[*variable] = new Start(window, background, mousePosWindow, mousePosView, font, gameState, texture, variable, WIDTH, HEIGHT);
	while (gameState == START)
	{
		this->window->clear();
		this->start[*variable]->update();
		this->start[*variable]->render(window);
		this->window->display();
	}
}

void TypeGame::render(sf::RenderTarget* target)
{
	target->draw(*background);
}

void TypeGame::buttonsRender()
{
	for (auto i : this->button)
	{
		i.second->render(this->window);
	}
	if (gameState == START)
		this->startGame(variable);
}
