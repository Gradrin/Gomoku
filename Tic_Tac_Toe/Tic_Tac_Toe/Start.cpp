#include "Start.h"


//-----------CLASS BOARD------------------//

bool Board::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the gameMap size
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

    return true;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &m_tileset;

    // draw the vertex array
    target.draw(m_vertices, states);
}




//-----------CLASS START------------------//



void Start::initVariables()
{
    this->quadSize = 32;
    this->height = 22;
    this->width = 22;

    escPanel = false;
    resolutionPanel = false;
}

void Start::addText()
{
    this->player = "Player 1 = \nPlayer 2 = ";
    this->pointsPlayer_1 = std::to_string(circlePoints);
    this->pointsPlayer_2 = std::to_string(circlePoints);

    this->text.setFont(*font);
    this->text.setString(player);
    this->text.setCharacterSize(12);
    this->text.setFillColor(sf::Color::Black);
    this->text.setPosition(sf::Vector2f(0.f, 0.f));

    this->text2.setFont(*font);
    this->text2.setString(pointsPlayer_1);
    this->text2.setCharacterSize(12);
    this->text2.setFillColor(sf::Color::Black);
    this->text2.setPosition(sf::Vector2f(45.f, 0.f));

    this->text3.setFont(*font);
    this->text3.setString(pointsPlayer_2);
    this->text3.setCharacterSize(12);
    this->text3.setFillColor(sf::Color::Black);
    this->text3.setPosition(sf::Vector2f(45.f,15.f));
}

void Start::initBoard()
{
  
    this->quad = CIRCLE;

    int gameMap[tableSize];
    int i = 0;
    std::string linia;
    this->basicBoard.open(BOARD);
    while (getline(basicBoard, linia))
    {
        gameMap[i] = std::stoi(linia);
        i++;
    }
    this->basicBoard.close();
    this->board.setPosition((float)quadSize, (float)quadSize);
}

Start::Start(sf::RenderWindow* window, sf::Sprite* background, sf::Vector2i& mousePosWindow, sf::Vector2f& mousePosView, sf::Font* font, GameState& gameState, sf::Texture* texture, int* variable, short& WIDTH, short& HEIGHT)
    :window(window), background(background), mousePosWindow(mousePosWindow), mousePosView(mousePosView), font(font), gameState(gameState), texture(texture), variable(variable), WIDTH(WIDTH), HEIGHT(HEIGHT)
{

    this->initVariables();
    this->addText();
    this->initBoard();

    informationPanel = new Panels(window, WIDTH, HEIGHT);
}

Start::~Start()
{
    delete this->escapePanel;
    delete this->informationPanel;
}

void Start::points(sign SIGN)
{
    if (SIGN == CIRCLE)
        this->circlePoints++;
    else if (SIGN == CROSS)
        this->crossPoints++;
    for (int i = 0; i < tableSize; ++i)
    {
        gameMapUpdate[i] = 0;
    }
    if ((circlePoints == *variable) && (*variable > BASIC))
        this->gameState = GAMESTATS;
    else if ((crossPoints == *variable) && (*variable > BASIC))
        this->gameState = GAMESTATS;
}


