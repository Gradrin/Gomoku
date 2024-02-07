#include "Button.h"


void Button::initColors()
{
	this->basic = sf::Color(70, 70, 70,200);
	this->intersects = sf::Color(150, 150, 150,255);
	this->click = sf::Color(20, 20, 20,200);
}

void Button::initButton(sf::Font* font, int x_position, int y_position, int x_size, int y_size, std::string str_text, int text_size)
{

	this->shape.setPosition(x_position, y_position);
	this->shape.setSize(sf::Vector2f(x_size, y_size));
	this->shape.setFillColor(basic);
	this->shape.getGlobalBounds();
}

void Button::initText(sf::Font* font, std::string str_text, int text_size)
{
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(str_text);

	this->text.setPosition(this->shape.getPosition().x
		+ (this->shape.getGlobalBounds().width / 2.f)
		- this->text.getGlobalBounds().width / 2.f, this->shape.getPosition().y
		+ (this->shape.getGlobalBounds().height / 2.f)
		- this->text.getGlobalBounds().height / 2.f);

	this->text.setCharacterSize(text_size);
	this->text.setFillColor(sf::Color::Red);
}

Button::Button( sf::Font* font, int x_position, int y_position, int x_size, int y_size, std::string  str_text, int text_size)
{
	this->initColors();
	this->initButton(font, x_position, y_position, x_size, y_size, str_text, text_size);
	this->initText(font, str_text, text_size);
}

Button::~Button()
{
}

const sf::FloatRect& Button::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const sf::Color& Button::getBasic() const
{
	return this->basic;
}

const sf::Color& Button::getIntersect() const
{
	return this->intersects;
}

const sf::Color& Button::getClick() const
{
	return this->click;
}

int Button::getSize_x()const
{
	return this->shape.getSize().x;
}

int Button::getSize_y()const
{
	return this->shape.getSize().y;
}

void Button::setColor(const sf::Color& color)
{
	this->shape.setFillColor(color);
}



void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}
