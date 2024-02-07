#pragma once

#include<fstream>
#include<vector>

#include"Button.h"
#include"StatsWindow.h"
#include"Resolution.h"
#include"Panels.h"
#include"GameState.h"

const int tableSize = 484;

enum type { BASIC = 1, BEST_OF_THREE, BEST_OF_FIVE, BEST_OF_SEVEN, BACK };
enum positionSign { HORIZONTALLY, VERTICALLY, DIAGONALLY };

class Board : public sf::Drawable, public sf::Transformable
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};

class Start
{
private:
	sf::RenderWindow* window;
	sf::Sprite* background;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Font* font;
	sf::Text text;
	sf::Text text2;
	sf::Text text3;
	std::string player;
	std::string pointsPlayer_1;
	std::string pointsPlayer_2;
	std::fstream basicBoard;
	std::fstream actualBoard;
	sf::Event ev;

	Panels *escapePanel;
	Panels* informationPanel;

	std::fstream strim;

	short &HEIGHT;
	short &WIDTH;

	sf::Texture* texture;
	sf::Texture nowa;

	int quadSize = 32;
	int height = 22;
	int width = 22;

	bool escPanel;
	bool resolutionPanel;
	std::map<std::string, Button*> button;

	int quad;
	int circlePoints;
	int crossPoints;
	int gameMapUpdate[tableSize];
	int* status;
	int* variable;

	Board board;
	GameState& gameState;
	StatsWindow *statsWindow;

	enum sign { EMPTY, CROSS, CIRCLE };

	void initVariables();
	void addText();
	void initBoard();
public:
	Start(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, sf::Texture* texture, int* variable, short& WIDTH, short& HEIGHT);
	~Start();

	void points(sign SIGN);


	void updateKeyboard();
	void mousePosition();
	void updateBoard();
	void updatePlayers();
	void checkingBoard();
	void checkingBoardContinued(sign SIGN,int &j, int &i,const int &width );
	void update();


	void buttonsMenuRender();
	void buttonsResolutionRender();
	void render(sf::RenderTarget* target);
	void renderEndGame();

	sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);
};