void Start::updateKeyboard()
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
                if (escPanel == false)
                {
                    escapePanel = new Panels(window, WIDTH, HEIGHT);
                    this->button["RESUME"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 2, WIDTH * 0.15, HEIGHT * 0.1, "RESUME", 26);
                    this->button["RESOLUTION"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 3.6, WIDTH * 0.15, HEIGHT * 0.1, "RESOLUTION", 26);
                    this->button["EXIT"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 5.25, WIDTH * 0.15, HEIGHT * 0.1, "EXIT", 26);
                    escPanel = true;
                }
                else
                {
                    delete this->escapePanel;
                    delete this->button["RESUME"];
                    delete this->button["RESOLUTION"];
                    delete this->button["EXIT"];

                    escPanel = false;
                }
            }
        }

    if (escPanel == true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {         
            if (this->button["EXIT"]->getBounds().contains(this->mousePosView))
            {
                window->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    this->gameState = MAIN_MENU;
                }
            }
            if (this->button["RESOLUTION"]->getBounds().contains(this->mousePosView))
            {
                window->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    this->button["3840 x 2160"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 1.5, WIDTH * 0.15, HEIGHT * 0.08, "3840 x 2160", 26);
                    this->button["2560 x 1440"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 2.4, WIDTH * 0.15, HEIGHT * 0.08, "2560 x 1440", 26);
                    this->button["1920 x 1080"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 3.3, WIDTH * 0.15, HEIGHT * 0.08, "1920 x 1080", 26);
                    this->button["1024 x 768"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 4.2, WIDTH * 0.15, HEIGHT * 0.08, "1024 x 768", 26);
                    this->button["800 x 600"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 5.1, WIDTH * 0.15, HEIGHT * 0.08, "800 x 600", 26);
                    this->button["BACK"] = new Button(font, escapePanel->getPosition_x() + (WIDTH * escapePanel->getSize_x() * 0.5 - (WIDTH * 0.15 * 0.5)), escapePanel->getPosition_y() * 6.0, WIDTH * 0.15, HEIGHT * 0.08, "BACK", 26);
                    this->resolutionPanel = true;
                }
            }
        }
    }
     

    if (resolutionPanel == true)
    {
        Resolution resolution(window, background, mousePosWindow, mousePosView, font, gameState, texture, WIDTH, HEIGHT);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (this->button["3840 x 2160"]->getBounds().contains(this->mousePosView))
            {
                resolution.buttonFunction(2560, 1440);
            }
            if (this->button["2560 x 1440"]->getBounds().contains(this->mousePosView))
            {
                resolution.buttonFunction(2560, 1440);
            }
            if (this->button["1920 x 1080"]->getBounds().contains(this->mousePosView))
            {
                resolution.buttonFunction(1920, 1080);
            }
            if (this->button["1024 x 768"]->getBounds().contains(this->mousePosView))
            {
                resolution.buttonFunction(1024, 1080);
            }
            if (this->button["800 x 600"]->getBounds().contains(this->mousePosView))
            {
                resolution.buttonFunction(800, 600);
            }
            if (this->button["BACK"]->getBounds().contains(this->mousePosView))
            {
                window->waitEvent(ev);
                if (ev.type == sf::Event::MouseButtonReleased)
                {
                    resolutionPanel = false;
                    escPanel = true;
                    delete this->button["3840 x 2160"];
                    delete this->button["2560 x 1440"];
                    delete this->button["1920 x 1080"];
                    delete this->button["1024 x 768"];
                    delete this->button["800 x 600"];
                    delete this->button["BACK"];
                }
            }
        }
    }


}

void Start::mousePosition()
{  
        this->mousePosWindow = sf::Mouse::getPosition(*this->window);
        this->mousePosView = window->mapPixelToCoords(this->mousePosWindow); 
}

void Start::updateBoard()
{
 
    int gameMap[tableSize];
    int x = 0;

    for (unsigned int j = 0; j < height; ++j)
        for (unsigned int i = 0; i < width; ++i)
        {
            gameMap[x] = gameMapUpdate[x];
            if ((this->mousePosView.x >= (i * quadSize + quadSize) && this->mousePosView.x <= ((i + 1) * quadSize + quadSize)) && (this->mousePosView.y >= (j * quadSize + quadSize) && this->mousePosView.y <= ((j + 1) * quadSize + quadSize)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    window->waitEvent(ev);
                    if (ev.type == sf::Event::MouseButtonReleased)
                    {
                        if ((this->gameMapUpdate[x] != CROSS) && (this->gameMapUpdate[x] != CIRCLE))
                        {
                            this->gameMapUpdate[x] = this->quad;
                            if (this->quad == CROSS)
                                this->quad = CIRCLE;
                            else if (this->quad == CIRCLE)
                                this->quad = CROSS;
                        }
                    }
                }
            }
            x++;
        }
    if (!board.load(ICONS, sf::Vector2u(quadSize, quadSize), gameMap, width, height))
        std::cout << "ERROR" << "\n";

    
    basicBoard.open(BOARD);
    for (unsigned int i = 0; i < tableSize; ++i)
    {
        basicBoard << gameMapUpdate[i] << "\n";
    }
    basicBoard.close();
}

