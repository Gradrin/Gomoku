#include "Resolution.h"

void Resolution::variables()
{

}

void Resolution::addButtons(sf::Font* font)
{
	this->button["3840 x 2160"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.15, WIDTH * 0.3, HEIGHT * 0.1, "3840 x 2160", 26);
	this->button["2560 x 1440"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.3, WIDTH * 0.3, HEIGHT * 0.1, "2560 x 1440", 26);
	this->button["1920 x 1080"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.45, WIDTH * 0.3, HEIGHT * 0.1, "1920 x 1080", 26);
	this->button["1024 x 768"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.6, WIDTH * 0.3, HEIGHT * 0.1, "1024 x 768", 26);
	this->button["800 x 600"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.75, WIDTH * 0.3, HEIGHT * 0.1, "800 x 600", 26);
	this->button["BACK"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.9, WIDTH * 0.3, HEIGHT * 0.1, "BACK", 26);
}

Resolution::Resolution(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, sf::Texture* texture, short& WIDTH, short& HEIGHT)
	:window(window), background(background), mousePosWindow(mousePosWindow), mousePosView(mousePosView), font(font), gameState(gameState),texture(texture), WIDTH(WIDTH), HEIGHT(HEIGHT)
{
	this->variables();
	this->addButtons(font);
}


Resolution::~Resolution()
{
	for (auto i : this->button)
	{
		delete i.second;
	}
}

void Resolution::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Resolution::keyboardUpdate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			this->gameState = MAIN_MENU;
		}
	}

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
		if (this->button["3840 x 2160"]->getBounds().contains(this->mousePosView))
		{
			buttonFunction(3840, 2160);
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button["2560 x 1440"]->getBounds().contains(this->mousePosView))
		{
			buttonFunction(2560, 1440);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button["1920 x 1080"]->getBounds().contains(this->mousePosView))
		{
			buttonFunction(1920, 1080);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button["1024 x 768"]->getBounds().contains(this->mousePosView))
		{
			buttonFunction(1024, 768);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button["800 x 600"]->getBounds().contains(this->mousePosView))
		{
			buttonFunction(800, 600);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["BACK"]->getBounds().contains(this->mousePosView))
			this->gameState = MAIN_MENU;
}

void Resolution::buttonFunction(const int& width, const int& height)
{
		window->waitEvent(ev);
		if (ev.type == sf::Event::MouseButtonReleased)
		{
			this->strim.open(WINDOW);

			strim << "Tic_Tac_Toe\n";
			strim << width << " " << height << "\n";
			strim << 60 << "\n";
			strim << 0 << "\n";

			this->strim.close();
			window->setSize(sf::Vector2u(width,height));
		}
}

void Resolution::buttonUpdate()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
	}
}

void Resolution::update()
{
	this->mousePosition();
	this->keyboardUpdate();
	this->buttonUpdate();
}

void Resolution::render(sf::RenderTarget* target)
{
	target->draw(*background);
}

void Resolution::renderButton()
{
	for (auto i : this->button)
	{
		i.second->render(this->window);
	}
}
