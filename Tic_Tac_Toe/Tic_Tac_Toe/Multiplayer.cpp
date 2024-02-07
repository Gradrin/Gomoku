#include "Multiplayer.h"



void Multiplayer::variables()
{
	this->lineEdit[IP].isClicked = false;
	this->lineEdit[PORT].isClicked = false;

	this->lineEdit[IP].x_size = 300.f;
	this->lineEdit[IP].y_size = 50.f;
	this->lineEdit[IP].x_position = WIDTH / 2 - this->lineEdit[IP].x_size / 2;
	this->lineEdit[IP].y_position = HEIGHT*0.5;

	this->lineEdit[PORT].x_size = 300.f;
	this->lineEdit[PORT].y_size = 50.f;
	this->lineEdit[PORT].x_position = WIDTH / 2 - this->lineEdit[PORT].x_size / 2;
	this->lineEdit[PORT].y_position = HEIGHT*0.6;

}

void Multiplayer::addLineEdits(sf::Font* font)
{
	this->lineEdit[IP].shape.setSize(sf::Vector2f(lineEdit[IP].x_size, lineEdit[IP].y_size));
	this->lineEdit[IP].shape.setFillColor(sf::Color::Black);
	this->lineEdit[IP].shape.setPosition(lineEdit[IP].x_position, lineEdit[IP].y_position);

	this->lineEdit[IP].name = "TCP/IP:";

	this->lineEdit[IP].textName.setFont(*font);
	this->lineEdit[IP].textName.setString(lineEdit[IP].name);
	this->lineEdit[IP].textName.setCharacterSize(32);
	this->lineEdit[IP].textName.setPosition(lineEdit[IP].x_position - 100.f, lineEdit[IP].y_position);

	this->lineEdit[IP].characters = "";

	this->lineEdit[IP].text.setFont(*font);
	this->lineEdit[IP].text.setString(lineEdit[IP].characters);
	this->lineEdit[IP].text.setCharacterSize(32);
	this->lineEdit[IP].text.setPosition(lineEdit[IP].x_position, lineEdit[IP].y_position);


	this->lineEdit[PORT].shape.setSize(sf::Vector2f(lineEdit[PORT].x_size, lineEdit[PORT].y_size));
	this->lineEdit[PORT].shape.setFillColor(sf::Color::Black);
	this->lineEdit[PORT].shape.setPosition(lineEdit[PORT].x_position, lineEdit[PORT].y_position);

	this->lineEdit[PORT].name = "Port:";

	this->lineEdit[PORT].textName.setFont(*font);
	this->lineEdit[PORT].textName.setString(lineEdit[PORT].name);
	this->lineEdit[PORT].textName.setCharacterSize(32);
	this->lineEdit[PORT].textName.setPosition(lineEdit[PORT].x_position - 65.f, lineEdit[PORT].y_position);

	this->lineEdit[PORT].characters = "";

	this->lineEdit[PORT].text.setFont(*font);
	this->lineEdit[PORT].text.setString(lineEdit[PORT].characters);
	this->lineEdit[PORT].text.setCharacterSize(32);
	this->lineEdit[PORT].text.setPosition(lineEdit[PORT].x_position, lineEdit[PORT].y_position);

}

void Multiplayer::addButtons(sf::Font* font)
{

	this->button["HOST"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.2, WIDTH * 0.3, HEIGHT * 0.1, "HOST", 26);
	this->button["JOIN"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.35, WIDTH * 0.3, HEIGHT * 0.1, "JOIN", 26);
	this->button["BACK"] = new Button(font, (WIDTH / 2) - (WIDTH * 0.3 / 2), HEIGHT * 0.8, WIDTH * 0.3, HEIGHT * 0.1, "BACK", 26);
}

Multiplayer::Multiplayer(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, short& WIDTH, short& HEIGHT, Online* online)
	:window(window), background(background), mousePosWindow(mousePosWindow), mousePosView(mousePosView), font(font), gameState(gameState), WIDTH(WIDTH), HEIGHT(HEIGHT), online(online)
{
	this->variables();
	this->addLineEdits(font);
	this->addButtons(font);

	this->isClicked = false;
}

