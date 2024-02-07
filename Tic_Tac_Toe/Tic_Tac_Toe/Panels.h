#pragma once

#include"Button.h"
#include "resources.h"

class Panels
{
private:
	sf::RenderWindow* window;
	sf::Sprite escapePanel;
	sf::Texture texture;

	short &HEIGHT;
	short &WIDTH;

public:
	Panels(sf::RenderWindow* window, short& WIDTH, short& HEIGHT);
	~Panels();

	void update();
	void render(sf::RenderTarget* target);


	float getSize_x()const;
	float getSize_y()const;

	short getPosition_x()const;
	short getPosition_y()const;
};
					