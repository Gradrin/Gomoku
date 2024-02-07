#include "StatsWindow.h"

void StatsWindow::initText()
{
	this->std_text = "THIS GAME WON PLAYER PLAYED AS:";

	if (this->circlePoints == *this->variable)
	{
		if (!this->sign.loadFromFile(CIRCLE_WIN))
		{
			throw"ERROR";
		}
		this->backgroundSign = new sf::Sprite;
		this->backgroundSign->setTexture(sign);
		
	}
	else
	{
		if (!this->sign.loadFromFile(CROSS_WIN))
		{
			throw"ERROR";
		}
		this->backgroundSign = new sf::Sprite;
		this->backgroundSign->setTexture(sign);

	}

	this->text.setFont(*font);
	this->text.setString(std_text);
	this->text.setCharacterSize(34);
	this->text.setPosition(sf::Vector2f(250.f, 200.f));

}

void StatsWindow::addButtons()
{
	this->button["PLAY AGAIN"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.15, WIDTH * 0.3, HEIGHT * 0.1, "PLAY AGAIN", 26);
	this->button["BACK"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.3, WIDTH * 0.3, HEIGHT * 0.1, "BACK", 26);
}

StatsWindow::StatsWindow(sf::RenderWindow* window, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, int* variable, int& circlePoints, int& crossPoints, GameState& gameState,short& WIDTH, short& HEIGHT)
	:window(window), mousePosWindow(mousePosWindow), mousePosView(mousePosView), font(font),variable(variable),circlePoints(circlePoints),crossPoints(crossPoints),gameState(gameState), WIDTH(WIDTH), HEIGHT(HEIGHT)
{
	this->initText();
	this->addButtons();
}

StatsWindow::~StatsWindow()
{
	for (auto i : this->button)
	{
		delete i.second;
	}
	delete this->backgroundSign;

}

void StatsWindow::updateKeyboard()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
	}
}

void StatsWindow::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void StatsWindow::buttonsUpdate()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button["BACK"]->getBounds().contains(this->mousePosView))
			this->gameState = MAIN_MENU;

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->button["PLAY AGAIN"]->getBounds().contains(this->mousePosView))
			this->gameState = START;

	}
	
}

void StatsWindow::update()
{
	this->updateKeyboard();
	this->mousePosition();
	this->buttonsUpdate();
}

void StatsWindow::render(sf::RenderTarget* target)
{
	target->draw(*backgroundSign);
	target->draw(text);


}

void StatsWindow::buttonsRender()
{
	for (auto i : this->button)
	{
		i.second->render(window);
	}
}
