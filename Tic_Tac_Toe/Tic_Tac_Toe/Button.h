#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include"GameState.h"

class Button
{
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	std::string str_text;

	float x_position;
	float y_position;
	float x_size;
	float y_size;
	float text_size;

	sf::Color basic;
	sf::Color intersects;
	sf::Color click;

	//Constructor's functions
	void initColors();
	void initButton(sf::Font* font, int x_position, int y_position, int x_size, int y_size, std::string  str_text, int text_size);
	void initText(sf::Font* font, std::string str_text, int text_size);

public:
	Button(sf::Font *font, int x_position, int y_position, int x_size, int y_size, std::string  str_text, int text_size);
	~Button();

	const sf::FloatRect& getBounds()const;

	const sf::Color& getBasic()const;
	const sf::Color& getIntersect()const;
	const sf::Color& getClick()const;

	int getSize_x()const;
	int getSize_y()const;

    void setColor(const sf::Color& color);



	void render(sf::RenderTarget* target);
};

