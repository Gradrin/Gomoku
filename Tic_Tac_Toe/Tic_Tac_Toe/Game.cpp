#include "Game.h"

void Game::initVariables()
{
	this->stream.open(WINDOW);
	if (this->stream.is_open())
	{

		stream >> name;
		stream >> screen_x >> screen_y;
		stream >> frame;
		stream >> vsync;
	}
	this->stream.close();
	this->isConnected = false;

	WIDTH = screen_x;
	HEIGHT = screen_y;

	this->gameState = MAIN_MENU;
	online = new Online(gameState);
}

void Game::addWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(screen_x, screen_y), name);
		this->window->setFramerateLimit(frame);
	this->window->setVerticalSyncEnabled(vsync);
}

void Game::addBackground()
{
	this->texture = new sf::Texture();
	if (!this->texture->loadFromFile(BACKGROUND))
	{
		throw"ERROR";
	}

	this->background = new sf::Sprite;
	this->background->setTexture(*texture);
	
}

void Game::initFonts()
{
	this->font = new sf::Font;
	if (!this->font->loadFromFile(FONT))
	{
		std::cout << "FAILD" << "\n";
	}
}

void Game::addButtons()
{
	this->button["SINGLE PLAYER"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT*0.15, WIDTH * 0.3, HEIGHT * 0.1, "SINGLE PLAYER", 26);
	this->button["MULTIPLAYER"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.3, WIDTH * 0.3, HEIGHT * 0.1, "MULTIPLAYER", 26);
	this->button["RESOLUTION"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.45, WIDTH * 0.3, HEIGHT * 0.1, "RESOLUTION", 26);
	this->button["INTRODUCTION"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.6, WIDTH * 0.3, HEIGHT * 0.1, "INTRODUCTION", 26);
	this->button["EXIT"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.75, WIDTH * 0.3, HEIGHT * 0.1, "EXIT", 26);

}

Game::Game()
{
	this->initVariables();
	this->addWindow();
	this->addBackground();
	this->initFonts();
	this->addButtons();
}

Game::~Game()
{
	for (auto i : this->button)
	{
		delete i.second;
	}
	delete this->font;
	delete this->texture;
	delete this->background;
	delete this->window;
}

void Game::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Game::keyboardUpdate()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
	}
}


void Game::buttonsUpdate()
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
		if (this->button["SINGLE PLAYER"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				this->gameState = TYPEGAME;
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["MULTIPLAYER"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				this->gameState = MULTIPLAYER;
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["RESOLUTION"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				this->gameState = RESOLUTION;
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["INTRODUCTION"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				this->gameState = INTRODUCTION;
			}
		}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["EXIT"]->getBounds().contains(this->mousePosView))
		{
			this->window->close();
		}

}

void Game::update()
{
	this->mousePosition();
	this->keyboardUpdate();
	this->buttonsUpdate();
}

void Game::backgroundRender()
{
	this->window->draw(*background);
}

void Game::buttonsRender()
{
	for (auto i : this->button)
	{
		i.second->render(this->window);
	}
}

void Game::statusRender()
{
	if (this->gameState == TYPEGAME)
	{
		this->gameType = new TypeGame(window, background, mousePosWindow, mousePosView, font, gameState, texture, WIDTH, HEIGHT,online);
		while (gameState == TYPEGAME)
		{
			this->window->clear();
			this->gameType->update();
			this->gameType->render(window);
			this->gameType->buttonsRender();
			this->window->display();
		}
	}

	if (this->gameState == MULTIPLAYER)
	{
		this->multiplayer = new Multiplayer(window, background, mousePosWindow, mousePosView, font, gameState, WIDTH, HEIGHT,online);
		while (gameState == MULTIPLAYER)
		{
			this->window->clear();
			this->multiplayer->update();
			this->multiplayer->render(window);
			this->multiplayer->renderButton();
			this->window->display();
		}
	}
	if (this->gameState == RESOLUTION)
	{
		this->resolution = new Resolution(window, background, mousePosWindow, mousePosView, font, gameState,texture, WIDTH, HEIGHT);
		while (gameState == RESOLUTION)
		{
			this->window->clear();
			this->resolution->update();
			this->resolution->render(window);
			this->resolution->renderButton();
			this->window->display();
		}
	}

	if (this->gameState == INTRODUCTION)
	{
		this->introduction = new Introduction(window, background, mousePosWindow, mousePosView, font, gameState, WIDTH, HEIGHT);
		while (gameState == INTRODUCTION)
		{
		
			this->window->clear();
			this->introduction->update();
			this->introduction->render(window);
			this->introduction->renderButton();
			this->window->display();
		}
	}
}

void Game::render()
{
	this->window->clear();
	this->backgroundRender();
	this->buttonsRender();
	if (gameState != MAIN_MENU)
	this->statusRender();
	this->window->display();
}

void Game::run()
{
	std::thread connectionThread(&Online::ConnectClients, online);
	
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