Multiplayer::~Multiplayer()
{
	for (auto i : this->button)
	{
		delete i.second;
	}
	delete this->background;
}

void Multiplayer::mousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = window->mapPixelToCoords(this->mousePosWindow);
}

void Multiplayer::keyboardUpdate()
{
	while (this->window->pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			this->gameState = MAIN_MENU;
		}
	}
}

void Multiplayer::lineEditsUpdate()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->lineEdit[IP].shape.getGlobalBounds().contains(this->mousePosView))
			if (this->lineEdit[IP].isClicked == false)
			{
				this->lineEdit[IP].isClicked = true;
				this->lineEdit[PORT].isClicked = false;
			}
			else
				this->lineEdit[IP].isClicked = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->lineEdit[PORT].shape.getGlobalBounds().contains(this->mousePosView))
			if (this->lineEdit[PORT].isClicked == false)
			{
				this->lineEdit[PORT].isClicked = true;
				this->lineEdit[IP].isClicked = false;
			}
			else
				this->lineEdit[PORT].isClicked = false;


	if (lineEdit[IP].isClicked == true)
	{
		this->lineEdit[IP].shape.setFillColor(sf::Color::Green);
		if (ev.type == sf::Event::TextEntered)
		{
			if (ev.text.unicode == 8)
			{
				lineEdit[PORT].textInput.erase(lineEdit[PORT].textInput.getSize() - 1, 1);
				lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
				window->waitEvent(ev);
			}
			else
			{
				lineEdit[PORT].textInput += ev.text.unicode;
				lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
				window->waitEvent(ev);
			}
		}
	}
	else
		this->lineEdit[IP].shape.setFillColor(sf::Color::Black);

	if (lineEdit[PORT].isClicked == true)
	{
		this->lineEdit[PORT].shape.setFillColor(sf::Color::Green);
			if (ev.type == sf::Event::TextEntered)
			{
				if (ev.text.unicode == 8)
				{
					lineEdit[PORT].textInput.erase(lineEdit[PORT].textInput.getSize() - 1, 1);
					lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
					window->waitEvent(ev);
				}
				else
				{
					lineEdit[PORT].textInput += ev.text.unicode;
					lineEdit[PORT].text.setString(lineEdit[PORT].textInput);
					window->waitEvent(ev);
				}
			}
	}
	else
			this->lineEdit[PORT].shape.setFillColor(sf::Color::Black);

}

void Multiplayer::buttonUpdate()
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
		if (this->button["JOIN"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
				online->IsConnectionVariable(true);
			}
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (this->button["HOST"]->getBounds().contains(this->mousePosView))
		{
			window->waitEvent(ev);
			if (ev.type == sf::Event::MouseButtonReleased)
			{
					this->online->HostingVariable(true);
					this->gameState = TYPEGAME;
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



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		window->waitEvent(ev);
		if (ev.type == sf::Event::KeyReleased)
		{
			if (online->socket.receive(online->packet) != sf::Socket::Done)
			{
				logl("Error receiving data!");
			}
			else
			{
				logl("receiving data!");
				int receivedIntValue;
				online->packet >> receivedIntValue;
				gameState = static_cast<GameState>(receivedIntValue);
			}
		}
	}
}

void Multiplayer::update()
{
	this->mousePosition();
	this->lineEditsUpdate();
	this->keyboardUpdate();
	this->buttonUpdate();
}

void Multiplayer::render(sf::RenderTarget* target)
{
	target->draw(*background);
	target->draw(lineEdit[IP].shape);
	target->draw(lineEdit[IP].text);
	target->draw(lineEdit[IP].textName);
	target->draw(lineEdit[PORT].shape);
	target->draw(lineEdit[PORT].text);
	target->draw(lineEdit[PORT].textName);

}

void Multiplayer::renderButton()
{
	for (auto i : this->button)
	{
		i.second->render(this->window);
	}

}