void Start::updatePlayers()
{
    this->pointsPlayer_1 = std::to_string(circlePoints);
    this->text2.setString(pointsPlayer_1);

    this->pointsPlayer_2 = std::to_string(crossPoints);
    this->text3.setString(pointsPlayer_2);
}

void Start::update()
{
    this->updateKeyboard();
    this->mousePosition();
    if (escPanel == false)
    this->updateBoard();
    this->checkingBoard();
    this->updatePlayers();
}

void Start::render(sf::RenderTarget* target)
{
	target->draw(*background);
    target->draw(text);
    target->draw(text2);
    target->draw(text3);
    target->draw(board);
    if (escPanel == true) 
    {
        buttonsMenuRender();
    }
    if (resolutionPanel == true)
    {
        buttonsResolutionRender();
    }

    if (this->gameState == GAMESTATS)
        this->renderEndGame();
}

void Start::checkingBoard()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //POINTS FOR X AND O FOR VERTICALL AND HORIZONTALL
            if (gameMapUpdate[j + (i * width)] == CROSS)
            {
                checkingBoardContinued(CROSS, j, i, width);
            }
            else if (gameMapUpdate[j + (i * width)] == CIRCLE)
            {
                checkingBoardContinued(CIRCLE, j, i, width);
            }
        }
    }
}
 
void Start::checkingBoardContinued(sign SIGN, int& j, int& i, const int& width)
    {
    if ((gameMapUpdate[(j + 1) + ((i + 1) * width)] == SIGN)
        && (gameMapUpdate[(j + 2) + ((i + 2) * width)] == SIGN)
        && (gameMapUpdate[(j + 3) + ((i + 3) * width)] == SIGN)
        && (gameMapUpdate[(j + 4) + ((i + 4) * width)] == SIGN))
    {
        this->points(SIGN);
    }
    if ((gameMapUpdate[(j - 1) + ((i + 1) * width)] == SIGN)
        && (gameMapUpdate[(j - 2) + ((i + 2) * width)] == SIGN)
        && (gameMapUpdate[(j - 3) + ((i + 3) * width)] == SIGN)
        && (gameMapUpdate[(j - 4) + ((i + 4) * width)] == SIGN))
    {
        this->points(SIGN);
    }
    if ((gameMapUpdate[(j + 1) + (i * width)] == SIGN)
        && (gameMapUpdate[(j + 2) + (i * width)] == SIGN)
        && (gameMapUpdate[(j + 3) + (i * width)] == SIGN)
        && (gameMapUpdate[(j + 4) + (i * width)] == SIGN))
    {
        this->points(SIGN);
    }
    if ((gameMapUpdate[j + ((i + 1) * width)] == SIGN)
        && (gameMapUpdate[j + ((i + 2) * width)] == SIGN)
        && (gameMapUpdate[j + ((i + 3) * width)] == SIGN)
        && (gameMapUpdate[j + ((i + 4) * width)] == SIGN))
    {
        this->points(SIGN);
    }
}

void Start::renderEndGame()
{
    this->statsWindow = new StatsWindow(window, mousePosWindow, mousePosView, font, variable, circlePoints, crossPoints, gameState, WIDTH, HEIGHT);
    while (this->gameState == GAMESTATS)
    {
        this->window->clear();
        this->statsWindow->update();
        this->statsWindow->render(window);
        this->statsWindow->buttonsRender();
        this->window->display();
    }
}

void Start::buttonsMenuRender()
{
    escapePanel->render(window);
    button["RESUME"]->render(window);
    button["RESOLUTION"]->render(window);
    button["EXIT"]->render(window);
}

void Start::buttonsResolutionRender()
{
    escapePanel->render(window);
    button["3840 x 2160"]->render(window);
    button["2560 x 1440"]->render(window);
    button["1920 x 1080"]->render(window);
    button["1024 x 768"]->render(window);
    button["800 x 600"]->render(window);
    button["BACK"]->render(window);
}

sf::View Start::getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float)windowHeight;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));

    return view;
}

